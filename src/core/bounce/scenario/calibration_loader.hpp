// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/engine/collision_sim.hpp"

#include <array>
#include <cstddef>

namespace bounce::core::scenario {

constexpr int kMaxScenarioCoeffs = 9;
constexpr int kMaxScenarioBalls = 4;
constexpr int kMaxScenarioRefEvents = 64;

struct ReferenceEvent {
  double t = 0.0;
  double contact_x = 0.0;
  double contact_y = 0.0;
  int ball_id = 0;
  int seq = 0;
};

struct CalibrationScenario {
  int coeff_count = 0;
  std::array<double, kMaxScenarioCoeffs> coeffs{};
  double domain_min = 0.0;
  double domain_max = 0.0;
  int ball_count = 0;
  std::array<engine::BallSpec, kMaxScenarioBalls> balls{};
  int ref_event_count = 0;
  std::array<ReferenceEvent, kMaxScenarioRefEvents> reference_events{};
};

bool load_calibration_scenario(const char* path, CalibrationScenario& out);

engine::MultiBallSimResult run_calibration_scenario(const CalibrationScenario& scenario,
                                                  int max_events);

bool events_equal(const engine::MultiBallSimResult& a, const engine::MultiBallSimResult& b);

constexpr int kMaxCollisionIntervals = engine::kMaxSimEvents - 1;

int extract_collision_intervals(const engine::MultiBallSimResult& result,
                                std::array<double, kMaxCollisionIntervals>& intervals);

bool intervals_equal(const std::array<double, kMaxCollisionIntervals>& a,
                     const std::array<double, kMaxCollisionIntervals>& b, int count);

constexpr double kTier1ReferenceEpsilon = 1e-12;

bool agrees_with_tier1_reference(const CalibrationScenario& scenario,
                                 const engine::MultiBallSimResult& result);

} // namespace bounce::core::scenario
