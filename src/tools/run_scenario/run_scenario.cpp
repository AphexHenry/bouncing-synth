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

struct StreamCtx {
  bounce::core::io::EventStreamWriter* writer = nullptr;
};

bool on_event_sink(void* user_data, const bounce::core::events::CollisionEvent& event) {
  auto* ctx = static_cast<StreamCtx*>(user_data);
  return bounce::core::io::emit_event_stream(*ctx->writer, event);
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
  if (max_events <= 0 || max_events > bounce::core::io::kMaxOfflineEvents) {
    std::cerr << "invalid --max-events\n";
    return 1;
  }
  (void)max_events_set;

  bounce::core::scenario::CalibrationScenario scenario{};
  if (!bounce::core::scenario::load_calibration_scenario(scenario_path, scenario)) {
    std::cerr << "failed to load scenario: " << scenario_path << '\n';
    return 1;
  }

  bounce::core::io::EventStreamWriter writer{};
  std::string error;
  if (!bounce::core::io::begin_event_stream(out_path, scenario_path, writer, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  StreamCtx ctx{&writer};
  bounce::core::engine::EventEmitSink sink{};
  sink.user_data = &ctx;
  sink.on_event = on_event_sink;

  const auto result =
      bounce::core::scenario::run_calibration_scenario(scenario, max_events, &sink);

  if (!bounce::core::io::finish_event_stream(writer, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  if (result.count != writer.count) {
    std::cerr << "event count mismatch\n";
    return 1;
  }

  std::cout << "events=" << writer.count << '\n';
  return 0;
}
