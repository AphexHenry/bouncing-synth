// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/curve/bezier.hpp"

#include <doctest/doctest.h>

using bounce::core::curve::compile_cubic_bezier;
using bounce::core::curve::compile_piecewise_bezier;
using bounce::core::curve::compile_quadratic_bezier;
using bounce::core::curve::deriv;
using bounce::core::curve::eval;
using bounce::core::curve::normal;
using bounce::core::curve::validate_c1;

TEST_CASE("quadratic bezier eval at midpoint") {
  const auto seg = compile_quadratic_bezier({0.0, 0.0}, {1.0, 2.0}, {2.0, 0.0});
  const auto p = eval(seg, 0.5);
  CHECK(p.x == doctest::Approx(1.0));
  CHECK(p.y == doctest::Approx(1.0));
  const auto d = deriv(seg, 0.5);
  CHECK(d.x == doctest::Approx(2.0));
  CHECK(d.y == doctest::Approx(0.0));
}

TEST_CASE("cubic bezier endpoint") {
  const auto seg = compile_cubic_bezier({0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0});
  const auto p0 = eval(seg, 0.0);
  CHECK(p0.x == doctest::Approx(0.0));
  CHECK(p0.y == doctest::Approx(0.0));
  const auto p1 = eval(seg, 1.0);
  CHECK(p1.x == doctest::Approx(1.0));
  CHECK(p1.y == doctest::Approx(0.0));
  const auto n = normal(seg, 0.5);
  CHECK((n.nx * n.nx + n.ny * n.ny) == doctest::Approx(1.0));
}

TEST_CASE("piecewise quadratic C1 passes validator") {
  const auto seg0 = compile_quadratic_bezier({0.0, 2.0}, {1.0, 0.0}, {2.0, 0.0});
  const auto seg1 = compile_quadratic_bezier({2.0, 0.0}, {3.0, 0.0}, {4.0, 2.0});
  const auto curve = compile_piecewise_bezier({seg0, seg1});
  const auto result = validate_c1(curve);
  CHECK(result.ok);
  CHECK(result.joint_index == -1);
}

TEST_CASE("piecewise quadratic kink fails C1 validator") {
  const auto seg0 = compile_quadratic_bezier({0.0, 2.0}, {1.0, 0.0}, {2.0, 0.0});
  const auto seg1 = compile_quadratic_bezier({2.0, 0.0}, {3.0, 1.0}, {4.0, 2.0});
  const auto curve = compile_piecewise_bezier({seg0, seg1});
  const auto result = validate_c1(curve);
  CHECK_FALSE(result.ok);
  CHECK(result.joint_index == 0);
}
