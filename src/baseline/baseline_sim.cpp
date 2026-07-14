// SPDX-License-Identifier: GPL-3.0-only
#include "baseline/baseline_sim.hpp"

#include "baseline/polyline.hpp"
#include "bounce/engine/vca.hpp"

#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <limits>
#include <vector>

namespace bounce::baseline {
namespace {

using bounce::core::engine::BallSpec;
using bounce::core::engine::kMaxBalls;
using bounce::core::engine::kMaxSimEvents;
using bounce::core::engine::kVGraze;
using bounce::core::engine::kVSettle;
using bounce::core::engine::MultiBallSimResult;
using bounce::core::engine::ReflectedVelocity;
using bounce::core::events::CollisionEvent;

constexpr double kDomainEps = 1e-12;
constexpr double kContactEps = 1e-15;

struct BallState {
  int ball_id = 0;
  double x = 0.0;
  double y = 0.0;
  double vx = 0.0;
  double vy = 0.0;
  double g = 0.0;
  double restitution = 0.5;
  double x_min = 0.0;
  bool settled = false;
};

struct ContactCandidate {
  bool found = false;
  double tau = 0.0;
  double x = 0.0;
  double y = 0.0;
  int segment = -1;
  double impact_speed = 0.0;
};

double next_x_min(double x_contact, double vx) {
  if (vx > 0.0) {
    return x_contact + kDomainEps;
  }
  if (vx < 0.0) {
    return x_contact - kDomainEps;
  }
  return x_contact;
}

ReflectedVelocity reflect_segment(const SegmentNormal& n, double vx, double vy, double restitution) {
  const double vn = vx * n.nx + vy * n.ny;
  ReflectedVelocity out{};
  out.vx = vx - (1.0 + restitution) * vn * n.nx;
  out.vy = vy - (1.0 + restitution) * vn * n.ny;
  out.normal_speed_out = std::abs(vn);
  return out;
}

bool time_less(double t_a, int ball_a, double t_b, int ball_b) {
  if (t_a != t_b) {
    return t_a < t_b;
  }
  return ball_a < ball_b;
}

ContactCandidate find_segment_contact(const Polyline& poly, double x0, double y0, double vx,
                                      double vy_step, double dt, double x_min_bound,
                                      double x_max_bound) {
  ContactCandidate best{};
  best.tau = std::numeric_limits<double>::infinity();

  for (int seg = 0; seg < poly.segment_count; ++seg) {
    const std::size_t i = static_cast<std::size_t>(seg);
    const double xa = poly.x[i];
    const double xb = poly.x[i + 1];
    const double ya = poly.y[i];
    const double yb = poly.y[i + 1];
    const double seg_dx = xb - xa;
    const double slope = seg_dx == 0.0 ? 0.0 : (yb - ya) / seg_dx;

    const double denom = slope * vx - vy_step;
    if (std::abs(denom) < kContactEps) {
      continue;
    }

    const double numer = y0 - ya - slope * (x0 - xa);
    const double tau = numer / denom;
    if (tau <= kContactEps || tau > dt + kContactEps) {
      continue;
    }

    const double x_c = x0 + vx * tau;
    const double y_c = y0 + vy_step * tau;
    if (x_c < xa - kContactEps || x_c > xb + kContactEps) {
      continue;
    }
    if (x_c < x_min_bound - kContactEps || x_c > x_max_bound + kContactEps) {
      continue;
    }

    const SegmentNormal n = segment_normal(poly, seg);
    const double vn = vx * n.nx + vy_step * n.ny;
    if (vn >= -kContactEps) {
      continue;
    }

    const double gap0 = y0 - surface_y(poly, x0);
    if (gap0 < -kContactEps) {
      continue;
    }

    const double impact_speed = std::abs(vn);
    if (tau < best.tau) {
      best.found = true;
      best.tau = tau;
      best.x = x_c;
      best.y = y_c;
      best.segment = seg;
      best.impact_speed = impact_speed;
    }
  }

  if (!best.found) {
    best.tau = 0.0;
  }
  return best;
}

void advance_ballistic(BallState& ball, double tau) {
  ball.vy -= ball.g * tau;
  ball.x += ball.vx * tau;
  ball.y += ball.vy * tau;
}

} // namespace

MultiBallSimResult simulate_baseline_polyline(const Polyline& poly, double domain_min,
                                              double domain_max, const BallSpec* balls,
                                              int ball_count, int max_events,
                                              const BaselineParams& params,
                                              bounce::core::engine::EventEmitSink* sink) {
  MultiBallSimResult out{};
  if (max_events <= 0 || ball_count <= 0 || ball_count > kMaxBalls || balls == nullptr ||
      params.dt <= 0.0 || poly.segment_count <= 0) {
    return out;
  }

  std::array<BallState, kMaxBalls> state{};
  for (int i = 0; i < ball_count; ++i) {
    state[static_cast<std::size_t>(i)].ball_id = balls[i].ball_id;
    state[static_cast<std::size_t>(i)].x = balls[i].init.x0;
    state[static_cast<std::size_t>(i)].y = balls[i].init.y0;
    state[static_cast<std::size_t>(i)].vx = balls[i].init.vx;
    state[static_cast<std::size_t>(i)].vy = balls[i].init.vy;
    state[static_cast<std::size_t>(i)].g = balls[i].init.g;
    state[static_cast<std::size_t>(i)].restitution = balls[i].restitution;
    state[static_cast<std::size_t>(i)].x_min = balls[i].init.x0;
    state[static_cast<std::size_t>(i)].settled = balls[i].init.vx == 0.0;
  }

  double global_time = 0.0;
  constexpr int kMaxSteps = 10000000;
  for (int step = 0; step < kMaxSteps && out.count < max_events; ++step) {
    int chosen = -1;
    ContactCandidate chosen_contact{};
    double chosen_t_abs = 0.0;
    bool have_candidate = false;

    for (int i = 0; i < ball_count; ++i) {
      auto& ball = state[static_cast<std::size_t>(i)];
      if (ball.settled || ball.vx == 0.0) {
        continue;
      }
      if (ball.x < domain_min - kDomainEps || ball.x > domain_max + kDomainEps) {
        ball.settled = true;
        continue;
      }

      const double vy_step = ball.vy - ball.g * params.dt;
      const ContactCandidate contact = find_segment_contact(
          poly, ball.x, ball.y, ball.vx, vy_step, params.dt, ball.x_min, domain_max);
      if (!contact.found) {
        continue;
      }
      const double t_abs = global_time + contact.tau;
      if (!have_candidate ||
          time_less(t_abs, ball.ball_id, chosen_t_abs,
                    state[static_cast<std::size_t>(chosen)].ball_id)) {
        chosen = i;
        chosen_contact = contact;
        chosen_t_abs = t_abs;
        have_candidate = true;
      }
    }

    if (have_candidate && chosen >= 0) {
      auto& ball = state[static_cast<std::size_t>(chosen)];
      advance_ballistic(ball, chosen_contact.tau);
      global_time += chosen_contact.tau;

      if (chosen_contact.impact_speed < kVGraze) {
        ball.x_min = next_x_min(chosen_contact.x, ball.vx);
        continue;
      }

      const SegmentNormal n = segment_normal(poly, chosen_contact.segment);
      CollisionEvent event{};
      event.t = global_time;
      event.ball_id = ball.ball_id;
      event.s = chosen_contact.x;
      event.impact_speed = chosen_contact.impact_speed;
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

      const ReflectedVelocity reflected =
          reflect_segment(n, ball.vx, ball.vy, ball.restitution);
      if (reflected.normal_speed_out < kVSettle) {
        ball.settled = true;
        continue;
      }
      ball.vx = reflected.vx;
      ball.vy = reflected.vy;
      ball.x_min = next_x_min(chosen_contact.x, ball.vx);
      continue;
    }

    bool any_active = false;
    for (int i = 0; i < ball_count; ++i) {
      auto& ball = state[static_cast<std::size_t>(i)];
      if (ball.settled || ball.vx == 0.0) {
        continue;
      }
      if (ball.x < domain_min - kDomainEps || ball.x > domain_max + kDomainEps) {
        ball.settled = true;
        continue;
      }
      any_active = true;
      advance_ballistic(ball, params.dt);
      if (ball.y < surface_y(poly, ball.x) - kContactEps) {
        ball.y = surface_y(poly, ball.x);
      }
    }
    global_time += params.dt;
    if (!any_active) {
      break;
    }
  }

  return out;
}

MultiBallSimResult simulate_baseline(const bounce::core::curve::CompiledPolynomial& curve_y,
                                     double domain_min, double domain_max,
                                     const BallSpec* balls, int ball_count, int max_events,
                                     const BaselineParams& params,
                                     bounce::core::engine::EventEmitSink* sink) {
  if (params.segments <= 0 || params.segments > kMaxPolylineVertices - 1) {
    return {};
  }
  const Polyline poly =
      sample_polynomial_polyline(curve_y, domain_min, domain_max, params.segments);
  return simulate_baseline_polyline(poly, domain_min, domain_max, balls, ball_count, max_events,
                                    params, sink);
}

MultiBallSimResult simulate_baseline(const Polyline& poly, const BallSpec* balls, int ball_count,
                                     int max_events, const BaselineParams& params,
                                     bounce::core::engine::EventEmitSink* sink) {
  if (poly.segment_count <= 0) {
    return {};
  }
  return simulate_baseline_polyline(poly, poly.x_min, poly.x_max, balls, ball_count, max_events,
                                    params, sink);
}

MultiBallSimResult run_baseline_calibration(
    const bounce::core::scenario::CalibrationScenario& scenario, int max_events,
    const BaselineParams& params, bounce::core::engine::EventEmitSink* sink) {
  Polyline poly{};
  if (scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::PiecewiseBezier) {
    poly = sample_piecewise_bezier_polyline(scenario.piecewise_bezier, params.segments);
  } else {
    std::vector<double> coeff_vec(static_cast<std::size_t>(scenario.coeff_count));
    for (int i = 0; i < scenario.coeff_count; ++i) {
      coeff_vec[static_cast<std::size_t>(i)] =
          scenario.coeffs[static_cast<std::size_t>(i)];
    }
    const auto curve = bounce::core::curve::compile_polynomial(coeff_vec);
    poly = sample_polynomial_polyline(curve, scenario.domain_min, scenario.domain_max,
                                      params.segments);
  }
  return simulate_baseline(poly, scenario.balls.data(), scenario.ball_count, max_events, params,
                           sink);
}

void dump_baseline_trajectory(const bounce::core::scenario::CalibrationScenario& scenario,
                              const BaselineParams& params, double t_start, double t_end) {
  std::vector<double> coeff_vec(static_cast<std::size_t>(scenario.coeff_count));
  for (int i = 0; i < scenario.coeff_count; ++i) {
    coeff_vec[static_cast<std::size_t>(i)] =
        scenario.coeffs[static_cast<std::size_t>(i)];
  }
  const auto curve = bounce::core::curve::compile_polynomial(coeff_vec);
  const Polyline poly = sample_polynomial_polyline(curve, scenario.domain_min, scenario.domain_max,
                                                   params.segments);

  BallState ball{};
  ball.ball_id = scenario.balls[0].ball_id;
  ball.x = scenario.balls[0].init.x0;
  ball.y = scenario.balls[0].init.y0;
  ball.vx = scenario.balls[0].init.vx;
  ball.vy = scenario.balls[0].init.vy;
  ball.g = scenario.balls[0].init.g;
  ball.restitution = scenario.balls[0].restitution;
  ball.x_min = scenario.balls[0].init.x0;

  double global_time = 0.0;
  int step = 0;
  std::cout << std::format("# baseline trajectory dump dt={} segments={} window=[{},{}]\n",
                           params.dt, params.segments, t_start, t_end);
  std::cout << "step,time,x,y,vx,vy,event\n";

  while (global_time <= t_end + params.dt && step < 10000000) {
    if (global_time >= t_start - params.dt) {
      std::cout << std::format("{},{:.17g},{:.17g},{:.17g},{:.17g},{:.17g},-\n", step, global_time,
                               ball.x, ball.y, ball.vx, ball.vy);
    }

    const double vy_step = ball.vy - ball.g * params.dt;
    const ContactCandidate contact = find_segment_contact(
        poly, ball.x, ball.y, ball.vx, vy_step, params.dt, ball.x_min, scenario.domain_max);
    if (contact.found && global_time + contact.tau <= t_end + params.dt) {
      const double t_abs = global_time + contact.tau;
      advance_ballistic(ball, contact.tau);
      global_time = t_abs;
      if (contact.impact_speed >= kVGraze) {
        if (t_abs >= t_start - params.dt) {
          std::cout << std::format("{},{:.17g},{:.17g},{:.17g},{:.17g},{:.17g},contact\n", step + 1,
                                   t_abs, ball.x, ball.y, ball.vx, ball.vy);
        }
        const SegmentNormal n = segment_normal(poly, contact.segment);
        const ReflectedVelocity reflected =
            reflect_segment(n, ball.vx, ball.vy, ball.restitution);
        ball.vx = reflected.vx;
        ball.vy = reflected.vy;
        ball.x_min = next_x_min(contact.x, ball.vx);
        ++step;
        continue;
      }
      ball.x_min = next_x_min(contact.x, ball.vx);
    }

    advance_ballistic(ball, params.dt);
    if (ball.y < surface_y(poly, ball.x) - kContactEps) {
      ball.y = surface_y(poly, ball.x);
    }
    global_time += params.dt;
    ++step;
    if (ball.x < scenario.domain_min - kDomainEps || ball.x > scenario.domain_max + kDomainEps) {
      if (global_time >= t_start) {
        std::cout << std::format("# domain exit at t={:.17g} x={:.17g}\n", global_time, ball.x);
      }
      break;
    }
  }
}

} // namespace bounce::baseline
