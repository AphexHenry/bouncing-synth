// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/polynomial.hpp"
#include "bounce/engine/ballistic.hpp"

namespace bounce::core::engine {

struct RootBracket {
  double lo = 0.0;
  double hi = 0.0;
  bool found = false;
};

curve::CompiledPolynomial collision_difference_x(const curve::CompiledPolynomial& curve_y,
                                                 const BallisticParabola& arc);

RootBracket vca_isolate_smallest_root(const curve::CompiledPolynomial& q, double x_min,
                                      double x_max);

} // namespace bounce::core::engine
