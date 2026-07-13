// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/curve/polynomial.hpp"

#include <array>
#include <cmath>

namespace bounce::baseline {

constexpr int kMaxPolylineVertices = 257;

struct Polyline {
  int segment_count = 0;
  double x_min = 0.0;
  double x_max = 0.0;
  std::array<double, kMaxPolylineVertices> x{};
  std::array<double, kMaxPolylineVertices> y{};
};

struct SegmentNormal {
  double nx = 0.0;
  double ny = 1.0;
};

Polyline sample_polynomial_polyline(const bounce::core::curve::CompiledPolynomial& curve,
                                    double x_min, double x_max, int segment_count);

SegmentNormal segment_normal(const Polyline& poly, int segment_index);

double surface_y(const Polyline& poly, double x);

} // namespace bounce::baseline
