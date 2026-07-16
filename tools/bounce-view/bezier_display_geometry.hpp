// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/bezier.hpp"

namespace bounce_view {

// Display-only: map contact x to piecewise-bezier segment coordinates for curve rasterization.
struct BezierDisplayPoint {
  std::size_t segment_index = 0;
  double segment_s = 0.0;
  bool found = false;
};

BezierDisplayPoint locate_bezier_display_point(
    const bounce::core::curve::CompiledPiecewiseBezier& curve, double contact_x);

} // namespace bounce_view
