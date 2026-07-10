// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/vca.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

namespace bounce::core::engine {

namespace {

using bounce::core::curve::compile_polynomial;
using bounce::core::curve::CompiledPolynomial;
using bounce::core::curve::eval;

CompiledPolynomial poly_subtract(const CompiledPolynomial& a, const CompiledPolynomial& b) {
  const int deg = std::max(a.degree, b.degree);
  std::vector<double> coeffs(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int k = 0; k <= deg; ++k) {
    coeffs[static_cast<std::size_t>(k)] =
        a.coeffs[static_cast<std::size_t>(k)] - b.coeffs[static_cast<std::size_t>(k)];
  }
  return compile_polynomial(coeffs);
}

bool has_root_in_interval(const CompiledPolynomial& q, double lo, double hi) {
  const double pl = eval(q, lo);
  const double pr = eval(q, hi);
  if (pl == 0.0 || pr == 0.0) {
    return true;
  }
  if (pl * pr > 0.0) {
    return false;
  }
  if (hi - lo <= 1e-15) {
    return true;
  }
  const double mid = 0.5 * (lo + hi);
  const double pm = eval(q, mid);
  if (pm == 0.0) {
    return true;
  }
  return has_root_in_interval(q, lo, mid) || has_root_in_interval(q, mid, hi);
}

} // namespace

curve::CompiledPolynomial collision_difference_x(const CompiledPolynomial& curve_y,
                                                 const BallisticParabola& arc) {
  return poly_subtract(curve_y, arc.poly);
}

RootBracket vca_isolate_smallest_root(const CompiledPolynomial& q, double x_min, double x_max) {
  RootBracket out{};
  if (q.degree < 1 || x_max <= x_min) {
    return out;
  }
  const int nseg = std::max(16, q.degree * 8);
  const double step = (x_max - x_min) / static_cast<double>(nseg);
  double prev_x = x_min;
  double prev_v = eval(q, prev_x);
  for (int i = 1; i <= nseg; ++i) {
    const double x = x_min + step * static_cast<double>(i);
    const double v = eval(q, x);
    if (prev_v == 0.0) {
      out.found = true;
      out.lo = prev_x;
      out.hi = prev_x;
      return out;
    }
    if (v == 0.0) {
      out.found = true;
      out.lo = x;
      out.hi = x;
      return out;
    }
    if (prev_v * v < 0.0 && has_root_in_interval(q, prev_x, x)) {
      out.found = true;
      out.lo = prev_x;
      out.hi = x;
      return out;
    }
    prev_x = x;
    prev_v = v;
  }
  return out;
}

} // namespace bounce::core::engine
