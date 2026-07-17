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
using bounce::core::engine::kVGraze;
using bounce::core::engine::normal_impact_speed;
using bounce::core::engine::step_ball_next_collision;
using bounce::core::engine::vca_isolate_smallest_root;
using bounce::core::engine::vca_refine_root_x;

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

TEST_CASE("vca refines FL-1 root to ground hit x=1") {
  const auto curve = compile_polynomial({0.0});
  const auto arc = ballistic_parabola_px(BallisticInit{0.0, 5.0, 1.0, 0.0, 10.0});
  const auto diff = collision_difference_x(curve, arc);
  const auto bracket = vca_isolate_smallest_root(diff, 0.0, 100.0);
  REQUIRE(bracket.found);
  const double x = vca_refine_root_x(diff, bracket.lo, bracket.hi);
  CHECK(x == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(eval(diff, x) == doctest::Approx(0.0).epsilon(1e-12));
}

TEST_CASE("FL-1 normal impact speed exceeds graze threshold") {
  const auto curve = compile_polynomial({0.0});
  const BallisticInit init{0.0, 5.0, 1.0, 0.0, 10.0};
  const double speed = normal_impact_speed(curve, 1.0, init.vx, init.vy - init.g * 1.0);
  CHECK(speed > kVGraze);
}

TEST_CASE("step_ball_next_collision FL-1 accepted ground hit") {
  const auto curve = compile_polynomial({0.0});
  const BallisticInit init{0.0, 5.0, 1.0, 0.0, 10.0};
  const auto step = step_ball_next_collision(curve, init, 0.0, 100.0);
  CHECK(step.found);
  CHECK(step.accepted);
  CHECK(step.t == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(step.x == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(step.y == doctest::Approx(0.0).epsilon(1e-12));
  CHECK(step.impact_speed > kVGraze);
}

TEST_CASE("step_ball_next_collision finds no hit above curve") {
  const auto curve = compile_polynomial({10.0});
  const BallisticInit init{0.0, 5.0, 1.0, 0.0, 10.0};
  const auto step = step_ball_next_collision(curve, init, 0.0, 100.0);
  CHECK_FALSE(step.found);
  CHECK_FALSE(step.accepted);
}
