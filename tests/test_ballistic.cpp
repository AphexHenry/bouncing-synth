// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/ballistic.hpp"
#include "bounce/curve/polynomial.hpp"

#include <doctest/doctest.h>

using bounce::core::curve::eval;
using bounce::core::engine::ballistic_parabola_px;
using bounce::core::engine::BallisticInit;
using bounce::core::engine::position_at_time;

TEST_CASE("ballistic FL-1 parabola P(x) hits ground at x=1") {
  const BallisticInit init{0.0, 5.0, 1.0, 0.0, 10.0};
  const auto arc = ballistic_parabola_px(init);
  CHECK(eval(arc.poly, 0.0) == doctest::Approx(5.0));
  CHECK(eval(arc.poly, 1.0) == doctest::Approx(0.0));
  const auto pos = position_at_time(init, 1.0);
  CHECK(pos.x == doctest::Approx(1.0));
  CHECK(pos.y == doctest::Approx(0.0));
}

TEST_CASE("ballistic vx=0 rejected for P(x)") {
  const BallisticInit init{0.0, 5.0, 0.0, 0.0, 10.0};
  CHECK_THROWS_AS(ballistic_parabola_px(init), std::invalid_argument);
}
