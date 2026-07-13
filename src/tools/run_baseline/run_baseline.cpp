// SPDX-License-Identifier: GPL-3.0-only
#include "run_baseline.hpp"

#include "baseline/baseline_sim.hpp"
#include "bounce/io/event_file.hpp"
#include "bounce/scenario/calibration_loader.hpp"

#include <iostream>
#include <string>

namespace {

void print_usage() {
  std::cerr << "usage: bounce-baseline-run --scenario <path> --out <path> --dt <seconds> "
               "--segments <N> [--max-events M]\n";
}

} // namespace

int run_baseline_cli(int argc, char** argv) {
  const char* scenario_path = nullptr;
  const char* out_path = nullptr;
  double dt = 0.0;
  int segments = 0;
  int max_events = bounce::core::engine::kMaxSimEvents;
  bool dt_set = false;
  bool segments_set = false;

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (arg == "--scenario" && i + 1 < argc) {
      scenario_path = argv[++i];
      continue;
    }
    if (arg == "--out" && i + 1 < argc) {
      out_path = argv[++i];
      continue;
    }
    if (arg == "--dt" && i + 1 < argc) {
      dt = std::stod(argv[++i]);
      dt_set = true;
      continue;
    }
    if (arg == "--segments" && i + 1 < argc) {
      segments = std::stoi(argv[++i]);
      segments_set = true;
      continue;
    }
    if (arg == "--max-events" && i + 1 < argc) {
      max_events = std::stoi(argv[++i]);
      continue;
    }
    print_usage();
    return 1;
  }

  if (scenario_path == nullptr || out_path == nullptr || !dt_set || !segments_set) {
    print_usage();
    return 1;
  }
  if (max_events <= 0 || max_events > static_cast<int>(bounce::core::engine::kMaxSimEvents)) {
    std::cerr << "invalid --max-events\n";
    return 1;
  }
  if (dt <= 0.0 || segments <= 0) {
    std::cerr << "invalid --dt or --segments\n";
    return 1;
  }

  bounce::core::scenario::CalibrationScenario scenario{};
  if (!bounce::core::scenario::load_calibration_scenario(scenario_path, scenario)) {
    std::cerr << "failed to load scenario: " << scenario_path << '\n';
    return 1;
  }

  bounce::baseline::BaselineParams params{};
  params.dt = dt;
  params.segments = segments;
  const auto result = bounce::baseline::run_baseline_calibration(scenario, max_events, params);

  std::string error;
  if (!bounce::core::io::write_event_file(out_path, scenario_path, result, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  std::cout << "events=" << result.count << '\n';
  return 0;
}
