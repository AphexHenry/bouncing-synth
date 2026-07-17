// SPDX-License-Identifier: GPL-3.0-only
#include "perf.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>

namespace bounce_view {

void record_subsystem(SubsystemTiming& slot, double ms) {
  slot.total_ms += ms;
  ++slot.samples;
}

double percentile_ms(const std::vector<double>& samples, double p) {
  if (samples.empty()) {
    return 0.0;
  }
  std::vector<double> sorted = samples;
  std::sort(sorted.begin(), sorted.end());
  const double rank = p * static_cast<double>(sorted.size() - 1);
  const auto lo = static_cast<std::size_t>(std::floor(rank));
  const auto hi = static_cast<std::size_t>(std::ceil(rank));
  if (lo == hi) {
    return sorted[lo];
  }
  const double frac = rank - static_cast<double>(lo);
  return sorted[lo] * (1.0 - frac) + sorted[hi] * frac;
}

namespace {

double mean_ms(const std::vector<double>& samples) {
  if (samples.empty()) {
    return 0.0;
  }
  return std::accumulate(samples.begin(), samples.end(), 0.0) /
         static_cast<double>(samples.size());
}

double subsystem_mean(const SubsystemTiming& slot) {
  if (slot.samples == 0) {
    return 0.0;
  }
  return slot.total_ms / static_cast<double>(slot.samples);
}

} // namespace

void print_perf_report(const PerfStats& stats) {
  const double mean = mean_ms(stats.frame_times_ms);
  const double p50 = percentile_ms(stats.frame_times_ms, 0.50);
  const double p95 = percentile_ms(stats.frame_times_ms, 0.95);
  const double max =
      stats.frame_times_ms.empty()
          ? 0.0
          : *std::max_element(stats.frame_times_ms.begin(), stats.frame_times_ms.end());

  std::cout << "display: " << stats.display_w << 'x' << stats.display_h << " @ "
            << stats.refresh_hz << " Hz\n";
  std::cout << "frames: " << stats.frame_count << '\n';
  std::cout << "duration_s: " << stats.measured_duration_s << '\n';
  std::cout << std::setprecision(6) << std::fixed;
  std::cout << "frame_ms mean=" << mean << " p50=" << p50 << " p95=" << p95 << " max=" << max
            << '\n';
  std::cout << "subsystem_ms_per_frame engine_query=" << subsystem_mean(stats.engine_query)
            << " curve_draw=" << subsystem_mean(stats.curve_draw)
            << " ball_draw=" << subsystem_mean(stats.ball_draw)
            << " present=" << subsystem_mean(stats.present)
            << " audio=" << subsystem_mean(stats.audio) << '\n';
}

} // namespace bounce_view
