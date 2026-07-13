// SPDX-License-Identifier: GPL-3.0-only
#include "baseline/baseline_sim.hpp"
#include "bounce/io/event_file.hpp"
#include "bounce/io/sha256.hpp"
#include "bounce/scenario/calibration_loader.hpp"
#include "run_baseline.hpp"

#include <doctest/doctest.h>

#include <array>
#include <filesystem>
#include <format>
#include <fstream>

#ifndef BOUNCE_SOURCE_DIR
#define BOUNCE_SOURCE_DIR "."
#endif

namespace {

constexpr const char* kFl1Path =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/FL-1-h5-g10-e1o2.json";
constexpr double kDt = 1e-4;
constexpr int kSegments = 64;

std::string temp_path(const char* suffix) {
  const auto path = std::filesystem::temp_directory_path() /
                    std::format("bounce-baseline-test-{}-{}", suffix, std::rand());
  return path.string();
}

bounce::baseline::BaselineParams fl1_params() {
  bounce::baseline::BaselineParams params{};
  params.dt = kDt;
  params.segments = kSegments;
  return params;
}

} // namespace

TEST_CASE("baseline FL-1 first contact within 2*dt of tier-1 reference") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto result =
      bounce::baseline::run_baseline_calibration(scenario, scenario.ref_event_count, fl1_params());
  REQUIRE(result.count >= 8);
  const double ref_t = scenario.reference_events[0].t;
  const double delta_t = std::abs(result.events[0].t - ref_t);
  MESSAGE("first-contact t=", result.events[0].t, " ref_t=", ref_t, " |Δt|=", delta_t);
  CHECK(delta_t <= 2.0 * kDt);
}

TEST_CASE("baseline FL-1 emits at least 8 events before settle") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto result = bounce::baseline::run_baseline_calibration(
      scenario, bounce::core::engine::kMaxSimEvents, fl1_params());
  CHECK(result.count >= 8);
}

TEST_CASE("baseline output round-trips through shared io layer") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto result =
      bounce::baseline::run_baseline_calibration(scenario, scenario.ref_event_count, fl1_params());

  const std::string out_path = temp_path("roundtrip");
  std::string error;
  REQUIRE(bounce::core::io::write_event_file(out_path.c_str(), kFl1Path, result, error));

  bounce::core::io::EventFileData parsed{};
  REQUIRE(bounce::core::io::read_event_file(out_path.c_str(), parsed, error));
  CHECK(bounce::core::io::events_equal(parsed, result));

  std::error_code ec;
  std::filesystem::remove(out_path, ec);
}

TEST_CASE("baseline FL-1 determinism: two identical runs are bit-identical") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto a =
      bounce::baseline::run_baseline_calibration(scenario, scenario.ref_event_count, fl1_params());
  const auto b =
      bounce::baseline::run_baseline_calibration(scenario, scenario.ref_event_count, fl1_params());
  CHECK(bounce::core::scenario::events_equal(a, b));
}

TEST_CASE("bounce-baseline-run CLI writes byte-identical files on repeat") {
  const std::string out_a = temp_path("cli-a");
  const std::string out_b = temp_path("cli-b");
  const char* argv_a[] = {"bounce-baseline-run",
                            "--scenario",
                            kFl1Path,
                            "--out",
                            out_a.c_str(),
                            "--dt",
                            "0.0001",
                            "--segments",
                            "64"};
  const char* argv_b[] = {"bounce-baseline-run",
                            "--scenario",
                            kFl1Path,
                            "--out",
                            out_b.c_str(),
                            "--dt",
                            "0.0001",
                            "--segments",
                            "64"};
  CHECK(run_baseline_cli(9, const_cast<char**>(argv_a)) == 0);
  CHECK(run_baseline_cli(9, const_cast<char**>(argv_b)) == 0);

  std::array<unsigned char, bounce::core::io::kSha256DigestBytes> digest_a{};
  std::array<unsigned char, bounce::core::io::kSha256DigestBytes> digest_b{};
  REQUIRE(bounce::core::io::sha256_file(out_a.c_str(), digest_a));
  REQUIRE(bounce::core::io::sha256_file(out_b.c_str(), digest_b));
  CHECK(bounce::core::io::sha256_hex(digest_a) == bounce::core::io::sha256_hex(digest_b));

  std::error_code ec;
  std::filesystem::remove(out_a, ec);
  std::filesystem::remove(out_b, ec);
}
