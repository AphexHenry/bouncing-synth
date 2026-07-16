// SPDX-License-Identifier: GPL-3.0-only
#include "interactive.hpp"
#include "law1_guard.hpp"
#include "restitution_config.hpp"
#include "selftest.hpp"

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

namespace {

void print_usage() {
  std::cerr << "usage: bounce-view <scenario.json>\n"
               "       bounce-view --selftest <scenario.json> [--frames k] [--outdir dir]\n"
               "                      [--frame-times t1,t2,...] [--max-events n]\n"
               "                      [--scenario-restitution] [--restitution r]\n"
               "       bounce-view --perf-seconds <n> <scenario.json>\n"
               "                      [--scenario-restitution] [--restitution r]\n"
               "       bounce-view --print-config\n";
}

bool check_law1(const char* path) {
  if (bounce_view::is_heldout_path(path)) {
    std::cout << "LAW1: held-out scenario refused\n";
    return false;
  }
  return true;
}

struct FlagState {
  bool scenario_restitution = false;
  bool restitution_flag = false;
  double restitution_value = 1.0;
  bool max_events_flag = false;
  int max_events = 0;
};

bool parse_restitution_value(const char* text, double& out) {
  out = std::stod(text);
  return out > 0.0 && out <= 1.0;
}

bool conflicting_flags(const FlagState& flags) {
  return flags.scenario_restitution && flags.restitution_flag;
}

bounce_view::RunConfig make_run_config(bounce_view::RunKind kind, const FlagState& flags) {
  bounce_view::RunConfig cfg{};
  cfg.kind = kind;
  cfg.max_events = flags.max_events_flag ? flags.max_events : 200;
  if (flags.scenario_restitution) {
    cfg.mode = bounce_view::RestitutionMode::ScenarioFaithful;
  } else if (flags.restitution_flag) {
    cfg.mode = bounce_view::RestitutionMode::OverrideUniform;
    cfg.override_r = flags.restitution_value;
  } else {
    cfg.mode = bounce_view::default_restitution_mode(kind);
  }
  return cfg;
}

} // namespace

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage();
    return 1;
  }

  if (std::strcmp(argv[1], "--print-config") == 0) {
    bounce_view::print_config_defaults();
    return 0;
  }

  bool selftest = false;
  int frames = 0;
  int perf_seconds = 0;
  const char* outdir = nullptr;
  const char* scenario_path = nullptr;
  const char* frame_times = nullptr;
  FlagState flags{};

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (arg == "--selftest" && i + 1 < argc) {
      selftest = true;
      scenario_path = argv[++i];
      continue;
    }
    if (arg == "--perf-seconds" && i + 1 < argc) {
      perf_seconds = std::stoi(argv[++i]);
      continue;
    }
    if (arg == "--frames" && i + 1 < argc) {
      frames = std::stoi(argv[++i]);
      continue;
    }
    if (arg == "--outdir" && i + 1 < argc) {
      outdir = argv[++i];
      continue;
    }
    if (arg == "--frame-times" && i + 1 < argc) {
      frame_times = argv[++i];
      continue;
    }
    if (arg == "--scenario-restitution") {
      flags.scenario_restitution = true;
      continue;
    }
    if (arg == "--restitution" && i + 1 < argc) {
      flags.restitution_flag = true;
      if (!parse_restitution_value(argv[++i], flags.restitution_value)) {
        std::cerr << "error: --restitution requires r in (0,1]\n";
        return 1;
      }
      continue;
    }
    if (arg == "--max-events" && i + 1 < argc) {
      flags.max_events_flag = true;
      flags.max_events = std::stoi(argv[++i]);
      continue;
    }
    if (arg.rfind('-', 0) == 0) {
      print_usage();
      return 1;
    }
    scenario_path = argv[i];
  }

  if (conflicting_flags(flags)) {
    std::cerr << "error: --restitution and --scenario-restitution are mutually exclusive\n";
    return 1;
  }

  if (scenario_path == nullptr && !selftest && perf_seconds <= 0) {
    print_usage();
    return 1;
  }

  if (scenario_path != nullptr && !check_law1(scenario_path)) {
    return 2;
  }

  if (perf_seconds > 0) {
    const auto cfg = make_run_config(bounce_view::RunKind::Evidence, flags);
    bounce_view::set_render_optimized(true);
    return bounce_view::run_perf_seconds(scenario_path, perf_seconds, cfg);
  }

  if (selftest) {
    bounce_view::SelftestOptions opts{};
    opts.scenario_path = scenario_path;
    opts.outdir = outdir;
    opts.frames = frames;
    opts.frame_times = frame_times;
    opts.run_cfg = make_run_config(bounce_view::RunKind::Evidence, flags);
    return bounce_view::run_selftest(opts);
  }

  const auto cfg = make_run_config(bounce_view::RunKind::Interactive, flags);
  bounce_view::set_render_optimized(true);
  return bounce_view::run_interactive(scenario_path, cfg);
}
