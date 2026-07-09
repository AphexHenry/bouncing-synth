// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/curve/polynomial.hpp"

#include <cmath>
#include <stdexcept>

namespace bounce::core::curve {

CompiledPolynomial compile_polynomial(const std::vector<double>& coeffs) {
  if (coeffs.empty()) {
    throw std::invalid_argument("polynomial requires at least one coefficient");
  }
  if (coeffs.size() > CompiledPolynomial::kMaxDegree + 1) {
    throw std::invalid_argument("polynomial degree exceeds 8");
  }
  CompiledPolynomial out{};
  for (std::size_t i = 0; i < coeffs.size(); ++i) {
    out.coeffs[i] = coeffs[i];
  }
  int deg = static_cast<int>(coeffs.size()) - 1;
  while (deg > 0 && out.coeffs[static_cast<std::size_t>(deg)] == 0.0) {
    --deg;
  }
  out.degree = deg;
  return out;
}

double eval(const CompiledPolynomial& p, double x) {
  double acc = 0.0;
  for (int k = p.degree; k >= 0; --k) {
    acc = acc * x + p.coeffs[static_cast<std::size_t>(k)];
  }
  return acc;
}

double deriv(const CompiledPolynomial& p, double x) {
  if (p.degree < 1) {
    return 0.0;
  }
  double acc = 0.0;
  for (int k = p.degree; k >= 1; --k) {
    acc = acc * x + static_cast<double>(k) * p.coeffs[static_cast<std::size_t>(k)];
  }
  return acc;
}

UnitNormal normal(const CompiledPolynomial& p, double x) {
  const double dp = deriv(p, x);
  const double nx = -dp;
  const double ny = 1.0;
  const double len = std::sqrt(nx * nx + ny * ny);
  return {nx / len, ny / len};
}

} // namespace bounce::core::curve
