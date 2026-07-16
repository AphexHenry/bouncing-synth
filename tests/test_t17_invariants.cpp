// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/scenario/calibration_loader.hpp"

#include <doctest/doctest.h>

#include <bit>
#include <cmath>
#include <cstring>

#ifndef BOUNCE_SOURCE_DIR
#define BOUNCE_SOURCE_DIR "."
#endif

namespace {

constexpr const char* kT17Fixtures[] = {
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t17/CF-E1-parabola-periodic.json",
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t17/CF-E2a-parabola-settle.json",
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t17/CF-E2b-poly-settle.json",
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t17/CF-E3-bezier-settle.json",
};

bool per_ball_times_strictly_increasing(const bounce::core::engine::MultiBallSimResult& result) {
  double last_t[bounce::core::engine::kMaxBalls];
  for (int i = 0; i < bounce::core::engine::kMaxBalls; ++i) {
    last_t[i] = -1.0;
  }
  for (int i = 0; i < result.count; ++i) {
    const auto& event = result.events[static_cast<std::size_t>(i)];
    if (event.ball_id < 0 || event.ball_id >= bounce::core::engine::kMaxBalls) {
      return false;
    }
    if (event.t <= last_t[event.ball_id]) {
      return false;
    }
    last_t[event.ball_id] = event.t;
  }
  return true;
}

bool no_consecutive_duplicate_contact_hex_per_ball(
    const bounce::core::engine::MultiBallSimResult& result) {
  struct LastHex {
    bool set = false;
    unsigned long long t_bits = 0;
    unsigned long long s_bits = 0;
  };
  LastHex last[bounce::core::engine::kMaxBalls]{};
  for (int i = 0; i < result.count; ++i) {
    const auto& event = result.events[static_cast<std::size_t>(i)];
    if (event.ball_id < 0 || event.ball_id >= bounce::core::engine::kMaxBalls) {
      return false;
    }
    const unsigned long long t_bits = std::bit_cast<unsigned long long>(event.t);
    const unsigned long long s_bits = std::bit_cast<unsigned long long>(event.s);
    auto& slot = last[event.ball_id];
    if (slot.set && slot.t_bits == t_bits && slot.s_bits == s_bits) {
      return false;
    }
    slot.set = true;
    slot.t_bits = t_bits;
    slot.s_bits = s_bits;
  }
  return true;
}

} // namespace

TEST_CASE("T17 CF-E1 per-ball times strictly increasing") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[0], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(per_ball_times_strictly_increasing(result));
}

TEST_CASE("T17 CF-E2a per-ball times strictly increasing") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[1], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(per_ball_times_strictly_increasing(result));
}

TEST_CASE("T17 CF-E2b per-ball times strictly increasing") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[2], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(per_ball_times_strictly_increasing(result));
}

TEST_CASE("T17 CF-E3 per-ball times strictly increasing") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[3], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(per_ball_times_strictly_increasing(result));
}

TEST_CASE("T17 CF-E1 no consecutive duplicate t_hex s_hex per ball") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[0], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(no_consecutive_duplicate_contact_hex_per_ball(result));
}

TEST_CASE("T17 CF-E2a no consecutive duplicate t_hex s_hex per ball") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[1], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(no_consecutive_duplicate_contact_hex_per_ball(result));
}

TEST_CASE("T17 CF-E2b no consecutive duplicate t_hex s_hex per ball") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[2], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(no_consecutive_duplicate_contact_hex_per_ball(result));
}

TEST_CASE("T17 CF-E3 no consecutive duplicate t_hex s_hex per ball") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kT17Fixtures[3], scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(no_consecutive_duplicate_contact_hex_per_ball(result));
}

TEST_CASE("T17 CF fixtures agree with tier-1 references within 1e-9") {
  for (const char* path : kT17Fixtures) {
    bounce::core::scenario::CalibrationScenario scenario{};
    REQUIRE(bounce::core::scenario::load_calibration_scenario(path, scenario));
    const auto result =
        bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
    CHECK(bounce::core::scenario::agrees_with_tier1_reference(scenario, result));
  }
}
