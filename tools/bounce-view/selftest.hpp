// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "playback.hpp"

namespace bounce_view {

struct SelftestOptions {
  const char* scenario_path = nullptr;
  const char* outdir = nullptr;
  int frames = 0;
};

int run_selftest(const SelftestOptions& opts);

} // namespace bounce_view
