// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/engine/ballistic.hpp"
#include "bounce/engine/collision_sim.hpp"
#include "bounce/scenario/calibration_loader.hpp"

#include <array>
#include <vector>

namespace bounce_view {

struct BallRenderState {
  bounce::core::engine::Vec2 pos{};
  bool visible = true;
  bool settled = false;
};

struct Playback {
  bounce::core::scenario::CalibrationScenario scenario{};
  std::vector<bounce::core::events::CollisionEvent> events{};
  std::array<bounce::core::engine::BallisticInit, bounce::core::engine::kMaxBalls> inits{};
  std::array<bounce::core::engine::BallisticInit, bounce::core::engine::kMaxBalls> current{};
  std::array<double, bounce::core::engine::kMaxBalls> arc_start_t{};
  std::array<bool, bounce::core::engine::kMaxBalls> settled{};
  std::array<bounce::core::engine::Vec2, bounce::core::engine::kMaxBalls> settle_pos{};
  std::size_t next_event = 0;
  double end_time = 0.0;
};

bool load_and_simulate(const char* scenario_path, Playback& out, int max_events,
                       std::string& error);

void reset_playback(Playback& pb);

void advance_playback_to(Playback& pb, double t);

BallRenderState ball_state_at(const Playback& pb, int ball_id, double t);

} // namespace bounce_view
