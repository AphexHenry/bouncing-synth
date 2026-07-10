// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/polynomial.hpp"
#include "bounce/engine/ballistic.hpp"
#include "bounce/events/collision_event.hpp"

#include <array>
#include <cstddef>

namespace bounce::core::engine {

constexpr double kVSettle = 1e-9;
constexpr std::size_t kMaxSimEvents = 64;

struct ReflectedVelocity {
  double vx = 0.0;
  double vy = 0.0;
  double normal_speed_out = 0.0;
};

struct BallSimResult {
  std::array<events::CollisionEvent, kMaxSimEvents> events{};
  int count = 0;
  bool settled = false;
};

ReflectedVelocity reflect_velocity(const curve::CompiledPolynomial& curve_y, double x, double vx,
                                   double vy, double restitution);

BallSimResult simulate_ball_collisions(const curve::CompiledPolynomial& curve_y,
                                       BallisticInit init, double restitution, double x_max,
                                       int max_events, int ball_id = 0);

} // namespace bounce::core::engine
