// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/vca.hpp"

#include "bounce/numerics/double_double.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

namespace bounce::core::engine {

namespace {

using bounce::core::curve::compile_polynomial;
using bounce::core::curve::CompiledPolynomial;
using bounce::core::curve::eval;
using bounce::core::curve::normal;
using bounce::core::numerics::dd_add;
using bounce::core::numerics::dd_div;
using bounce::core::numerics::dd_from_double;
using bounce::core::numerics::dd_mul;
using bounce::core::numerics::DoubleDouble;
using bounce::core::numerics::to_double;

CompiledPolynomial poly_subtract(const CompiledPolynomial& a, const CompiledPolynomial& b) {
  const int deg = std::max(a.degree, b.degree);
  std::vector<double> coeffs(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int k = 0; k <= deg; ++k) {
    coeffs[static_cast<std::size_t>(k)] =
        a.coeffs[static_cast<std::size_t>(k)] - b.coeffs[static_cast<std::size_t>(k)];
  }
  return compile_polynomial(coeffs);
}

CompiledPolynomial poly_derivative(const CompiledPolynomial& p) {
  if (p.degree < 1) {
    return compile_polynomial({0.0});
  }
  std::vector<double> dc(static_cast<std::size_t>(p.degree));
  for (int k = 1; k <= p.degree; ++k) {
    dc[static_cast<std::size_t>(k - 1)] = p.coeffs[static_cast<std::size_t>(k)] *
                                          static_cast<double>(k);
  }
  return compile_polynomial(dc);
}

DoubleDouble eval_dd(const CompiledPolynomial& p, const DoubleDouble& x) {
  DoubleDouble acc = dd_from_double(p.coeffs[static_cast<std::size_t>(p.degree)]);
  for (int k = p.degree - 1; k >= 0; --k) {
    acc = dd_add(dd_mul(acc, x), dd_from_double(p.coeffs[static_cast<std::size_t>(k)]));
  }
  return acc;
}

DoubleDouble dd_neg(const DoubleDouble& a) {
  return {-a.hi, -a.lo};
}

DoubleDouble dd_sub(const DoubleDouble& a, const DoubleDouble& b) {
  return dd_add(a, dd_neg(b));
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

double vca_refine_root_x(const CompiledPolynomial& q, double lo, double hi) {
  if (lo == hi) {
    return lo;
  }
  const double scale = hi - lo;
  const double target = scale * std::ldexp(1.0, -kBisectBits);
  double a = lo;
  double b = hi;
  double fa = eval(q, a);
  double fb = eval(q, b);
  while (b - a > target) {
    const double m = 0.5 * (a + b);
    const double fm = eval(q, m);
    if (fm == 0.0) {
      a = b = m;
      break;
    }
    if (fa * fm <= 0.0) {
      b = m;
      fb = fm;
    } else {
      a = m;
      fa = fm;
    }
  }
  DoubleDouble t = dd_from_double(0.5 * (a + b));
  const CompiledPolynomial dq = poly_derivative(q);
  for (int i = 0; i < kNewtonSteps; ++i) {
    const DoubleDouble ft = eval_dd(q, t);
    const DoubleDouble dft = eval_dd(dq, t);
    if (to_double(dft) == 0.0) {
      break;
    }
    t = dd_sub(t, dd_div(ft, dft));
    const double td = to_double(t);
    if (td < lo) {
      t = dd_from_double(lo);
    } else if (td > hi) {
      t = dd_from_double(hi);
    }
  }
  double out = to_double(t);
  if (out < lo) {
    out = lo;
  } else if (out > hi) {
    out = hi;
  }
  return out;
}

double normal_impact_speed(const CompiledPolynomial& curve_y, double x, double vx, double vy) {
  const auto n = normal(curve_y, x);
  const double vn = vx * n.nx + vy * n.ny;
  return std::abs(vn);
}

BallCollisionStep step_ball_next_collision(const CompiledPolynomial& curve_y,
                                             const BallisticInit& init, double x_min,
                                             double x_max) {
  BallCollisionStep out{};
  if (init.vx == 0.0) {
    return out;
  }
  const BallisticParabola arc = ballistic_parabola_px(init);
  const CompiledPolynomial diff = collision_difference_x(curve_y, arc);
  const RootBracket bracket = vca_isolate_smallest_root(diff, x_min, x_max);
  if (!bracket.found) {
    return out;
  }
  out.found = true;
  out.x = vca_refine_root_x(diff, bracket.lo, bracket.hi);
  out.t = (out.x - init.x0) / init.vx;
  out.y = eval(curve_y, out.x);
  const double vy_contact = init.vy - init.g * out.t;
  out.impact_speed = normal_impact_speed(curve_y, out.x, init.vx, vy_contact);
  out.accepted = out.impact_speed >= kVGraze;
  return out;
}

} // namespace bounce::core::engine
