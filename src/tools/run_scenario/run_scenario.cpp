// SPDX-License-Identifier: GPL-3.0-only
#include "run_scenario.hpp"

#include "bounce/engine/collision_sim.hpp"
#include "bounce/io/event_file.hpp"
#include "bounce/scenario/calibration_loader.hpp"

#include <iostream>
#include <string>

namespace {

void print_usage() {
  std::cerr << "usage: bounce-run-scenario --scenario <path> --out <path> [--max-events N]\n";
}

} // namespace

int run_scenario_cli(int argc, char** argv) {
  const char* scenario_path = nullptr;
  const char* out_path = nullptr;
  int max_events = bounce::core::engine::kMaxSimEvents;
  bool max_events_set = false;

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
    if (arg == "--max-events" && i + 1 < argc) {
      max_events = std::stoi(argv[++i]);
      max_events_set = true;
      continue;
    }
    print_usage();
    return 1;
  }

  if (scenario_path == nullptr || out_path == nullptr) {
    print_usage();
    return 1;
  }
  if (max_events <= 0) {
    std::cerr << "invalid --max-events\n";
    return 1;
  }
  (void)max_events_set;

  bounce::core::scenario::CalibrationScenario scenario{};
  if (!bounce::core::scenario::load_calibration_scenario(scenario_path, scenario)) {
    std::cerr << "failed to load scenario: " << scenario_path << '\n';
    return 1;
  }

  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, max_events);

  std::string error;
  if (!bounce::core::io::write_event_file(out_path, scenario_path, result, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  std::cout << "events=" << result.count << '\n';
  return 0;
}
