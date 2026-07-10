// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/polynomial.hpp"

namespace bounce::core::engine {

struct BallisticInit {
  double x0 = 0.0;
  double y0 = 0.0;
  double vx = 0.0;
  double vy = 0.0;
  double g = 0.0;
};

struct BallisticParabola {
  bounce::core::curve::CompiledPolynomial poly{};
  double x0 = 0.0;
  double vx = 0.0;
};

struct Vec2 {
  double x;
  double y;
};

BallisticParabola ballistic_parabola_px(const BallisticInit& init);
Vec2 position_at_time(const BallisticInit& init, double t);

} // namespace bounce::core::engine
