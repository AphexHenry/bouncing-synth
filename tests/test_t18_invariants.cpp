// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/collision_sim.hpp"
#include "bounce/engine/vca.hpp"
#include "bounce/curve/polynomial.hpp"
#include "bounce/scenario/calibration_loader.hpp"

#include <doctest/doctest.h>
#include <cmath>
#include <limits>

namespace {

constexpr const char* kE4aPath =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t18/CF-E4a-wwell-e1.json";
constexpr const char* kE4bPath =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t18/CF-E4b-bezier-valley-e1.json";
constexpr const char* kE4aRef50Path =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t18/CF-E4a-wwell-e1-ref50.json";

bounce::core::engine::MultiBallSimResult run_fixture(const char* path, int max_events) {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(path, scenario));
  return bounce::core::scenario::run_calibration_scenario(scenario, max_events);
}

double energy_at_contact(double g, double y, double vx, double vy) {
  return g * y + 0.5 * (vx * vx + vy * vy);
}

constexpr int stored_events(const bounce::core::engine::MultiBallSimResult& result) {
  return std::min(result.count, static_cast<int>(bounce::core::engine::kMaxSimEvents));
}

double energy_drift_over_run(const char* path, int max_events, double& e0_out) {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(path, scenario));
  std::vector<double> coeffs(scenario.coeff_count);
  for (int i = 0; i < scenario.coeff_count; ++i) {
    coeffs[static_cast<std::size_t>(i)] = scenario.coeffs[static_cast<std::size_t>(i)];
  }
  const auto curve = bounce::core::curve::compile_polynomial(coeffs);
  bounce::core::engine::BallSpec ball = scenario.balls[0];
  const double g = ball.init.g;
  e0_out = energy_at_contact(g, ball.init.y0, ball.init.vx, ball.init.vy);
  double x_min = ball.init.x0;
  double max_rel = 0.0;
  int produced = 0;
  for (int i = 0; i < max_events; ++i) {
    const auto step = bounce::core::engine::step_ball_next_collision(
        curve, ball.init, x_min, scenario.domain_max);
    if (!step.found) {
      break;
    }
    if (!step.accepted) {
      const double vy_contact = ball.init.vy - ball.init.g * step.t;
      ball.init.x0 = step.x;
      ball.init.y0 = step.y;
      ball.init.vy = vy_contact;
      x_min = step.x;
      if (ball.init.vx > 0.0) {
        x_min = std::nextafter(step.x, std::numeric_limits<double>::infinity());
      } else if (ball.init.vx < 0.0) {
        x_min = std::nextafter(step.x, -std::numeric_limits<double>::infinity());
      }
      --i;
      continue;
    }
    const double vy_contact = ball.init.vy - ball.init.g * step.t;
    const double ek = energy_at_contact(g, step.y, ball.init.vx, vy_contact);
    max_rel = std::max(max_rel, std::abs(ek - e0_out) / e0_out);
    ++produced;
    const auto reflected = bounce::core::engine::reflect_velocity(
        curve, step.x, ball.init.vx, vy_contact, ball.restitution);
    ball.init.x0 = step.x;
    ball.init.y0 = step.y;
    ball.init.vx = reflected.vx;
    ball.init.vy = reflected.vy;
    x_min = step.x;
    if (ball.init.vx > 0.0) {
      x_min = std::nextafter(step.x, std::numeric_limits<double>::infinity());
    } else if (ball.init.vx < 0.0) {
      x_min = std::nextafter(step.x, -std::numeric_limits<double>::infinity());
    }
  }
  CHECK(produced == max_events);
  return max_rel;
}

} // namespace

TEST_CASE("T18 CF-E4a sustains 2000 confined lossless events") {
  const auto result = run_fixture(kE4aPath, 2000);
  CHECK(result.count == 2000);
}

TEST_CASE("T18 CF-E4b premature stream recorded") {
  const auto result = run_fixture(kE4bPath, 2000);
  MESSAGE("E4b events=", result.count);
  CHECK(result.count > 0);
  CHECK(result.count < 2000);
}

TEST_CASE("T18 CF-E4a per-ball times strictly increasing") {
  const auto result = run_fixture(kE4aPath, 2000);
  REQUIRE(result.count == 2000);
  const int n = stored_events(result);
  for (int i = 1; i < n; ++i) {
    const double t_prev = result.events[static_cast<std::size_t>(i - 1)].t;
    const double t_cur = result.events[static_cast<std::size_t>(i)].t;
    CHECK(t_cur > t_prev);
  }
}

TEST_CASE("T18 CF-E4a no consecutive duplicate t_hex s_hex per ball") {
  const auto result = run_fixture(kE4aPath, 2000);
  REQUIRE(result.count == 2000);
  const int n = stored_events(result);
  for (int i = 1; i < n; ++i) {
    const auto& a = result.events[static_cast<std::size_t>(i - 1)];
    const auto& b = result.events[static_cast<std::size_t>(i)];
    const bool dup = (a.t == b.t) && (a.s == b.s);
    CHECK_FALSE(dup);
  }
}

TEST_CASE("T18 CF-E4a e=1 energy drift invariant") {
  double e0 = 0.0;
  const double max_rel = energy_drift_over_run(kE4aPath, 2000, e0);
  MESSAGE("max_rel_energy_drift=", max_rel);
  CHECK(max_rel <= 1e-9);
  (void)e0;
}

TEST_CASE("T18 CF-E4a agrees with tier-2 50-event reference window") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kE4aRef50Path, scenario));
  const auto result = run_fixture(kE4aPath, scenario.ref_event_count);
  REQUIRE(result.count == scenario.ref_event_count);
  double worst_dt = 0.0;
  double worst_ds = 0.0;
  for (int i = 0; i < scenario.ref_event_count; ++i) {
    const auto& ref = scenario.reference_events[static_cast<std::size_t>(i)];
    const auto& eng = result.events[static_cast<std::size_t>(i)];
    worst_dt = std::max(worst_dt, std::abs(eng.t - ref.t));
    worst_ds = std::max(worst_ds, std::abs(eng.s - ref.contact_x));
    CHECK(eng.ball_id == ref.ball_id);
    CHECK(eng.seq == ref.seq);
  }
  MESSAGE("worst_dt=", worst_dt, " worst_ds=", worst_ds);
  CHECK(worst_dt <= 1e-9);
  CHECK(worst_ds <= 1e-9);
}
