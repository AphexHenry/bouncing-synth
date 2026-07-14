// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/collision_sim.hpp"

#include "bounce/engine/vca.hpp"

#include <cmath>

namespace bounce::core::engine {

namespace {

constexpr double kDomainEps = 1e-12;

double next_x_min(double x_contact, double vx) {
  if (vx > 0.0) {
    return x_contact + kDomainEps;
  }
  if (vx < 0.0) {
    return x_contact - kDomainEps;
  }
  return x_contact;
}

bool time_less(double t_a, int ball_a, double t_b, int ball_b) {
  if (t_a != t_b) {
    return t_a < t_b;
  }
  return ball_a < ball_b;
}

} // namespace

ReflectedVelocity reflect_velocity(const curve::CompiledPolynomial& curve_y, double x, double vx,
                                   double vy, double restitution) {
  const auto n = curve::normal(curve_y, x);
  const double vn = vx * n.nx + vy * n.ny;
  ReflectedVelocity out{};
  out.vx = vx - (1.0 + restitution) * vn * n.nx;
  out.vy = vy - (1.0 + restitution) * vn * n.ny;
  out.normal_speed_out = std::abs(vn);
  return out;
}

BallSimResult simulate_ball_collisions(const curve::CompiledPolynomial& curve_y,
                                       BallisticInit init, double restitution, double x_max,
                                       int max_events, int ball_id) {
  BallSimResult out{};
  if (max_events <= 0 || init.vx == 0.0) {
    return out;
  }
  double abs_time = 0.0;
  double x_min = init.x0;
  for (int i = 0; i < max_events; ++i) {
    if (out.settled) {
      break;
    }
    const BallCollisionStep step =
        step_ball_next_collision(curve_y, init, x_min, x_max);
    if (!step.found) {
      break;
    }
    const double vy_contact = init.vy - init.g * step.t;
    if (!step.accepted) {
      init.x0 = step.x;
      init.y0 = step.y;
      init.vy = vy_contact;
      x_min = next_x_min(step.x, init.vx);
      continue;
    }
    const double t_abs = abs_time + step.t;
    const auto n = curve::normal(curve_y, step.x);
    events::CollisionEvent event{};
    event.t = t_abs;
    event.ball_id = ball_id;
    event.s = step.x;
    event.impact_speed = step.impact_speed;
    event.normal_x = n.nx;
    event.normal_y = n.ny;
    event.seq = out.count;
    event.schema_version = 1;
    out.events[static_cast<std::size_t>(out.count)] = event;
    ++out.count;
    const ReflectedVelocity reflected =
        reflect_velocity(curve_y, step.x, init.vx, vy_contact, restitution);
    if (reflected.normal_speed_out < kVSettle) {
      out.settled = true;
      break;
    }
    init.x0 = step.x;
    init.y0 = step.y;
    init.vx = reflected.vx;
    init.vy = reflected.vy;
    abs_time = t_abs;
    x_min = next_x_min(step.x, init.vx);
  }
  return out;
}

MultiBallSimResult simulate_multi_ball_collisions(const curve::CompiledPolynomial& curve_y,
                                                  const BallSpec* balls, int ball_count,
                                                  double x_max, int max_events,
                                                  EventEmitSink* sink) {
  MultiBallSimResult out{};
  if (max_events <= 0 || ball_count <= 0 || ball_count > kMaxBalls || balls == nullptr) {
    return out;
  }
  std::array<ActiveBall, kMaxBalls> active{};
  for (int i = 0; i < ball_count; ++i) {
    active[static_cast<std::size_t>(i)].ball_id = balls[i].ball_id;
    active[static_cast<std::size_t>(i)].init = balls[i].init;
    active[static_cast<std::size_t>(i)].restitution = balls[i].restitution;
    active[static_cast<std::size_t>(i)].x_min = balls[i].init.x0;
    active[static_cast<std::size_t>(i)].abs_time = 0.0;
    active[static_cast<std::size_t>(i)].settled = balls[i].init.vx == 0.0;
  }
  for (int emitted = 0; emitted < max_events; ++emitted) {
    int chosen = -1;
    BallCollisionStep chosen_step{};
    double chosen_t_abs = 0.0;
    bool have_candidate = false;
    for (int i = 0; i < ball_count; ++i) {
      auto& ball = active[static_cast<std::size_t>(i)];
      if (ball.settled || ball.init.vx == 0.0) {
        continue;
      }
      const BallCollisionStep step =
          step_ball_next_collision(curve_y, ball.init, ball.x_min, x_max);
      if (!step.found) {
        ball.settled = true;
        continue;
      }
      const double t_abs = ball.abs_time + step.t;
      if (!have_candidate ||
          time_less(t_abs, ball.ball_id, chosen_t_abs, active[static_cast<std::size_t>(chosen)].ball_id)) {
        chosen = i;
        chosen_step = step;
        chosen_t_abs = t_abs;
        have_candidate = true;
      }
    }
    if (!have_candidate || chosen < 0) {
      break;
    }
    auto& ball = active[static_cast<std::size_t>(chosen)];
    const double vy_contact = ball.init.vy - ball.init.g * chosen_step.t;
    if (!chosen_step.accepted) {
      ball.init.x0 = chosen_step.x;
      ball.init.y0 = chosen_step.y;
      ball.init.vy = vy_contact;
      ball.x_min = next_x_min(chosen_step.x, ball.init.vx);
      continue;
    }
    const auto n = curve::normal(curve_y, chosen_step.x);
    events::CollisionEvent event{};
    event.t = chosen_t_abs;
    event.ball_id = ball.ball_id;
    event.s = chosen_step.x;
    event.impact_speed = chosen_step.impact_speed;
    event.normal_x = n.nx;
    event.normal_y = n.ny;
    event.seq = out.count;
    event.schema_version = 1;
    if (sink != nullptr && sink->on_event != nullptr) {
      if (!sink->on_event(sink->user_data, event)) {
        break;
      }
    }
    if (out.count < static_cast<int>(kMaxSimEvents)) {
      out.events[static_cast<std::size_t>(out.count)] = event;
    }
    ++out.count;
    const ReflectedVelocity reflected = reflect_velocity(curve_y, chosen_step.x, ball.init.vx,
                                                         vy_contact, ball.restitution);
    if (reflected.normal_speed_out < kVSettle) {
      ball.settled = true;
    } else {
      ball.init.x0 = chosen_step.x;
      ball.init.y0 = chosen_step.y;
      ball.init.vx = reflected.vx;
      ball.init.vy = reflected.vy;
      ball.abs_time = chosen_t_abs;
      ball.x_min = next_x_min(chosen_step.x, ball.init.vx);
    }
  }
  return out;
}

namespace {

ReflectedVelocity reflect_velocity_bezier(const curve::CompiledBezierSegment& segment, double s,
                                            double vx, double vy, double restitution) {
  const auto n = curve::normal(segment, s);
  const double vn = vx * n.nx + vy * n.ny;
  ReflectedVelocity out{};
  out.vx = vx - (1.0 + restitution) * vn * n.nx;
  out.vy = vy - (1.0 + restitution) * vn * n.ny;
  out.normal_speed_out = std::abs(vn);
  return out;
}

bool time_less_bezier(double t_a, int ball_a, int seg_a, double t_b, int ball_b, int seg_b) {
  if (t_a != t_b) {
    return t_a < t_b;
  }
  if (ball_a != ball_b) {
    return ball_a < ball_b;
  }
  return seg_a < seg_b;
}

} // namespace

MultiBallSimResult simulate_multi_ball_collisions_bezier(
    const curve::CompiledPiecewiseBezier& curve, const BallSpec* balls, int ball_count,
    double x_max, int max_events, EventEmitSink* sink) {
  MultiBallSimResult out{};
  if (max_events <= 0 || ball_count <= 0 || ball_count > kMaxBalls || balls == nullptr) {
    return out;
  }
  std::array<ActiveBall, kMaxBalls> active{};
  for (int i = 0; i < ball_count; ++i) {
    active[static_cast<std::size_t>(i)].ball_id = balls[i].ball_id;
    active[static_cast<std::size_t>(i)].init = balls[i].init;
    active[static_cast<std::size_t>(i)].restitution = balls[i].restitution;
    active[static_cast<std::size_t>(i)].x_min = balls[i].init.x0;
    active[static_cast<std::size_t>(i)].abs_time = 0.0;
    active[static_cast<std::size_t>(i)].settled = balls[i].init.vx == 0.0;
  }
  const double domain_min = curve.segments.empty() ? 0.0 : curve.segments.front().control[0].x;
  for (int emitted = 0; emitted < max_events; ++emitted) {
    int chosen = -1;
    BallCollisionStep chosen_step{};
    double chosen_t_abs = 0.0;
    bool have_candidate = false;
    for (int i = 0; i < ball_count; ++i) {
      auto& ball = active[static_cast<std::size_t>(i)];
      if (ball.settled || ball.init.vx == 0.0) {
        continue;
      }
      const double x_bound = ball.init.vx > 0.0 ? x_max : domain_min;
      const BallCollisionStep step =
          step_ball_next_collision_bezier(curve, ball.init, ball.x_min, x_bound);
      if (!step.found) {
        ball.settled = true;
        continue;
      }
      const double t_abs = ball.abs_time + step.t;
      if (!have_candidate ||
          time_less_bezier(t_abs, ball.ball_id, step.segment_index, chosen_t_abs,
                           active[static_cast<std::size_t>(chosen)].ball_id,
                           chosen_step.segment_index)) {
        chosen = i;
        chosen_step = step;
        chosen_t_abs = t_abs;
        have_candidate = true;
      }
    }
    if (!have_candidate || chosen < 0) {
      break;
    }
    auto& ball = active[static_cast<std::size_t>(chosen)];
    const auto& segment = curve.segments[static_cast<std::size_t>(chosen_step.segment_index)];
    const double vy_contact = ball.init.vy - ball.init.g * chosen_step.t;
    if (!chosen_step.accepted) {
      ball.init.x0 = chosen_step.x;
      ball.init.y0 = chosen_step.y;
      ball.init.vy = vy_contact;
      ball.x_min = next_x_min(chosen_step.x, ball.init.vx);
      continue;
    }
    const auto n = curve::normal(segment, chosen_step.segment_s);
    events::CollisionEvent event{};
    event.t = chosen_t_abs;
    event.ball_id = ball.ball_id;
    event.s = chosen_step.x;
    event.impact_speed = chosen_step.impact_speed;
    event.normal_x = n.nx;
    event.normal_y = n.ny;
    event.seq = out.count;
    event.schema_version = 1;
    if (sink != nullptr && sink->on_event != nullptr) {
      if (!sink->on_event(sink->user_data, event)) {
        break;
      }
    }
    if (out.count < static_cast<int>(kMaxSimEvents)) {
      out.events[static_cast<std::size_t>(out.count)] = event;
    }
    ++out.count;
    const ReflectedVelocity reflected = reflect_velocity_bezier(
        segment, chosen_step.segment_s, ball.init.vx, vy_contact, ball.restitution);
    if (reflected.normal_speed_out < kVSettle) {
      ball.settled = true;
    } else {
      ball.init.x0 = chosen_step.x;
      ball.init.y0 = chosen_step.y;
      ball.init.vx = reflected.vx;
      ball.init.vy = reflected.vy;
      ball.abs_time = chosen_t_abs;
      ball.x_min = next_x_min(chosen_step.x, ball.init.vx);
    }
  }
  return out;
}

} // namespace bounce::core::engine
