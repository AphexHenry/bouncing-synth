// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "restitution_config.hpp"

namespace bounce_view {

int run_interactive(const char* scenario_path, const RunConfig& cfg);
int run_perf_seconds(const char* scenario_path, int seconds, const RunConfig& cfg);

void set_render_optimized(bool enabled);

} // namespace bounce_view
