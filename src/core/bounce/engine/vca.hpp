// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/bezier.hpp"
#include "bounce/curve/polynomial.hpp"
#include "bounce/engine/ballistic.hpp"

namespace bounce::core::engine {

constexpr double kVGraze = 1e-9;
constexpr int kBisectBits = 40;
constexpr int kNewtonSteps = 3;

struct RootBracket {
  double lo = 0.0;
  double hi = 0.0;
  bool found = false;
};

struct BallCollisionStep {
  bool found = false;
  bool accepted = false;
  double t = 0.0;
  double x = 0.0;
  double y = 0.0;
  double impact_speed = 0.0;
  int segment_index = 0;
  double segment_s = 0.0;
};

curve::CompiledPolynomial collision_difference_x(const curve::CompiledPolynomial& curve_y,
                                                 const BallisticParabola& arc);

RootBracket vca_isolate_smallest_root(const curve::CompiledPolynomial& q, double x_min,
                                      double x_max, int min_segments = 0);

double vca_refine_root_x(const curve::CompiledPolynomial& q, double lo, double hi);

double normal_impact_speed(const curve::CompiledPolynomial& curve_y, double x, double vx,
                           double vy);

BallCollisionStep step_ball_next_collision(const curve::CompiledPolynomial& curve_y,
                                             const BallisticInit& init, double x_min,
                                             double x_max);

BallCollisionStep step_ball_next_collision_x(const curve::CompiledPolynomial& curve_y,
                                             const BallisticInit& init, double x_min,
                                             double x_max);

BallCollisionStep step_ball_next_collision_time(const curve::CompiledPolynomial& curve_y,
                                                const BallisticInit& init, double x_max);

curve::CompiledPolynomial collision_difference_t(const curve::CompiledPolynomial& curve_y,
                                                 const BallisticInit& init);

curve::CompiledPolynomial deflate_linear_root(const curve::CompiledPolynomial& q, double root);

BallCollisionStep step_ball_next_collision_bezier(const curve::CompiledPiecewiseBezier& curve,
                                                  const BallisticInit& init, double x_min,
                                                  double x_max);

} // namespace bounce::core::engine
