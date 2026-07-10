// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/numerics/double_double.hpp"

#include <cmath>

namespace bounce::core::numerics {

namespace {

constexpr double kSplit = 134217729.0; // 2^27 + 1

DoubleDouble quick_two_sum(double a, double b) {
  const double s = a + b;
  const double e = b - (s - a);
  return {s, e};
}

DoubleDouble two_sum(double a, double b) {
  const double s = a + b;
  const double v = s - a;
  const double e = (a - (s - v)) + (b - v);
  return {s, e};
}

void split(double a, double& hi, double& lo) {
  const double c = kSplit * a;
  hi = c - (c - a);
  lo = a - hi;
}

DoubleDouble dd_normalize(double hi, double lo) {
  const DoubleDouble s = quick_two_sum(hi, lo);
  return {s.hi, s.lo};
}

} // namespace

DoubleDouble dd_from_double(double value) {
  return {value, 0.0};
}

double to_double(const DoubleDouble& value) {
  return value.hi + value.lo;
}

DoubleDouble dd_add(const DoubleDouble& a, const DoubleDouble& b) {
  const DoubleDouble s = two_sum(a.hi, b.hi);
  const double e = a.lo + b.lo;
  return dd_normalize(s.hi, s.lo + e);
}

DoubleDouble dd_mul(const DoubleDouble& a, const DoubleDouble& b) {
  const double p = a.hi * b.hi;
  double a_hi = 0.0;
  double a_lo = 0.0;
  double b_hi = 0.0;
  double b_lo = 0.0;
  split(a.hi, a_hi, a_lo);
  split(b.hi, b_hi, b_lo);
  const double err =
      ((a_hi * b_hi - p) + a_hi * b_lo + a_lo * b_hi) + a.lo * b.hi + a.hi * b.lo;
  return dd_normalize(p, err);
}

DoubleDouble dd_div(const DoubleDouble& a, const DoubleDouble& b) {
  const double q = a.hi / b.hi;
  const DoubleDouble prod = dd_mul(dd_from_double(q), b);
  const DoubleDouble r{a.hi - prod.hi, a.lo - prod.lo};
  const double dq = to_double(r) / b.hi;
  return dd_add(dd_from_double(q), dd_from_double(dq));
}

} // namespace bounce::core::numerics
