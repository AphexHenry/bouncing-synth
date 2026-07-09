// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <array>
#include <cstddef>
#include <vector>

namespace bounce::core::curve {

// Compiled explicit polynomial y = sum_k c[k] * x^k, ascending coefficients.
// Degree <= 8 per DELIVERABLE_B section 2.
struct CompiledPolynomial {
  static constexpr std::size_t kMaxDegree = 8;
  std::array<double, kMaxDegree + 1> coeffs{};
  int degree = 0;
};

CompiledPolynomial compile_polynomial(const std::vector<double>& coeffs);

double eval(const CompiledPolynomial& p, double x);
double deriv(const CompiledPolynomial& p, double x);

struct UnitNormal {
  double nx;
  double ny;
};

UnitNormal normal(const CompiledPolynomial& p, double x);

} // namespace bounce::core::curve
