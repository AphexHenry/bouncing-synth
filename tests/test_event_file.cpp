// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/io/event_file.hpp"
#include "bounce/io/sha256.hpp"
#include "bounce/scenario/calibration_loader.hpp"
#include "run_scenario.hpp"

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

constexpr const char* kGrazeZeroRefPath =
    BOUNCE_SOURCE_DIR "/tests/fixtures/graze-zero-ref.json";

std::string temp_path(const char* suffix) {
  const auto path = std::filesystem::temp_directory_path() /
                    std::format("bounce-event-test-{}-{}", suffix, std::rand());
  return path.string();
}

} // namespace

TEST_CASE("event file round-trip is bit-exact on FL-1 run") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);

  const std::string out_path = temp_path("roundtrip");
  std::string error;
  REQUIRE(bounce::core::io::write_event_file(out_path.c_str(), kFl1Path, result, error));

  bounce::core::io::EventFileData parsed{};
  REQUIRE(bounce::core::io::read_event_file(out_path.c_str(), parsed, error));
  CHECK(bounce::core::io::events_equal(parsed, result));

  std::error_code ec;
  std::filesystem::remove(out_path, ec);
}

TEST_CASE("event file header contains schema and scenario sha256") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kFl1Path, scenario));
  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, scenario.ref_event_count);

  std::array<unsigned char, bounce::core::io::kSha256DigestBytes> digest{};
  REQUIRE(bounce::core::io::sha256_file(kFl1Path, digest));
  const std::string expected_sha = bounce::core::io::sha256_hex(digest);

  const std::string out_path = temp_path("header");
  std::string error;
  REQUIRE(bounce::core::io::write_event_file(out_path.c_str(), kFl1Path, result, error));

  std::ifstream in(out_path);
  std::string header;
  REQUIRE(std::getline(in, header));
  CHECK(header.find("\"schema\":\"bounce-events-v1\"") != std::string::npos);
  CHECK(header.find(expected_sha) != std::string::npos);
  CHECK(header.find(std::format("\"engine_events\":{}", result.count)) != std::string::npos);

  std::error_code ec;
  std::filesystem::remove(out_path, ec);
}

TEST_CASE("bounce-run-scenario exits nonzero on missing scenario path") {
  const std::string out_path = temp_path("missing");
  const char* argv[] = {"bounce-run-scenario",
                        "--scenario",
                        "/nonexistent/bounce-scenario-missing.json",
                        "--out",
                        out_path.c_str()};
  CHECK(run_scenario_cli(5, const_cast<char**>(argv)) != 0);
  CHECK(!std::filesystem::exists(out_path));
}

TEST_CASE("zero-event event file round-trip via write and read") {
  bounce::core::engine::MultiBallSimResult result{};
  result.count = 0;

  const std::string out_path = temp_path("zero-roundtrip");
  std::string error;
  REQUIRE(bounce::core::io::write_event_file(out_path.c_str(), kGrazeZeroRefPath, result, error));

  bounce::core::io::EventFileData parsed{};
  REQUIRE(bounce::core::io::read_event_file(out_path.c_str(), parsed, error));
  CHECK(parsed.count == 0);
  CHECK(bounce::core::io::events_equal(parsed, result));

  std::ifstream in(out_path);
  std::string header;
  REQUIRE(std::getline(in, header));
  CHECK(header.find("\"engine_events\":0") != std::string::npos);
  std::string line;
  CHECK(!std::getline(in, line));

  std::error_code ec;
  std::filesystem::remove(out_path, ec);
}

TEST_CASE("zero-event event file round-trip via streaming") {
  const std::string out_path = temp_path("zero-stream");
  std::string error;

  bounce::core::io::EventStreamWriter writer{};
  REQUIRE(bounce::core::io::begin_event_stream(out_path.c_str(), kGrazeZeroRefPath, writer, error));
  REQUIRE(bounce::core::io::finish_event_stream(writer, error));
  CHECK(writer.count == 0);

  bounce::core::io::EventFileData parsed{};
  REQUIRE(bounce::core::io::read_event_file(out_path.c_str(), parsed, error));
  CHECK(parsed.count == 0);

  std::ifstream in(out_path);
  std::string header;
  REQUIRE(std::getline(in, header));
  CHECK(header.find("\"engine_events\":0") != std::string::npos);

  std::error_code ec;
  std::filesystem::remove(out_path, ec);
}
