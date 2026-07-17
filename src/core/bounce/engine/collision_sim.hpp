// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/polynomial.hpp"
#include "bounce/curve/bezier.hpp"
#include "bounce/engine/ballistic.hpp"
#include "bounce/events/collision_event.hpp"

#include <array>
#include <cstddef>
#include <vector>

namespace bounce::core::engine {

constexpr double kVSettle = 1e-9;
constexpr std::size_t kMaxSimEvents = 256;
constexpr int kMaxOfflineEvents = 1'000'000;
constexpr int kMaxBalls = 4;

struct EventEmitSink {
  void* user_data = nullptr;
  bool (*on_event)(void* user_data, const events::CollisionEvent& event) = nullptr;
};

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

struct BallSpec {
  int ball_id = 0;
  BallisticInit init{};
  double restitution = 0.5;
};

struct ActiveBall {
  int ball_id = 0;
  BallisticInit init{};
  double restitution = 0.5;
  double x_min = 0.0;
  double abs_time = 0.0;
  bool settled = false;
  int depart_segment = -1;
  double depart_s = 0.0;
};

struct MultiBallSimResult {
  std::vector<events::CollisionEvent> events;
  int count = 0;
};

ReflectedVelocity reflect_velocity(const curve::CompiledPolynomial& curve_y, double x, double vx,
                                   double vy, double restitution);

BallSimResult simulate_ball_collisions(const curve::CompiledPolynomial& curve_y,
                                       BallisticInit init, double restitution, double x_max,
                                       int max_events, int ball_id = 0);

MultiBallSimResult simulate_multi_ball_collisions(const curve::CompiledPolynomial& curve_y,
                                                  const BallSpec* balls, int ball_count,
                                                  double x_max, int max_events,
                                                  EventEmitSink* sink = nullptr);

MultiBallSimResult simulate_multi_ball_collisions_bezier(
    const curve::CompiledPiecewiseBezier& curve, const BallSpec* balls, int ball_count,
    double x_max, int max_events, EventEmitSink* sink = nullptr);

} // namespace bounce::core::engine
