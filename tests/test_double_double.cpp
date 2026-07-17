// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/numerics/double_double.hpp"

#include <doctest/doctest.h>

#include <cmath>

using bounce::core::numerics::dd_add;
using bounce::core::numerics::dd_div;
using bounce::core::numerics::dd_from_double;
using bounce::core::numerics::dd_mul;
using bounce::core::numerics::to_double;

TEST_CASE("double-double preserves two-sum") {
  const double eps = std::ldexp(1.0, -53);
  const auto a = dd_from_double(1.0);
  const auto b = dd_from_double(eps);
  const auto sum = dd_add(a, b);
  CHECK(to_double(sum) == doctest::Approx(1.0 + eps));
}

TEST_CASE("double-double multiply") {
  const auto a = dd_from_double(3.0);
  const auto b = dd_from_double(7.0);
  CHECK(to_double(dd_mul(a, b)) == doctest::Approx(21.0));
}

TEST_CASE("double-double divide") {
  const auto a = dd_from_double(22.0);
  const auto b = dd_from_double(7.0);
  CHECK(to_double(dd_div(a, b)) == doctest::Approx(22.0 / 7.0));
}
