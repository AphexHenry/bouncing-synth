// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/polynomial.hpp"

#include <array>
#include <cstddef>
#include <vector>

namespace bounce::core::curve {

struct Vec2 {
  double x;
  double y;
};

enum class BezierKind { Quadratic, Cubic };

struct CompiledBezierSegment {
  BezierKind kind = BezierKind::Quadratic;
  std::array<Vec2, 4> control{};
};

struct CompiledPiecewiseBezier {
  std::vector<CompiledBezierSegment> segments;
};

struct C1ValidationResult {
  bool ok = false;
  int joint_index = -1;
};

CompiledBezierSegment compile_quadratic_bezier(Vec2 p0, Vec2 p1, Vec2 p2);
CompiledBezierSegment compile_cubic_bezier(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);
CompiledPiecewiseBezier compile_piecewise_bezier(std::vector<CompiledBezierSegment> segments);

Vec2 eval(const CompiledBezierSegment& segment, double s);
Vec2 deriv(const CompiledBezierSegment& segment, double s);
UnitNormal normal(const CompiledBezierSegment& segment, double s);

C1ValidationResult validate_c1(const CompiledPiecewiseBezier& curve);

} // namespace bounce::core::curve
