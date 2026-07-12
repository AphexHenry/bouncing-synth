// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/scenario/calibration_loader.hpp"
#include "bounce/scenario/rational.hpp"

#include <doctest/doctest.h>

#ifndef BOUNCE_SOURCE_DIR
#define BOUNCE_SOURCE_DIR "."
#endif

namespace {

constexpr const char* kFl1Path =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/FL-1-h5-g10-e1o2.json";
constexpr const char* kPb1Path =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/PB-1-h9-g16-c1.json";

constexpr const char* kTier1CalibrationCorpus[] = {kFl1Path, kPb1Path};

} // namespace

TEST_CASE("parse_rational handles integers and fractions") {
  double value = 0.0;
  CHECK(bounce::core::scenario::parse_rational("1", value));
  CHECK(value == doctest::Approx(1.0));
  CHECK(bounce::core::scenario::parse_rational("1/2", value));
  CHECK(value == doctest::Approx(0.5));
  CHECK(bounce::core::scenario::parse_rational("11/4", value));
  CHECK(value == doctest::Approx(2.75));
}

TEST_CASE("load FL-1 calibration scenario from JSON") {
  bounce::core::scenario::CalibrationScenario scenario{};
  CHECK(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  CHECK(scenario.coeff_count == 1);
  CHECK(scenario.coeffs[0] == doctest::Approx(0.0));
  CHECK(scenario.domain_max == doctest::Approx(100.0));
  CHECK(scenario.ball_count == 1);
  CHECK(scenario.balls[0].init.y0 == doctest::Approx(5.0));
  CHECK(scenario.balls[0].restitution == doctest::Approx(0.5));
  CHECK(scenario.balls[0].init.g == doctest::Approx(10.0));
  CHECK(scenario.ref_event_count == 8);
}

TEST_CASE("run FL-1 calibration scenario matches tier-1 reference events") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  CHECK(result.count == scenario.ref_event_count);
  for (int i = 0; i < scenario.ref_event_count; ++i) {
    const auto& ref = scenario.reference_events[static_cast<std::size_t>(i)];
    const auto& event = result.events[static_cast<std::size_t>(i)];
    CHECK(event.t == doctest::Approx(ref.t).epsilon(1e-12));
    CHECK(event.s == doctest::Approx(ref.contact_x).epsilon(1e-12));
    CHECK(event.ball_id == ref.ball_id);
    CHECK(event.seq == ref.seq);
  }
}

TEST_CASE("run PB-1 calibration scenario matches tier-1 first contact") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kPb1Path, scenario));
  const auto result = bounce::core::scenario::run_calibration_scenario(scenario, 1);
  CHECK(result.count == 1);
  const auto& ref = scenario.reference_events[0];
  const auto& event = result.events[0];
  CHECK(event.t == doctest::Approx(ref.t).epsilon(1e-12));
  CHECK(event.s == doctest::Approx(ref.contact_x).epsilon(1e-12));
  CHECK(event.ball_id == ref.ball_id);
  CHECK(event.seq == ref.seq);
}

TEST_CASE("FL-1 determinism_repro is bit-identical across 100 repeated runs") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto baseline =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
  for (int run = 0; run < 100; ++run) {
    const auto result =
        bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);
    CHECK(bounce::core::scenario::events_equal(baseline, result));
  }
}

TEST_CASE("FL-1 loop_stability has zero interval-sequence drift across 100 repeated runs") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  constexpr int kMaxEvents = bounce::core::engine::kMaxSimEvents;
  const auto baseline_result =
      bounce::core::scenario::run_calibration_scenario(scenario, kMaxEvents);
  std::array<double, bounce::core::scenario::kMaxCollisionIntervals> baseline_intervals{};
  const int baseline_interval_count =
      bounce::core::scenario::extract_collision_intervals(baseline_result, baseline_intervals);
  REQUIRE(baseline_interval_count == 12);
  constexpr double kExpectedDyadicHalving[] = {
      1.0,         0.5,         0.25,        0.125,       0.0625,      0.03125,
      0.015625,    0.0078125,   0.00390625,  0.001953125, 0.0009765625};
  for (int i = 0; i < 11; ++i) {
    CHECK(baseline_intervals[static_cast<std::size_t>(i)] == kExpectedDyadicHalving[i]);
  }
  for (int run = 0; run < 100; ++run) {
    const auto result = bounce::core::scenario::run_calibration_scenario(scenario, kMaxEvents);
    std::array<double, bounce::core::scenario::kMaxCollisionIntervals> intervals{};
    const int interval_count =
        bounce::core::scenario::extract_collision_intervals(result, intervals);
    CHECK(interval_count == baseline_interval_count);
    CHECK(bounce::core::scenario::intervals_equal(baseline_intervals, intervals,
                                                  baseline_interval_count));
  }
}

TEST_CASE("tier-1 calibration corpus passes reference_agreement") {
  for (const char* path : kTier1CalibrationCorpus) {
    bounce::core::scenario::CalibrationScenario scenario{};
    REQUIRE(bounce::core::scenario::load_calibration_scenario(path, scenario));
    const auto result = bounce::core::scenario::run_calibration_scenario(
        scenario, scenario.ref_event_count);
    CHECK(bounce::core::scenario::agrees_with_tier1_reference(scenario, result));
  }
}
