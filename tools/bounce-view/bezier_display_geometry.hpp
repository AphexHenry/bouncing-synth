// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/bezier.hpp"

#include "bounce/engine/ballistic.hpp"

namespace bounce_view {

// Display-only: map contact x to piecewise-bezier segment coordinates for curve rasterization.
struct BezierDisplayPoint {
  std::size_t segment_index = 0;
  double segment_s = 0.0;
  bool found = false;
};

BezierDisplayPoint locate_bezier_display_point(
    const bounce::core::curve::CompiledPiecewiseBezier& curve, double contact_x);

// Display-only: world position on the drawn curve at contact x (event.s for bezier).
bounce::core::engine::Vec2 eval_bezier_at_contact_x(
    const bounce::core::curve::CompiledPiecewiseBezier& curve, double contact_x);

} // namespace bounce_view
