// SPDX-License-Identifier: GPL-3.0-only
#pragma once

namespace bounce_view {

int run_interactive(const char* scenario_path);
int run_perf_seconds(const char* scenario_path, int seconds);

void set_render_optimized(bool enabled);

} // namespace bounce_view
