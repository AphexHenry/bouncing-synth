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

} // namespace bounce::core::engine
