// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/engine/collision_sim.hpp"
#include "bounce/scenario/calibration_loader.hpp"

namespace bounce::baseline {

struct BaselineParams {
  double dt = 1e-4;
  int segments = 64;
};

bounce::core::engine::MultiBallSimResult simulate_baseline(
    const bounce::core::curve::CompiledPolynomial& curve_y, double domain_min, double domain_max,
    const bounce::core::engine::BallSpec* balls, int ball_count, int max_events,
    const BaselineParams& params);

bounce::core::engine::MultiBallSimResult run_baseline_calibration(
    const bounce::core::scenario::CalibrationScenario& scenario, int max_events,
    const BaselineParams& params);

} // namespace bounce::baseline
