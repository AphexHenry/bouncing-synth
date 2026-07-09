// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/curve/polynomial.hpp"

#include <doctest/doctest.h>

#include <cmath>

using bounce::core::curve::compile_polynomial;
using bounce::core::curve::deriv;
using bounce::core::curve::eval;
using bounce::core::curve::normal;

TEST_CASE("polynomial flat line y=0") {
  const auto p = compile_polynomial({0.0});
  CHECK(eval(p, 1.0) == doctest::Approx(0.0));
  CHECK(deriv(p, 1.0) == doctest::Approx(0.0));
  const auto n = normal(p, 1.0);
  CHECK(n.nx == doctest::Approx(0.0));
  CHECK(n.ny == doctest::Approx(1.0));
}

TEST_CASE("polynomial parabola y=x^2") {
  const auto p = compile_polynomial({0.0, 0.0, 1.0});
  CHECK(eval(p, 1.0) == doctest::Approx(1.0));
  CHECK(deriv(p, 1.0) == doctest::Approx(2.0));
  const auto n = normal(p, 1.0);
  const double inv_sqrt5 = 1.0 / std::sqrt(5.0);
  CHECK(n.nx == doctest::Approx(-2.0 * inv_sqrt5));
  CHECK(n.ny == doctest::Approx(inv_sqrt5));
}
