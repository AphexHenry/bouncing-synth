// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <cstddef>
#include <vector>

namespace bounce_view {

struct SubsystemTiming {
  const char* name = nullptr;
  double total_ms = 0.0;
  std::size_t samples = 0;
};

struct PerfStats {
  int display_w = 0;
  int display_h = 0;
  int refresh_hz = 0;
  std::size_t frame_count = 0;
  std::vector<double> frame_times_ms{};
  SubsystemTiming engine_query{};
  SubsystemTiming curve_draw{};
  SubsystemTiming ball_draw{};
  SubsystemTiming present{};
  SubsystemTiming audio{};
};

void record_subsystem(SubsystemTiming& slot, double ms);
double percentile_ms(const std::vector<double>& samples, double p);
void print_perf_report(const PerfStats& stats);

} // namespace bounce_view
