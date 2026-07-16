// SPDX-License-Identifier: GPL-3.0-only
#include "bezier_contact.hpp"

#include <algorithm>
#include <cmath>

namespace bounce_view {

namespace {

constexpr double kEps = 1e-9;

double segment_x_min(const bounce::core::curve::CompiledBezierSegment& segment) {
  double xmin = segment.control[0].x;
  for (const auto& p : segment.control) {
    xmin = std::min(xmin, p.x);
  }
  return xmin;
}

double segment_x_max(const bounce::core::curve::CompiledBezierSegment& segment) {
  double xmax = segment.control[0].x;
  for (const auto& p : segment.control) {
    xmax = std::max(xmax, p.x);
  }
  return xmax;
}

double invert_segment_x(const bounce::core::curve::CompiledBezierSegment& segment, double contact_x) {
  double slo = 0.0;
  double shi = 1.0;
  for (int i = 0; i < 64; ++i) {
    const double sm = 0.5 * (slo + shi);
    const double xm = bounce::core::curve::eval(segment, sm).x;
    if (xm < contact_x) {
      slo = sm;
    } else {
      shi = sm;
    }
  }
  return 0.5 * (slo + shi);
}

} // namespace

BezierContact locate_bezier_contact(
    const bounce::core::curve::CompiledPiecewiseBezier& curve, double contact_x) {
  BezierContact out{};
  for (std::size_t i = 0; i < curve.segments.size(); ++i) {
    const auto& segment = curve.segments[i];
    const double xmin = segment_x_min(segment) - kEps;
    const double xmax = segment_x_max(segment) + kEps;
    if (contact_x < xmin || contact_x > xmax) {
      continue;
    }
    out.segment_index = i;
    out.segment_s = invert_segment_x(segment, contact_x);
    out.found = true;
    return out;
  }
  if (!curve.segments.empty()) {
    out.segment_index = 0;
    out.segment_s = invert_segment_x(curve.segments.front(), contact_x);
    out.found = true;
  }
  return out;
}

} // namespace bounce_view
