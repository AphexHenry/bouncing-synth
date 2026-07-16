// SPDX-License-Identifier: GPL-3.0-only
#include "interactive.hpp"
#include "law1_guard.hpp"
#include "selftest.hpp"

#include <cstring>
#include <iostream>
#include <string>

namespace {

void print_usage() {
  std::cerr << "usage: bounce-view <scenario.json>\n"
               "       bounce-view --selftest <scenario.json> [--frames k] [--outdir dir]\n"
               "                      [--frame-times t1,t2,...]\n"
               "       bounce-view --perf-seconds <n> <scenario.json>\n";
}

bool check_law1(const char* path) {
  if (bounce_view::is_heldout_path(path)) {
    std::cout << "LAW1: held-out scenario refused\n";
    return false;
  }
  return true;
}

} // namespace

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage();
    return 1;
  }

  bool selftest = false;
  int frames = 0;
  int perf_seconds = 0;
  const char* outdir = nullptr;
  const char* scenario_path = nullptr;
  const char* frame_times = nullptr;

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
    if (arg.rfind('-', 0) == 0) {
      print_usage();
      return 1;
    }
    scenario_path = argv[i];
  }

  if (scenario_path == nullptr) {
    print_usage();
    return 1;
  }

  if (!check_law1(scenario_path)) {
    return 2;
  }

  if (perf_seconds > 0) {
    return bounce_view::run_perf_seconds(scenario_path, perf_seconds);
  }

  if (selftest) {
    bounce_view::SelftestOptions opts{};
    opts.scenario_path = scenario_path;
    opts.outdir = outdir;
    opts.frames = frames;
    opts.frame_times = frame_times;
    return bounce_view::run_selftest(opts);
  }

  return bounce_view::run_interactive(scenario_path);
}
