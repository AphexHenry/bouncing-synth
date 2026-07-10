// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/vca.hpp"

#include "bounce/curve/polynomial.hpp"
#include "bounce/engine/ballistic.hpp"

#include <doctest/doctest.h>

using bounce::core::curve::compile_polynomial;
using bounce::core::curve::eval;
using bounce::core::engine::ballistic_parabola_px;
using bounce::core::engine::BallisticInit;
using bounce::core::engine::collision_difference_x;
using bounce::core::engine::vca_isolate_smallest_root;

TEST_CASE("collision difference FL-1 is zero at ground hit") {
  const auto curve = compile_polynomial({0.0});
  const auto arc = ballistic_parabola_px(BallisticInit{0.0, 5.0, 1.0, 0.0, 10.0});
  const auto diff = collision_difference_x(curve, arc);
  CHECK(eval(diff, 1.0) == doctest::Approx(0.0));
}

TEST_CASE("vca isolates FL-1 ground crossing bracket") {
  const auto curve = compile_polynomial({0.0});
  const auto arc = ballistic_parabola_px(BallisticInit{0.0, 5.0, 1.0, 0.0, 10.0});
  const auto diff = collision_difference_x(curve, arc);
  const auto bracket = vca_isolate_smallest_root(diff, 0.0, 100.0);
  CHECK(bracket.found);
  CHECK(bracket.lo <= 1.0);
  CHECK(bracket.hi >= 1.0);
}

TEST_CASE("vca finds no root when ballistic stays above curve") {
  const auto curve = compile_polynomial({10.0});
  const auto arc = ballistic_parabola_px(BallisticInit{0.0, 5.0, 1.0, 0.0, 10.0});
  const auto diff = collision_difference_x(curve, arc);
  const auto bracket = vca_isolate_smallest_root(diff, 0.0, 100.0);
  CHECK_FALSE(bracket.found);
}
