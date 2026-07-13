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
               "--segments <N> [--max-events M] [--dump-trajectory T_START T_END]\n";
}

struct StreamCtx {
  bounce::core::io::EventStreamWriter* writer = nullptr;
};

bool on_event_sink(void* user_data, const bounce::core::events::CollisionEvent& event) {
  auto* ctx = static_cast<StreamCtx*>(user_data);
  return bounce::core::io::emit_event_stream(*ctx->writer, event);
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
  bool dump_trajectory = false;
  double dump_t_start = 0.0;
  double dump_t_end = 0.0;

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
    if (arg == "--dump-trajectory" && i + 2 < argc) {
      dump_trajectory = true;
      dump_t_start = std::stod(argv[++i]);
      dump_t_end = std::stod(argv[++i]);
      continue;
    }
    print_usage();
    return 1;
  }

  if (scenario_path == nullptr || (!dump_trajectory && out_path == nullptr) || !dt_set ||
      !segments_set) {
    print_usage();
    return 1;
  }
  if (max_events <= 0 || max_events > bounce::core::io::kMaxOfflineEvents) {
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

  if (dump_trajectory) {
    bounce::baseline::dump_baseline_trajectory(scenario, params, dump_t_start, dump_t_end);
    return 0;
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
      bounce::baseline::run_baseline_calibration(scenario, max_events, params, &sink);

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
