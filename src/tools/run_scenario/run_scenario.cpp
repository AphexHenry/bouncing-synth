// SPDX-License-Identifier: GPL-3.0-only
#include "run_scenario.hpp"

#include "bounce/engine/collision_sim.hpp"
#include "bounce/io/event_file.hpp"
#include "bounce/scenario/calibration_loader.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace {

void print_usage() {
  std::cerr << "usage: bounce-run-scenario --scenario <path> --out <path> "
               "[--max-events N] [--repeat N]\n";
}

struct CollectCtx {
  std::vector<bounce::core::events::CollisionEvent>* events = nullptr;
};

bool on_event_collect(void* user_data, const bounce::core::events::CollisionEvent& event) {
  auto* ctx = static_cast<CollectCtx*>(user_data);
  ctx->events->push_back(event);
  return true;
}

bool report_event_mismatch(const std::vector<bounce::core::events::CollisionEvent>& baseline,
                           const std::vector<bounce::core::events::CollisionEvent>& candidate,
                           int run_index) {
  if (baseline.size() != candidate.size()) {
    std::cerr << "repeat-failed: run=" << run_index << " event_count baseline=" << baseline.size()
              << " candidate=" << candidate.size() << '\n';
    return false;
  }
  for (std::size_t i = 0; i < baseline.size(); ++i) {
    if (!bounce::core::io::events_equal(baseline[i], candidate[i])) {
      std::cerr << "repeat-failed: run=" << run_index << " first_divergence_event=" << i
                << " seq baseline=" << baseline[i].seq << " candidate=" << candidate[i].seq
                << '\n';
      return false;
    }
  }
  return true;
}

} // namespace

int run_scenario_cli(int argc, char** argv) {
  const char* scenario_path = nullptr;
  const char* out_path = nullptr;
  int max_events = bounce::core::engine::kMaxSimEvents;
  bool max_events_set = false;
  int repeat_count = 1;

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
    if (arg == "--repeat" && i + 1 < argc) {
      repeat_count = std::stoi(argv[++i]);
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
  if (repeat_count <= 0) {
    std::cerr << "invalid --repeat\n";
    return 1;
  }
  (void)max_events_set;

  bounce::core::scenario::CalibrationScenario scenario{};
  if (!bounce::core::scenario::load_calibration_scenario(scenario_path, scenario)) {
    std::cerr << "failed to load scenario: " << scenario_path << '\n';
    return 1;
  }

  std::vector<bounce::core::events::CollisionEvent> run_events;
  std::vector<bounce::core::events::CollisionEvent> baseline_events;
  CollectCtx collect_ctx{&run_events};
  bounce::core::engine::EventEmitSink collect_sink{};
  collect_sink.user_data = &collect_ctx;
  collect_sink.on_event = on_event_collect;

  for (int run = 0; run < repeat_count; ++run) {
    run_events.clear();
    const auto result =
        bounce::core::scenario::run_calibration_scenario(scenario, max_events, &collect_sink);
    if (static_cast<int>(run_events.size()) != result.count ||
        static_cast<int>(result.events.size()) != result.count) {
      std::cerr << "event storage mismatch: sink=" << run_events.size()
                << " vector=" << result.events.size() << " count=" << result.count << '\n';
      return 1;
    }
    if (run == 0) {
      baseline_events = run_events;
    } else if (!report_event_mismatch(baseline_events, run_events, run)) {
      return 1;
    }
  }

  bounce::core::io::EventStreamWriter writer{};
  std::string error;
  if (!bounce::core::io::begin_event_stream(out_path, scenario_path, writer, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  for (const auto& event : baseline_events) {
    if (!bounce::core::io::emit_event_stream(writer, event)) {
      std::cerr << "failed to emit event stream\n";
      return 1;
    }
  }

  if (!bounce::core::io::finish_event_stream(writer, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  if (static_cast<int>(baseline_events.size()) != writer.count) {
    std::cerr << "event count mismatch\n";
    return 1;
  }

  if (repeat_count > 1) {
    std::cout << "repeat-identity ok N=" << repeat_count << '\n';
  }
  std::cout << "events=" << writer.count << '\n';
  return 0;
}
