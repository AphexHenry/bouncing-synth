// SPDX-License-Identifier: GPL-3.0-only
#include "baseline/polyline.hpp"

#include <algorithm>
#include <cmath>

namespace bounce::baseline {

Polyline sample_polynomial_polyline(const bounce::core::curve::CompiledPolynomial& curve,
                                    double x_min, double x_max, int segment_count) {
  Polyline out{};
  if (segment_count <= 0) {
    return out;
  }
  out.segment_count = segment_count;
  out.x_min = x_min;
  out.x_max = x_max;
  const int vertex_count = segment_count + 1;
  const double dx = (x_max - x_min) / static_cast<double>(segment_count);
  for (int i = 0; i < vertex_count; ++i) {
    const double x = x_min + static_cast<double>(i) * dx;
    out.x[static_cast<std::size_t>(i)] = x;
    out.y[static_cast<std::size_t>(i)] = bounce::core::curve::eval(curve, x);
  }
  return out;
}

Polyline sample_piecewise_bezier_polyline(
    const bounce::core::curve::CompiledPiecewiseBezier& curve, int segment_count) {
  Polyline out{};
  if (segment_count <= 0 || curve.segments.empty()) {
    return out;
  }
  const int bezier_segments = static_cast<int>(curve.segments.size());
  const int per_seg = std::max(1, segment_count / bezier_segments);
  out.segment_count = per_seg * bezier_segments;
  int vertex = 0;
  out.x_min = bounce::core::curve::eval(curve.segments.front(), 0.0).x;
  out.x_max = bounce::core::curve::eval(curve.segments.back(), 1.0).x;
  for (const auto& segment : curve.segments) {
    for (int i = 0; i <= per_seg; ++i) {
      if (vertex >= kMaxPolylineVertices) {
        break;
      }
      const double s = static_cast<double>(i) / static_cast<double>(per_seg);
      const auto p = bounce::core::curve::eval(segment, s);
      out.x[static_cast<std::size_t>(vertex)] = p.x;
      out.y[static_cast<std::size_t>(vertex)] = p.y;
      ++vertex;
      if (i == per_seg && &segment != &curve.segments.back()) {
        --vertex;
      }
    }
  }
  out.segment_count = vertex - 1;
  if (out.segment_count > 0) {
    out.x_min = out.x[0];
    out.x_max = out.x[static_cast<std::size_t>(out.segment_count)];
  }
  return out;
}

SegmentNormal segment_normal(const Polyline& poly, int segment_index) {
  const std::size_t i = static_cast<std::size_t>(segment_index);
  const double dx = poly.x[i + 1] - poly.x[i];
  const double dy = poly.y[i + 1] - poly.y[i];
  const double len = std::hypot(dx, dy);
  SegmentNormal n{};
  if (len <= 0.0) {
    n.ny = 1.0;
    return n;
  }
  n.nx = -dy / len;
  n.ny = dx / len;
  if (n.ny < 0.0) {
    n.nx = -n.nx;
    n.ny = -n.ny;
  }
  return n;
}

double surface_y(const Polyline& poly, double x) {
  if (poly.segment_count <= 0) {
    return 0.0;
  }
  if (x <= poly.x_min) {
    return poly.y[0];
  }
  if (x >= poly.x_max) {
    return poly.y[static_cast<std::size_t>(poly.segment_count)];
  }
  const double dx = (poly.x_max - poly.x_min) / static_cast<double>(poly.segment_count);
  const int seg = static_cast<int>(std::floor((x - poly.x_min) / dx));
  const int clamped = std::clamp(seg, 0, poly.segment_count - 1);
  const std::size_t i = static_cast<std::size_t>(clamped);
  const double seg_dx = poly.x[i + 1] - poly.x[i];
  if (seg_dx == 0.0) {
    return poly.y[i];
  }
  const double t = (x - poly.x[i]) / seg_dx;
  return poly.y[i] + t * (poly.y[i + 1] - poly.y[i]);
}

} // namespace bounce::baseline
