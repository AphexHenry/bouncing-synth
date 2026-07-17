// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/vca.hpp"

#include "bounce/curve/bezier.hpp"
#include "bounce/numerics/double_double.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
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
using bounce::core::numerics::dd_sub;
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

} // namespace

CompiledPolynomial deflate_linear_root(const CompiledPolynomial& q, double root) {
  if (q.degree < 1) {
    return compile_polynomial({0.0});
  }
  const int n = q.degree;
  std::vector<double> out(static_cast<std::size_t>(n));
  double carry = q.coeffs[static_cast<std::size_t>(n)];
  out[static_cast<std::size_t>(n - 1)] = carry;
  for (int k = n - 1; k >= 1; --k) {
    carry = q.coeffs[static_cast<std::size_t>(k)] + root * carry;
    out[static_cast<std::size_t>(k - 1)] = carry;
  }
  return compile_polynomial(out);
}

namespace {

double strict_departure_x_min(double x_dep, double vx, double x_max) {
  if (vx > 0.0) {
    return std::nextafter(x_dep, std::numeric_limits<double>::infinity());
  }
  if (vx < 0.0) {
    return std::nextafter(x_dep, -std::numeric_limits<double>::infinity());
  }
  return x_dep;
}

double ballistic_ground_time_upper(const BallisticInit& init) {
  if (init.g <= 0.0) {
    return 0.1;
  }
  if (init.y0 <= 1e-15) {
    const double vy_eff = std::abs(init.vy);
    if (vy_eff > 0.0) {
      return std::max(0.1, 2.0 * vy_eff / init.g);
    }
    return 0.1;
  }
  const double disc = init.vy * init.vy + 2.0 * init.g * init.y0;
  if (disc <= 0.0) {
    return std::max(0.1, std::abs(init.vy) / init.g);
  }
  return std::max(0.1, (init.vy + std::sqrt(disc)) / init.g);
}

double x_reachable_upper(const BallisticInit& init, double x_max) {
  const double t = ballistic_ground_time_upper(init);
  if (init.vx > 0.0) {
    return std::min(x_max, init.x0 + init.vx * t);
  }
  if (init.vx < 0.0) {
    return std::max(-x_max, init.x0 + init.vx * t);
  }
  return init.x0;
}

int time_scan_segments(double t_lo, double scan_hi, double t_flight) {
  const double span = scan_hi - t_lo;
  if (span <= 0.0) {
    return 32;
  }
  const double resolution = std::max(t_flight / static_cast<double>(std::max(32, kBisectBits)),
                                     std::numeric_limits<double>::epsilon());
  return std::min(4096, std::max(32, static_cast<int>(std::ceil(span / resolution))));
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

bool has_root_in_interval(const CompiledPolynomial& q, double lo, double hi) {
  double a = lo;
  double b = hi;
  double fa = eval(q, a);
  double fb = eval(q, b);
  if (fa == 0.0 || fb == 0.0) {
    return true;
  }
  if (fa * fb > 0.0) {
    return false;
  }
  while (b - a > 1e-15) {
    const double mid = 0.5 * (a + b);
    const double fm = eval(q, mid);
    if (fm == 0.0) {
      return true;
    }
    if (fa * fm <= 0.0) {
      b = mid;
      fb = fm;
    } else {
      a = mid;
      fa = fm;
    }
  }
  return true;
}

} // namespace

curve::CompiledPolynomial collision_difference_x(const CompiledPolynomial& curve_y,
                                                 const BallisticParabola& arc) {
  return poly_subtract(curve_y, arc.poly);
}

RootBracket vca_isolate_smallest_root(const CompiledPolynomial& q, double x_min, double x_max,
                                      int min_segments) {
  RootBracket out{};
  if (q.degree < 1 || x_max <= x_min) {
    return out;
  }
  const int nseg = min_segments > 0 ? min_segments : std::max(16, q.degree * 8);
  const double step = (x_max - x_min) / static_cast<double>(nseg);
  double prev_x = x_min;
  double prev_v = eval(q, prev_x);
  for (int i = 1; i <= nseg; ++i) {
    const double x = x_min + step * static_cast<double>(i);
    const double v = eval(q, x);
    if (prev_v == 0.0) {
      if (x > prev_x) {
        out.found = true;
        out.lo = prev_x;
        out.hi = prev_x;
        return out;
      }
      prev_x = x;
      prev_v = v;
      continue;
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

RootBracket vca_isolate_largest_root(const CompiledPolynomial& q, double x_min, double x_max) {
  RootBracket out{};
  if (q.degree < 1 || x_max <= x_min) {
    return out;
  }
  const int nseg = std::max(16, q.degree * 8);
  const double step = (x_max - x_min) / static_cast<double>(nseg);
  double prev_x = x_max;
  double prev_v = eval(q, prev_x);
  for (int i = 1; i <= nseg; ++i) {
    const double x = x_max - step * static_cast<double>(i);
    const double v = eval(q, x);
    if (prev_v == 0.0) {
      if (prev_x > x) {
        out.found = true;
        out.lo = prev_x;
        out.hi = prev_x;
        return out;
      }
      prev_x = x;
      prev_v = v;
      continue;
    }
    if (v == 0.0) {
      out.found = true;
      out.lo = x;
      out.hi = x;
      return out;
    }
    if (prev_v * v < 0.0 && has_root_in_interval(q, x, prev_x)) {
      out.found = true;
      out.lo = x;
      out.hi = prev_x;
      return out;
    }
    prev_x = x;
    prev_v = v;
  }
  return out;
}

double curve_y_at_x(const CompiledPolynomial& curve_y, double x) {
  return to_double(eval_dd(curve_y, dd_from_double(x)));
}

bool polish_collision_x(const CompiledPolynomial& curve_y, const BallisticInit& init,
                        double x_min, double x_max, BallCollisionStep& step) {
  const BallisticParabola arc = ballistic_parabola_px(init);
  CompiledPolynomial diff = collision_difference_x(curve_y, arc);
  const double dx = std::max(1e-14, std::abs(step.x) * 1e-12);
  double lo = step.x - dx;
  double hi = step.x + dx;
  if (init.vx > 0.0) {
    lo = std::max(x_min, lo);
    hi = std::min(x_max, hi);
  } else {
    lo = std::max(-x_max, lo);
    hi = std::min(x_min, hi);
  }
  if (hi <= lo) {
    return false;
  }
  step.x = vca_refine_root_x(diff, lo, hi);
  step.t = (step.x - init.x0) / init.vx;
  step.y = curve_y_at_x(curve_y, step.x);
  const double vy_contact = init.vy - init.g * step.t;
  step.impact_speed = normal_impact_speed(curve_y, step.x, init.vx, vy_contact);
  step.accepted = step.impact_speed >= kVGraze;
  return true;
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

std::vector<double> poly_trim_vec(const std::vector<double>& p) {
  int deg = static_cast<int>(p.size()) - 1;
  while (deg > 0 && p[static_cast<std::size_t>(deg)] == 0.0) {
    --deg;
  }
  return std::vector<double>(p.begin(), p.begin() + deg + 1);
}

std::vector<double> poly_add_vec(const std::vector<double>& a, const std::vector<double>& b) {
  const int deg = std::max(static_cast<int>(a.size()), static_cast<int>(b.size())) - 1;
  std::vector<double> out(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int k = 0; k <= deg; ++k) {
    const double av = k < static_cast<int>(a.size()) ? a[static_cast<std::size_t>(k)] : 0.0;
    const double bv = k < static_cast<int>(b.size()) ? b[static_cast<std::size_t>(k)] : 0.0;
    out[static_cast<std::size_t>(k)] = av + bv;
  }
  return poly_trim_vec(out);
}

std::vector<double> poly_sub_vec(const std::vector<double>& a, const std::vector<double>& b) {
  const int deg = std::max(static_cast<int>(a.size()), static_cast<int>(b.size())) - 1;
  std::vector<double> out(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int k = 0; k <= deg; ++k) {
    const double av = k < static_cast<int>(a.size()) ? a[static_cast<std::size_t>(k)] : 0.0;
    const double bv = k < static_cast<int>(b.size()) ? b[static_cast<std::size_t>(k)] : 0.0;
    out[static_cast<std::size_t>(k)] = av - bv;
  }
  return poly_trim_vec(out);
}

std::vector<double> poly_mul_vec(const std::vector<double>& a, const std::vector<double>& b) {
  if (a.empty() || b.empty()) {
    return {0.0};
  }
  const int deg = static_cast<int>(a.size()) + static_cast<int>(b.size()) - 2;
  std::vector<double> out(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int i = 0; i < static_cast<int>(a.size()); ++i) {
    for (int j = 0; j < static_cast<int>(b.size()); ++j) {
      out[static_cast<std::size_t>(i + j)] +=
          a[static_cast<std::size_t>(i)] * b[static_cast<std::size_t>(j)];
    }
  }
  return poly_trim_vec(out);
}

std::vector<double> poly_compose_vec(const std::vector<double>& outer,
                                     const std::vector<double>& inner) {
  if (outer.empty()) {
    return {0.0};
  }
  std::vector<double> out{0.0};
  std::vector<double> power{1.0};
  for (int k = 0; k < static_cast<int>(outer.size()); ++k) {
    if (outer[static_cast<std::size_t>(k)] != 0.0) {
      std::vector<double> scaled(power.size());
      for (std::size_t i = 0; i < power.size(); ++i) {
        scaled[i] = power[i] * outer[static_cast<std::size_t>(k)];
      }
      out = poly_add_vec(out, scaled);
    }
    power = poly_mul_vec(power, inner);
  }
  return poly_trim_vec(out);
}

CompiledPolynomial collision_difference_t(const CompiledPolynomial& curve_y,
                                          const BallisticInit& init) {
  const std::vector<double> x_of_t = {init.x0, init.vx};
  std::vector<double> curve_vec(static_cast<std::size_t>(curve_y.degree) + 1);
  for (int k = 0; k <= curve_y.degree; ++k) {
    curve_vec[static_cast<std::size_t>(k)] = curve_y.coeffs[static_cast<std::size_t>(k)];
  }
  const std::vector<double> y_curve_t = poly_compose_vec(curve_vec, x_of_t);
  const std::vector<double> y_ball_t = {init.y0, init.vy, -0.5 * init.g};
  return compile_polynomial(poly_sub_vec(y_curve_t, y_ball_t));
}

BallCollisionStep step_ball_next_collision_time(const CompiledPolynomial& curve_y,
                                                const BallisticInit& init, double x_max) {
  BallCollisionStep out{};
  if (init.vx == 0.0) {
    return out;
  }
  CompiledPolynomial diff = collision_difference_t(curve_y, init);
  const double t_depart = std::nextafter(0.0, std::numeric_limits<double>::infinity());
  double t_lo = 0.0;
  const double diff_at_depart = eval(diff, 0.0);
  if (diff_at_depart == 0.0 || std::abs(diff_at_depart) <= 1e-14) {
    diff = deflate_linear_root(diff, 0.0);
    t_lo = t_depart;
  }
  constexpr double kTimeHorizonPad = 1.0;
  const double t_flight = ballistic_ground_time_upper(init);
  const double kTimeHorizonMax = std::max(t_flight * 2.0, t_flight + kTimeHorizonPad);
  double scan_window = t_flight;
  const double initial_scan_window = scan_window;
  for (int attempt = 0; attempt < 8; ++attempt) {
    if (t_lo >= kTimeHorizonMax) {
      return out;
    }
    RootBracket bracket{};
    double scan_hi = t_lo;
    while (scan_hi < kTimeHorizonMax) {
      scan_hi = std::min(kTimeHorizonMax, t_lo + scan_window);
      const int nseg = time_scan_segments(t_lo, scan_hi, t_flight);
      bracket = vca_isolate_smallest_root(diff, t_lo, scan_hi, nseg);
      if (bracket.found || scan_hi >= kTimeHorizonMax) {
        break;
      }
      scan_window = std::min(scan_window * 2.0, kTimeHorizonMax - t_lo);
    }
    if (!bracket.found) {
      return out;
    }
    const BallisticParabola arc = ballistic_parabola_px(init);
    CompiledPolynomial diff_x = collision_difference_x(curve_y, arc);
    const double x_lo = init.x0 + init.vx * bracket.lo;
    const double x_hi = init.x0 + init.vx * bracket.hi;
    const double x_a = std::min(x_lo, x_hi);
    const double x_b = std::max(x_lo, x_hi);
    out.found = true;
    out.x = vca_refine_root_x(diff_x, x_a, x_b);
    out.t = (out.x - init.x0) / init.vx;
    if (out.t <= t_lo) {
      if (eval(diff_x, out.x) == 0.0) {
        diff = deflate_linear_root(diff, out.t);
        t_lo = std::nextafter(out.t, std::numeric_limits<double>::infinity());
        out = BallCollisionStep{};
        continue;
      }
      return out;
    }
    const double x_hit = out.x;
    if (x_hit > x_max + 1e-12 || x_hit < -x_max - 1e-12) {
      if (eval(diff_x, x_hit) == 0.0) {
        diff = deflate_linear_root(diff, out.t);
      }
      t_lo = std::nextafter(out.t, std::numeric_limits<double>::infinity());
      out = BallCollisionStep{};
      continue;
    }
    out.y = curve_y_at_x(curve_y, out.x);
    out.root_path = (attempt > 0 || scan_window > initial_scan_window + 1e-15)
                        ? CollisionRootPath::TimeFineScan
                        : CollisionRootPath::TimeFallback;
    const double vy_contact = init.vy - init.g * out.t;
    out.impact_speed = normal_impact_speed(curve_y, out.x, init.vx, vy_contact);
    out.accepted = out.impact_speed >= kVGraze;
    return out;
  }
  return out;
}

BallCollisionStep step_ball_next_collision_x(const CompiledPolynomial& curve_y,
                                             const BallisticInit& init, double x_min,
                                             double x_max) {
  BallCollisionStep out{};
  if (init.vx == 0.0) {
    return out;
  }
  const BallisticParabola arc = ballistic_parabola_px(init);
  CompiledPolynomial diff = collision_difference_x(curve_y, arc);
  if (eval(diff, init.x0) == 0.0) {
    diff = deflate_linear_root(diff, init.x0);
  }
  const double depart_x = strict_departure_x_min(init.x0, init.vx, x_max);
  double search_lo = 0.0;
  double search_hi = 0.0;
  const double x_phys = x_reachable_upper(init, x_max);
  if (init.vx > 0.0) {
    search_lo = std::max(x_min, depart_x);
    search_hi = x_max > 1e5 ? std::min(x_max, std::max(x_phys, search_lo)) : x_max;
  } else {
    search_hi = std::min(x_min, depart_x);
    search_lo = x_max > 1e5 ? std::max(-x_max, std::min(x_phys, search_hi)) : -x_max;
  }
  for (int attempt = 0; attempt < 8; ++attempt) {
    if (search_hi <= search_lo) {
      return out;
    }
    const RootBracket bracket =
        init.vx > 0.0 ? vca_isolate_smallest_root(diff, search_lo, search_hi)
                      : vca_isolate_largest_root(diff, search_lo, search_hi);
    if (!bracket.found) {
      return out;
    }
    out.found = true;
    out.x = vca_refine_root_x(diff, bracket.lo, bracket.hi);
    out.t = (out.x - init.x0) / init.vx;
    out.root_path = CollisionRootPath::XPrimary;
    const bool depart_rehit =
        init.vx > 0.0 ? out.x <= depart_x : out.x >= depart_x;
    if (out.t <= 0.0 || depart_rehit) {
      if (eval(diff, out.x) == 0.0) {
        diff = deflate_linear_root(diff, out.x);
        if (init.vx > 0.0) {
          search_lo = strict_departure_x_min(out.x, init.vx, x_max);
        } else {
          search_hi = strict_departure_x_min(out.x, init.vx, x_max);
        }
        out = BallCollisionStep{};
        continue;
      }
      out.found = false;
      return out;
    }
    out.y = curve_y_at_x(curve_y, out.x);
    const double vy_contact = init.vy - init.g * out.t;
    out.impact_speed = normal_impact_speed(curve_y, out.x, init.vx, vy_contact);
    out.accepted = out.impact_speed >= kVGraze;
    if (!out.accepted) {
      if (eval(diff, out.x) == 0.0) {
        diff = deflate_linear_root(diff, out.x);
      }
      if (init.vx > 0.0) {
        search_lo = strict_departure_x_min(out.x, init.vx, x_max);
      } else {
        search_hi = strict_departure_x_min(out.x, init.vx, x_max);
      }
      out = BallCollisionStep{};
      continue;
    }
    break;
  }
  if (!out.found) {
    return out;
  }
  if (out.root_path == CollisionRootPath::None) {
    out.root_path = CollisionRootPath::XPrimary;
  }
  return out;
}

BallCollisionStep step_ball_next_collision(const CompiledPolynomial& curve_y,
                                             const BallisticInit& init, double x_min,
                                             double x_max) {
  BallCollisionStep out =
      step_ball_next_collision_x(curve_y, init, x_min, x_max);
  if (!out.found) {
    out = step_ball_next_collision_time(curve_y, init, x_max);
  }
  return out;
}

} // namespace bounce::core::engine

// Bezier collision (Y(s) - P(X(s)) = 0) appended in same translation unit below.

namespace bounce::core::engine {

namespace {

using bounce::core::curve::BezierKind;
using bounce::core::curve::CompiledBezierSegment;
using bounce::core::curve::CompiledPiecewiseBezier;
using bounce::core::curve::compile_polynomial;
using bounce::core::curve::CompiledPolynomial;
using bounce::core::curve::eval;
using bounce::core::curve::normal;
using bounce::core::curve::Vec2;

constexpr double kBezierDomainEps = 1e-12;

bool bezier_y_at_x(const CompiledBezierSegment& segment, double x_target, double& y_out,
                   double& s_out);

double strict_departure_s_min(double s_dep) {
  return std::nextafter(s_dep, 1.0);
}

bool contact_s_on_segment(const CompiledBezierSegment& segment, const BallisticInit& init,
                          double& s_out) {
  double y_at_s = 0.0;
  if (!bezier_y_at_x(segment, init.x0, y_at_s, s_out)) {
    return false;
  }
  return std::abs(y_at_s - init.y0) <= kBezierDomainEps;
}

std::vector<double> bezier_axis_poly(const CompiledBezierSegment& segment, bool y_axis) {
  if (segment.kind == BezierKind::Quadratic) {
    const double p0 = y_axis ? segment.control[0].y : segment.control[0].x;
    const double p1 = y_axis ? segment.control[1].y : segment.control[1].x;
    const double p2 = y_axis ? segment.control[2].y : segment.control[2].x;
    return {p0, 2.0 * (p1 - p0), p0 - 2.0 * p1 + p2};
  }
  const double p0 = y_axis ? segment.control[0].y : segment.control[0].x;
  const double p1 = y_axis ? segment.control[1].y : segment.control[1].x;
  const double p2 = y_axis ? segment.control[2].y : segment.control[2].x;
  const double p3 = y_axis ? segment.control[3].y : segment.control[3].x;
  return {p0, 3.0 * (p1 - p0), 3.0 * (p0 - 2.0 * p1 + p2), -p0 + 3.0 * p1 - 3.0 * p2 + p3};
}

std::vector<double> poly_trim(const std::vector<double>& p) {
  int deg = static_cast<int>(p.size()) - 1;
  while (deg > 0 && p[static_cast<std::size_t>(deg)] == 0.0) {
    --deg;
  }
  return std::vector<double>(p.begin(), p.begin() + deg + 1);
}

std::vector<double> poly_add(const std::vector<double>& a, const std::vector<double>& b) {
  const int deg = std::max(static_cast<int>(a.size()), static_cast<int>(b.size())) - 1;
  std::vector<double> out(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int k = 0; k <= deg; ++k) {
    const double av = k < static_cast<int>(a.size()) ? a[static_cast<std::size_t>(k)] : 0.0;
    const double bv = k < static_cast<int>(b.size()) ? b[static_cast<std::size_t>(k)] : 0.0;
    out[static_cast<std::size_t>(k)] = av + bv;
  }
  return poly_trim(out);
}

std::vector<double> poly_sub(const std::vector<double>& a, const std::vector<double>& b) {
  const int deg = std::max(static_cast<int>(a.size()), static_cast<int>(b.size())) - 1;
  std::vector<double> out(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int k = 0; k <= deg; ++k) {
    const double av = k < static_cast<int>(a.size()) ? a[static_cast<std::size_t>(k)] : 0.0;
    const double bv = k < static_cast<int>(b.size()) ? b[static_cast<std::size_t>(k)] : 0.0;
    out[static_cast<std::size_t>(k)] = av - bv;
  }
  return poly_trim(out);
}

std::vector<double> poly_mul(const std::vector<double>& a, const std::vector<double>& b) {
  if (a.empty() || b.empty()) {
    return {0.0};
  }
  const int deg = static_cast<int>(a.size()) + static_cast<int>(b.size()) - 2;
  std::vector<double> out(static_cast<std::size_t>(deg) + 1, 0.0);
  for (int i = 0; i < static_cast<int>(a.size()); ++i) {
    for (int j = 0; j < static_cast<int>(b.size()); ++j) {
      out[static_cast<std::size_t>(i + j)] +=
          a[static_cast<std::size_t>(i)] * b[static_cast<std::size_t>(j)];
    }
  }
  return poly_trim(out);
}

std::vector<double> poly_compose(const std::vector<double>& outer,
                                 const std::vector<double>& inner) {
  if (outer.empty()) {
    return {0.0};
  }
  std::vector<double> out{0.0};
  std::vector<double> power{1.0};
  for (int k = 0; k < static_cast<int>(outer.size()); ++k) {
    if (outer[static_cast<std::size_t>(k)] != 0.0) {
      std::vector<double> scaled(power.size());
      for (std::size_t i = 0; i < power.size(); ++i) {
        scaled[i] = power[i] * outer[static_cast<std::size_t>(k)];
      }
      out = poly_add(out, scaled);
    }
    power = poly_mul(power, inner);
  }
  return poly_trim(out);
}

CompiledPolynomial to_compiled_poly(const std::vector<double>& coeffs) {
  return compile_polynomial(coeffs);
}

bool x_admissible(double x, double x_min, double x_max, double vx) {
  if (vx > 0.0) {
    return x >= x_min - kBezierDomainEps && x <= x_max + kBezierDomainEps;
  }
  if (vx < 0.0) {
    return x <= x_min + kBezierDomainEps && x >= x_max - kBezierDomainEps;
  }
  return false;
}

double bezier_normal_impact_speed(const CompiledBezierSegment& segment, double s, double vx,
                                  double vy) {
  const auto n = normal(segment, s);
  const double vn = vx * n.nx + vy * n.ny;
  return std::abs(vn);
}

std::vector<double> poly_roots_in_interval(const CompiledPolynomial& q, double lo, double hi) {
  std::vector<double> roots;
  if (q.degree < 1 || hi <= lo) {
    return roots;
  }
  const int nseg = std::max(32, q.degree * 16);
  const double step = (hi - lo) / static_cast<double>(nseg);
  double prev_x = lo;
  double prev_v = eval(q, prev_x);
  if (prev_v == 0.0) {
    roots.push_back(prev_x);
  }
  for (int i = 1; i <= nseg; ++i) {
    const double x = lo + step * static_cast<double>(i);
    const double v = eval(q, x);
    if (v == 0.0) {
      roots.push_back(x);
    } else if (prev_v * v < 0.0) {
      RootBracket bracket{};
      bracket.found = true;
      bracket.lo = prev_x;
      bracket.hi = x;
      roots.push_back(vca_refine_root_x(q, bracket.lo, bracket.hi));
    }
    prev_x = x;
    prev_v = v;
  }
  return roots;
}

CompiledPolynomial deflate_bezier_departure_s_aliases(const CompiledBezierSegment& segment,
                                                      CompiledPolynomial diff, double x0) {
  auto x_poly_vec = bezier_axis_poly(segment, false);
  if (!x_poly_vec.empty()) {
    x_poly_vec[0] -= x0;
  }
  const auto x_diff = to_compiled_poly(poly_trim(x_poly_vec));
  const auto x_roots = poly_roots_in_interval(x_diff, 0.0, 1.0);
  for (double s_root : x_roots) {
    const double d = eval(diff, s_root);
    if (d == 0.0 || std::abs(d) <= 1e-14) {
      diff = deflate_linear_root(diff, s_root);
    }
  }
  return diff;
}

bool collision_less(double t_a, int seg_a, double t_b, int seg_b) {
  if (t_a != t_b) {
    return t_a < t_b;
  }
  return seg_a < seg_b;
}

struct BezierSegmentCollisionDiff {
  CompiledPolynomial work_diff{};
  double s_lo = 0.0;
  double s_hi = 1.0;
};

BezierSegmentCollisionDiff bezier_segment_collision_diff(const CompiledBezierSegment& segment,
                                                       const BallisticInit& init,
                                                       int depart_segment_index,
                                                       int segment_index, double depart_s) {
  BezierSegmentCollisionDiff out{};
  const BallisticParabola arc = ballistic_parabola_px(init);
  const auto x_poly_vec = bezier_axis_poly(segment, false);
  const auto y_poly = bezier_axis_poly(segment, true);
  std::vector<double> arc_coeffs(static_cast<std::size_t>(arc.poly.degree) + 1);
  for (int k = 0; k <= arc.poly.degree; ++k) {
    arc_coeffs[static_cast<std::size_t>(k)] = arc.poly.coeffs[static_cast<std::size_t>(k)];
  }
  const auto composed = poly_compose(arc_coeffs, x_poly_vec);
  const auto diff_coeffs = poly_sub(y_poly, composed);
  out.work_diff = to_compiled_poly(diff_coeffs);
  out.s_lo = 0.0;
  out.s_hi = 1.0;
  auto apply_depart = [&](double s_depart) {
    const double diff_at = eval(out.work_diff, s_depart);
    if (diff_at == 0.0 || std::abs(diff_at) <= 1e-14) {
      out.work_diff = deflate_linear_root(out.work_diff, s_depart);
    }
    const Vec2 p0 = eval(segment, 0.0);
    const Vec2 p1 = eval(segment, 1.0);
    const bool x_increases = p1.x >= p0.x;
    if (init.vx > 0.0) {
      if (x_increases) {
        out.s_lo = std::max(out.s_lo, strict_departure_s_min(s_depart));
      } else {
        out.s_hi = std::min(out.s_hi, std::nextafter(s_depart, 0.0));
      }
    } else if (init.vx < 0.0) {
      if (x_increases) {
        out.s_hi = std::min(out.s_hi, std::nextafter(s_depart, 0.0));
      } else {
        out.s_lo = std::max(out.s_lo, strict_departure_s_min(s_depart));
      }
    }
  };
  if (depart_segment_index == segment_index && depart_s >= 0.0 && depart_s <= 1.0) {
    apply_depart(depart_s);
  } else {
    double s_depart = 0.0;
    if (contact_s_on_segment(segment, init, s_depart)) {
      apply_depart(s_depart);
    } else {
      const double diff_at_zero = eval(out.work_diff, 0.0);
      if (diff_at_zero == 0.0 || std::abs(diff_at_zero) <= 1e-14) {
        apply_depart(0.0);
      }
    }
  }
  out.work_diff = deflate_bezier_departure_s_aliases(segment, out.work_diff, init.x0);
  return out;
}

BallCollisionStep step_ball_next_collision_segment(const CompiledBezierSegment& segment,
                                                   int segment_index, const BallisticInit& init,
                                                   double x_min, double x_max,
                                                   int depart_segment_index, double depart_s) {
  BallCollisionStep out{};
  if (init.vx == 0.0) {
    return out;
  }
  const double x_lo = init.vx > 0.0 ? x_min : x_max;
  const double x_hi = init.vx > 0.0 ? x_max : x_min;
  const double depart_x = strict_departure_x_min(init.x0, init.vx, x_hi);
  const double x_refine_tol =
      std::ldexp(std::max({std::abs(x_max), std::abs(x_min), std::abs(init.x0), 1.0}),
                 -kBisectBits);
  const double t_min = x_refine_tol / std::abs(init.vx);
  auto seg_diff =
      bezier_segment_collision_diff(segment, init, depart_segment_index, segment_index, depart_s);

  auto advance_s_bound = [&](double s_root) {
    const Vec2 p0 = eval(segment, 0.0);
    const Vec2 p1 = eval(segment, 1.0);
    const bool x_increases = p1.x >= p0.x;
    if (init.vx > 0.0) {
      if (x_increases) {
        seg_diff.s_lo = std::max(seg_diff.s_lo, strict_departure_s_min(s_root));
      } else {
        seg_diff.s_hi = std::min(seg_diff.s_hi, std::nextafter(s_root, 0.0));
      }
    } else if (init.vx < 0.0) {
      if (x_increases) {
        seg_diff.s_hi = std::min(seg_diff.s_hi, std::nextafter(s_root, 0.0));
      } else {
        seg_diff.s_lo = std::max(seg_diff.s_lo, strict_departure_s_min(s_root));
      }
    }
  };

  for (int attempt = 0; attempt < 16; ++attempt) {
    if (seg_diff.s_hi <= seg_diff.s_lo) {
      return out;
    }
    const auto roots =
        poly_roots_in_interval(seg_diff.work_diff, seg_diff.s_lo, seg_diff.s_hi);
    BallCollisionStep best{};
    double ghost_s = -1.0;
    for (double s_root : roots) {
      const Vec2 pos = eval(segment, s_root);
      if (pos.x + kBezierDomainEps < x_lo || pos.x - kBezierDomainEps > x_hi) {
        continue;
      }
      if (init.vx > 0.0 && pos.x < x_min - kBezierDomainEps) {
        continue;
      }
      if (init.vx < 0.0 && pos.x > x_min + kBezierDomainEps) {
        continue;
      }
      const double t = (pos.x - init.x0) / init.vx;
      const bool depart_rehit =
          t <= t_min || (init.vx > 0.0 ? pos.x <= depart_x : pos.x >= depart_x);
      if (depart_rehit) {
        ghost_s = s_root;
        continue;
      }
      const double vy_contact = init.vy - init.g * t;
      const double impact = bezier_normal_impact_speed(segment, s_root, init.vx, vy_contact);
      BallCollisionStep candidate{};
      candidate.found = true;
      candidate.segment_index = segment_index;
      candidate.segment_s = s_root;
      candidate.x = pos.x;
      candidate.y = pos.y;
      candidate.t = t;
      candidate.impact_speed = impact;
      candidate.accepted = impact >= kVGraze;
      candidate.root_path = CollisionRootPath::BezierSParam;
      if (!best.found || collision_less(candidate.t, candidate.segment_index, best.t,
                                        best.segment_index)) {
        best = candidate;
      }
    }
    if (!best.found) {
      if (ghost_s >= 0.0) {
        if (eval(seg_diff.work_diff, ghost_s) == 0.0 ||
            std::abs(eval(seg_diff.work_diff, ghost_s)) <= 1e-14) {
          seg_diff.work_diff = deflate_linear_root(seg_diff.work_diff, ghost_s);
        }
        advance_s_bound(ghost_s);
        continue;
      }
      return out;
    }
    if (!best.accepted) {
      if (eval(seg_diff.work_diff, best.segment_s) == 0.0 ||
          std::abs(eval(seg_diff.work_diff, best.segment_s)) <= 1e-14) {
        seg_diff.work_diff = deflate_linear_root(seg_diff.work_diff, best.segment_s);
      }
      advance_s_bound(best.segment_s);
      continue;
    }
    return best;
  }
  return out;
}

bool bezier_y_at_x(const CompiledBezierSegment& segment, double x_target, double& y_out,
                   double& s_out) {
  const Vec2 p0 = eval(segment, 0.0);
  const Vec2 p1 = eval(segment, 1.0);
  const double x_lo = std::min(p0.x, p1.x);
  const double x_hi = std::max(p0.x, p1.x);
  if (x_target < x_lo - kBezierDomainEps || x_target > x_hi + kBezierDomainEps) {
    return false;
  }
  double lo = 0.0;
  double hi = 1.0;
  double x_lo_s = p0.x;
  for (int i = 0; i < 80; ++i) {
    const double mid = 0.5 * (lo + hi);
    const double xm = eval(segment, mid).x;
    if (xm == x_target) {
      s_out = mid;
      y_out = eval(segment, mid).y;
      return true;
    }
    if ((xm - x_target) * (x_lo_s - x_target) <= 0.0) {
      hi = mid;
    } else {
      lo = mid;
      x_lo_s = xm;
    }
  }
  s_out = 0.5 * (lo + hi);
  y_out = eval(segment, s_out).y;
  return true;
}

double bezier_ball_height_diff(const CompiledPiecewiseBezier& curve, const BallisticInit& init,
                               double t) {
  const double x = init.x0 + init.vx * t;
  for (const auto& segment : curve.segments) {
    double yc = 0.0;
    double s = 0.0;
    if (bezier_y_at_x(segment, x, yc, s)) {
      return init.y0 + init.vy * t - 0.5 * init.g * t * t - yc;
    }
  }
  return 1.0;
}

double refine_scalar_root(const std::function<double(double)>& f, double lo, double hi) {
  if (lo == hi) {
    return lo;
  }
  const double scale = hi - lo;
  const double target = scale * std::ldexp(1.0, -kBisectBits);
  double a = lo;
  double b = hi;
  double fa = f(a);
  double fb = f(b);
  (void)fb;
  while (b - a > target) {
    const double m = 0.5 * (a + b);
    const double fm = f(m);
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
  for (int i = 0; i < kNewtonSteps; ++i) {
    const double td = to_double(t);
    const double h = std::max(1e-12, std::abs(td) * 1e-8);
    const double ft = f(td);
    const double dft = (f(td + h) - f(td - h)) / (2.0 * h);
    if (dft == 0.0) {
      break;
    }
    t = dd_sub(t, dd_div(dd_from_double(ft), dd_from_double(dft)));
    const double tdn = to_double(t);
    if (tdn < lo) {
      t = dd_from_double(lo);
    } else if (tdn > hi) {
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

} // namespace

bool bezier_s_for_x(const CompiledBezierSegment& segment, double x_target, double& s_out) {
  double y = 0.0;
  return bezier_y_at_x(segment, x_target, y, s_out);
}

bool bezier_y_at_world_x(const CompiledPiecewiseBezier& curve, double x, double& y_out) {
  for (const auto& segment : curve.segments) {
    double s = 0.0;
    if (bezier_y_at_x(segment, x, y_out, s)) {
      return true;
    }
  }
  return false;
}

BallCollisionStep step_ball_next_collision_bezier_time(const CompiledPiecewiseBezier& curve,
                                                       const BallisticInit& init, double x_min,
                                                       double x_max) {
  BallCollisionStep out{};
  if (init.vx == 0.0) {
    return out;
  }
  const double bound_lo = std::min(x_min, x_max);
  const double bound_hi = std::max(x_min, x_max);
  const double x_refine_tol =
      std::ldexp(std::max({std::abs(bound_hi), std::abs(bound_lo), std::abs(init.x0), 1.0}),
                 -kBisectBits);
  const double t_min_sched = x_refine_tol / std::abs(init.vx);
  double t_lo = std::max(std::nextafter(0.0, std::numeric_limits<double>::infinity()), t_min_sched);
  constexpr double kTimeHorizonPad = 1.0;
  const double t_flight = ballistic_ground_time_upper(init);
  // Valley bounce periods can exceed a single ground-flight estimate; keep a padded horizon.
  const double kTimeHorizonMax =
      std::max({t_flight * 4.0, t_flight + kTimeHorizonPad, 50.0});
  double scan_window = std::max(t_flight, 1.0);
  const double initial_scan_window = scan_window;
  const double depart_x = strict_departure_x_min(init.x0, init.vx, bound_hi);
  const auto height_diff = [&](double t) { return bezier_ball_height_diff(curve, init, t); };
  for (int attempt = 0; attempt < 16; ++attempt) {
    if (t_lo >= kTimeHorizonMax) {
      return out;
    }
    double scan_hi = t_lo;
    RootBracket bracket{};
    while (scan_hi < kTimeHorizonMax) {
      scan_hi = std::min(kTimeHorizonMax, t_lo + scan_window);
      const int nseg = time_scan_segments(t_lo, scan_hi, t_flight);
      const double step = (scan_hi - t_lo) / static_cast<double>(nseg);
      double prev_t = t_lo;
      double prev_v = height_diff(prev_t);
      // Skip an exact residual at the open departure bound without treating it as a hit.
      if (prev_v == 0.0) {
        prev_t = std::nextafter(prev_t, std::numeric_limits<double>::infinity());
        prev_v = height_diff(prev_t);
      }
      bracket = RootBracket{};
      for (int i = 1; i <= nseg; ++i) {
        const double t = t_lo + step * static_cast<double>(i);
        const double v = height_diff(t);
        if (v == 0.0) {
          bracket.found = true;
          bracket.lo = t;
          bracket.hi = t;
          break;
        }
        if (prev_v * v < 0.0) {
          bracket.found = true;
          bracket.lo = prev_t;
          bracket.hi = t;
          break;
        }
        prev_t = t;
        prev_v = v;
      }
      if (bracket.found || scan_hi >= kTimeHorizonMax) {
        break;
      }
      scan_window = std::min(scan_window * 2.0, kTimeHorizonMax - t_lo);
    }
    if (!bracket.found) {
      return out;
    }
    const double t_hit = refine_scalar_root(height_diff, bracket.lo, bracket.hi);
    if (t_hit <= t_lo) {
      t_lo = std::nextafter(std::max(t_hit, t_lo), std::numeric_limits<double>::infinity());
      continue;
    }
    const double x_hit = init.x0 + init.vx * t_hit;
    if (init.vx > 0.0 ? x_hit <= depart_x : x_hit >= depart_x) {
      t_lo = std::nextafter(t_hit, std::numeric_limits<double>::infinity());
      continue;
    }
    if (x_hit < bound_lo - kBezierDomainEps || x_hit > bound_hi + kBezierDomainEps) {
      t_lo = std::nextafter(t_hit, std::numeric_limits<double>::infinity());
      continue;
    }
    int seg_idx = -1;
    double s_hit = 0.0;
    double y_hit = 0.0;
    for (std::size_t si = 0; si < curve.segments.size(); ++si) {
      if (bezier_y_at_x(curve.segments[si], x_hit, y_hit, s_hit)) {
        seg_idx = static_cast<int>(si);
        break;
      }
    }
    if (seg_idx < 0) {
      t_lo = std::nextafter(t_hit, std::numeric_limits<double>::infinity());
      continue;
    }
    out.found = true;
    out.t = t_hit;
    out.x = x_hit;
    out.y = y_hit;
    out.segment_index = seg_idx;
    out.segment_s = s_hit;
    out.root_path = (attempt > 0 || scan_window > initial_scan_window + 1e-15)
                        ? CollisionRootPath::TimeFineScan
                        : CollisionRootPath::BezierTimeFallback;
    const double vy_contact = init.vy - init.g * out.t;
    out.impact_speed =
        bezier_normal_impact_speed(curve.segments[static_cast<std::size_t>(seg_idx)], s_hit,
                                   init.vx, vy_contact);
    out.accepted = out.impact_speed >= kVGraze;
    if (!out.accepted) {
      t_lo = std::nextafter(t_hit, std::numeric_limits<double>::infinity());
      out = BallCollisionStep{};
      continue;
    }
    return out;
  }
  return out;
}

BallCollisionStep step_ball_next_collision_bezier(const CompiledPiecewiseBezier& curve,
                                                  const BallisticInit& init, double x_min,
                                                  double x_max, int depart_segment,
                                                  double depart_s) {
  (void)depart_segment;
  (void)depart_s;
  // Time-primary: s-param path still available via segment stepper for diagnostics,
  // but the live search uses the registered time scan (refsim-equivalent) so departure
  // exclusion is exact in t with the refinement-schedule floor.
  BallCollisionStep time_best =
      step_ball_next_collision_bezier_time(curve, init, x_min, x_max);
  BallCollisionStep s_best{};
  for (std::size_t i = 0; i < curve.segments.size(); ++i) {
    const BallCollisionStep step = step_ball_next_collision_segment(
        curve.segments[i], static_cast<int>(i), init, x_min, x_max, depart_segment, depart_s);
    if (!step.found) {
      continue;
    }
    if (!s_best.found ||
        collision_less(step.t, step.segment_index, s_best.t, s_best.segment_index)) {
      s_best = step;
    }
  }
  if (time_best.found) {
    return time_best;
  }
  return s_best;
}

} // namespace bounce::core::engine
