// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/collision_sim.hpp"

#include "bounce/curve/polynomial.hpp"
#include "bounce/engine/ballistic.hpp"

#include <doctest/doctest.h>

#include <cmath>

using bounce::core::curve::compile_polynomial;
using bounce::core::engine::BallisticInit;
using bounce::core::engine::BallSpec;
using bounce::core::engine::reflect_velocity;
using bounce::core::engine::simulate_ball_collisions;
using bounce::core::engine::simulate_multi_ball_collisions;

TEST_CASE("reflect_velocity inverts normal component with restitution 0.5") {
  const auto curve = compile_polynomial({0.0});
  const auto reflected = reflect_velocity(curve, 1.0, 1.0, -10.0, 0.5);
  CHECK(reflected.vx == doctest::Approx(1.0));
  CHECK(reflected.vy == doctest::Approx(5.0));
  CHECK(reflected.normal_speed_out == doctest::Approx(10.0));
}

TEST_CASE("simulate FL-1 produces eight tier-1 event times") {
  const auto curve = compile_polynomial({0.0});
  const BallisticInit init{0.0, 5.0, 1.0, 0.0, 10.0};
  const auto result = simulate_ball_collisions(curve, init, 0.5, 100.0, 8);
  CHECK(result.count == 8);
  CHECK_FALSE(result.settled);
  const double expected[8] = {1.0, 2.0, 2.5, 2.75, 2.875, 2.9375, 2.96875, 2.984375};
  for (int i = 0; i < 8; ++i) {
    CHECK(result.events[static_cast<std::size_t>(i)].t ==
          doctest::Approx(expected[i]).epsilon(1e-12));
    CHECK(result.events[static_cast<std::size_t>(i)].s ==
          doctest::Approx(expected[i]).epsilon(1e-12));
    CHECK(result.events[static_cast<std::size_t>(i)].seq == i);
    CHECK(result.events[static_cast<std::size_t>(i)].schema_version == 1);
  }
}

TEST_CASE("simulate stops at max_events") {
  const auto curve = compile_polynomial({0.0});
  const BallisticInit init{0.0, 5.0, 1.0, 0.0, 10.0};
  const auto result = simulate_ball_collisions(curve, init, 0.5, 100.0, 3);
  CHECK(result.count == 3);
  CHECK(result.events[0].t == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(result.events[1].t == doctest::Approx(2.0).epsilon(1e-12));
  CHECK(result.events[2].t == doctest::Approx(2.5).epsilon(1e-12));
}

TEST_CASE("S-1 settle triggers when post-bounce normal speed below kVSettle") {
  const auto curve = compile_polynomial({0.0});
  const auto reflected = reflect_velocity(curve, 1.0, 1.0, -1e-12, 1.0);
  CHECK(reflected.normal_speed_out < bounce::core::engine::kVSettle);
}

TEST_CASE("PB-1 first contact matches tier-1 reference") {
  const auto curve = compile_polynomial({0.0, 0.0, 1.0});
  const BallisticInit init{0.0, 9.0, 1.0, 0.0, 16.0};
  const auto result = simulate_ball_collisions(curve, init, 0.5, 100.0, 1, 0);
  CHECK(result.count == 1);
  const auto& event = result.events[0];
  CHECK(event.t == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(event.s == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(event.ball_id == 0);
  CHECK(event.seq == 0);
  CHECK(event.schema_version == 1);
  CHECK(event.impact_speed > 0.0);
  const double inv_sqrt5 = 1.0 / std::sqrt(5.0);
  CHECK(event.normal_x == doctest::Approx(-2.0 * inv_sqrt5));
  CHECK(event.normal_y == doctest::Approx(inv_sqrt5));
}

TEST_CASE("CollisionEvent normal is unit length") {
  const auto curve = compile_polynomial({0.0, 0.0, 1.0});
  const BallisticInit init{0.0, 9.0, 1.0, 0.0, 16.0};
  const auto result = simulate_ball_collisions(curve, init, 0.5, 100.0, 1, 0);
  const auto& event = result.events[0];
  const double norm_len =
      std::sqrt(event.normal_x * event.normal_x + event.normal_y * event.normal_y);
  CHECK(norm_len == doctest::Approx(1.0).epsilon(1e-12));
}

TEST_CASE("TB-1 tie-break prefers lower ball_id at equal event time") {
  const auto curve = compile_polynomial({0.0});
  const BallSpec balls[2] = {
      {0, {0.0, 5.0, 1.0, 0.0, 10.0}, 0.5},
      {1, {2.0, 5.0, 1.0, 0.0, 10.0}, 0.5},
  };
  const auto result = simulate_multi_ball_collisions(curve, balls, 2, 100.0, 2);
  CHECK(result.count == 2);
  CHECK(result.events[0].t == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(result.events[0].ball_id == 0);
  CHECK(result.events[0].s == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(result.events[0].seq == 0);
  CHECK(result.events[1].t == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(result.events[1].ball_id == 1);
  CHECK(result.events[1].s == doctest::Approx(3.0).epsilon(1e-12));
  CHECK(result.events[1].seq == 1);
}

TEST_CASE("TB-1 global queue picks earliest collision time") {
  const auto curve = compile_polynomial({0.0});
  const BallSpec balls[2] = {
      {1, {0.0, 12.5, 0.5, 0.0, 10.0}, 0.5},
      {0, {0.0, 5.0, 1.0, 0.0, 10.0}, 0.5},
  };
  const auto result = simulate_multi_ball_collisions(curve, balls, 2, 100.0, 2);
  CHECK(result.count == 2);
  CHECK(result.events[0].t == doctest::Approx(1.0).epsilon(1e-12));
  CHECK(result.events[0].ball_id == 0);
  CHECK(result.events[1].t == doctest::Approx(std::sqrt(2.5)).epsilon(1e-12));
  CHECK(result.events[1].ball_id == 1);
}

TEST_CASE("multi-ball monotone seq assignment") {
  const auto curve = compile_polynomial({0.0});
  const BallSpec balls[2] = {
      {0, {0.0, 5.0, 1.0, 0.0, 10.0}, 0.5},
      {1, {2.0, 5.0, 1.0, 0.0, 10.0}, 0.5},
  };
  const auto result = simulate_multi_ball_collisions(curve, balls, 2, 100.0, 4);
  CHECK(result.count == 4);
  for (int i = 0; i < result.count; ++i) {
    CHECK(result.events[static_cast<std::size_t>(i)].seq == i);
    if (i > 0) {
      const auto& prev = result.events[static_cast<std::size_t>(i - 1)];
      const auto& cur = result.events[static_cast<std::size_t>(i)];
      if (cur.t == prev.t) {
        CHECK(cur.ball_id > prev.ball_id);
      } else {
        CHECK(cur.t > prev.t);
      }
    }
  }
}
