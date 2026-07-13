// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/collision_sim.hpp"
#include "bounce/scenario/calibration_loader.hpp"

#include <doctest/doctest.h>

TEST_CASE("capacity lift: >64 events reached with monotone seq") {
  bounce::core::scenario::CalibrationScenario scenario{};
  scenario.coeff_count = 1;
  scenario.coeffs[0] = 0.0;
  scenario.domain_min = 0.0;
  scenario.domain_max = 1000000.0;
  scenario.ball_count = 1;
  scenario.balls[0].ball_id = 0;
  scenario.balls[0].init.x0 = 0.0;
  scenario.balls[0].init.y0 = 5.0;
  scenario.balls[0].init.vx = 0.1;
  scenario.balls[0].init.vy = 0.0;
  scenario.balls[0].init.g = 10.0;
  scenario.balls[0].restitution = 0.999;
  scenario.ref_event_count = 1;
  scenario.reference_events[0].t = 1.0;

  constexpr int kRequestedHorizon = 100;
  static_assert(kRequestedHorizon > 64);
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, kRequestedHorizon);

  MESSAGE("scenario: flat line, restitution=0.999, vx=0.1, domain=[0,1000000], --max-events=",
          kRequestedHorizon);
  MESSAGE("events emitted: ", result.count);
  CHECK(result.count == kRequestedHorizon);
  for (int i = 0; i < result.count; ++i) {
    CHECK(result.events[static_cast<std::size_t>(i)].seq == i);
    if (i > 0) {
      CHECK(result.events[static_cast<std::size_t>(i)].t >
            result.events[static_cast<std::size_t>(i - 1)].t);
    }
  }
}

TEST_CASE("capacity lift: kMaxSimEvents is 256") {
  CHECK(bounce::core::engine::kMaxSimEvents == 256);
}
