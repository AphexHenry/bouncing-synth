// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/curve/bezier.hpp"

#include <cmath>
#include <stdexcept>

namespace bounce::core::curve {

namespace {

constexpr double kJointPositionTol = 1e-12;
constexpr double kTangentCrossTol = 1e-12;

bool near_equal(double a, double b) {
  return std::fabs(a - b) <= kJointPositionTol;
}

bool near_zero(double v) {
  return std::fabs(v) <= kTangentCrossTol;
}

} // namespace

CompiledBezierSegment compile_quadratic_bezier(Vec2 p0, Vec2 p1, Vec2 p2) {
  CompiledBezierSegment out{};
  out.kind = BezierKind::Quadratic;
  out.control[0] = p0;
  out.control[1] = p1;
  out.control[2] = p2;
  return out;
}

CompiledBezierSegment compile_cubic_bezier(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3) {
  CompiledBezierSegment out{};
  out.kind = BezierKind::Cubic;
  out.control[0] = p0;
  out.control[1] = p1;
  out.control[2] = p2;
  out.control[3] = p3;
  return out;
}

CompiledPiecewiseBezier compile_piecewise_bezier(std::vector<CompiledBezierSegment> segments) {
  if (segments.empty()) {
    throw std::invalid_argument("piecewise bezier requires at least one segment");
  }
  CompiledPiecewiseBezier out{};
  out.segments = std::move(segments);
  return out;
}

Vec2 eval(const CompiledBezierSegment& segment, double s) {
  const double u = 1.0 - s;
  if (segment.kind == BezierKind::Quadratic) {
    const Vec2& p0 = segment.control[0];
    const Vec2& p1 = segment.control[1];
    const Vec2& p2 = segment.control[2];
    const double w0 = u * u;
    const double w1 = 2.0 * u * s;
    const double w2 = s * s;
    return {w0 * p0.x + w1 * p1.x + w2 * p2.x, w0 * p0.y + w1 * p1.y + w2 * p2.y};
  }
  const Vec2& p0 = segment.control[0];
  const Vec2& p1 = segment.control[1];
  const Vec2& p2 = segment.control[2];
  const Vec2& p3 = segment.control[3];
  const double w0 = u * u * u;
  const double w1 = 3.0 * u * u * s;
  const double w2 = 3.0 * u * s * s;
  const double w3 = s * s * s;
  return {w0 * p0.x + w1 * p1.x + w2 * p2.x + w3 * p3.x,
          w0 * p0.y + w1 * p1.y + w2 * p2.y + w3 * p3.y};
}

Vec2 deriv(const CompiledBezierSegment& segment, double s) {
  const double u = 1.0 - s;
  if (segment.kind == BezierKind::Quadratic) {
    const Vec2& p0 = segment.control[0];
    const Vec2& p1 = segment.control[1];
    const Vec2& p2 = segment.control[2];
    return {2.0 * u * (p1.x - p0.x) + 2.0 * s * (p2.x - p1.x),
            2.0 * u * (p1.y - p0.y) + 2.0 * s * (p2.y - p1.y)};
  }
  const Vec2& p0 = segment.control[0];
  const Vec2& p1 = segment.control[1];
  const Vec2& p2 = segment.control[2];
  const Vec2& p3 = segment.control[3];
  return {3.0 * u * u * (p1.x - p0.x) + 6.0 * u * s * (p2.x - p1.x) + 3.0 * s * s * (p3.x - p2.x),
          3.0 * u * u * (p1.y - p0.y) + 6.0 * u * s * (p2.y - p1.y) + 3.0 * s * s * (p3.y - p2.y)};
}

UnitNormal normal(const CompiledBezierSegment& segment, double s) {
  const Vec2 d = deriv(segment, s);
  const double nx = -d.y;
  const double ny = d.x;
  const double len = std::sqrt(nx * nx + ny * ny);
  if (len == 0.0) {
    return {0.0, 1.0};
  }
  return {nx / len, ny / len};
}

C1ValidationResult validate_c1(const CompiledPiecewiseBezier& curve) {
  if (curve.segments.size() <= 1) {
    return {true, -1};
  }
  for (std::size_t i = 1; i < curve.segments.size(); ++i) {
    const auto& left = curve.segments[i - 1];
    const auto& right = curve.segments[i];
    const Vec2 end_pos = eval(left, 1.0);
    const Vec2 start_pos = eval(right, 0.0);
    if (!near_equal(end_pos.x, start_pos.x) || !near_equal(end_pos.y, start_pos.y)) {
      return {false, static_cast<int>(i - 1)};
    }
    const Vec2 end_tangent = deriv(left, 1.0);
    const Vec2 start_tangent = deriv(right, 0.0);
    const double cross = end_tangent.x * start_tangent.y - end_tangent.y * start_tangent.x;
    if (!near_zero(cross)) {
      return {false, static_cast<int>(i - 1)};
    }
  }
  return {true, -1};
}

} // namespace bounce::core::curve
