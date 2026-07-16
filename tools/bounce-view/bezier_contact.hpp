// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/bezier.hpp"

namespace bounce_view {

struct BezierContact {
  std::size_t segment_index = 0;
  double segment_s = 0.0;
  bool found = false;
};

BezierContact locate_bezier_contact(const bounce::core::curve::CompiledPiecewiseBezier& curve,
                                    double contact_x);

} // namespace bounce_view
