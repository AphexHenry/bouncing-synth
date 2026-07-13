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
