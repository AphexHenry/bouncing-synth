// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "playback.hpp"
#include "perf.hpp"

#include <SDL.h>

#include <vector>

namespace bounce_view {

struct Viewport {
  double x_min = 0.0;
  double x_max = 1.0;
  double y_min = 0.0;
  double y_max = 1.0;
};

struct SceneCache {
  bounce::core::curve::CompiledPolynomial curve_y{};
  bool has_polynomial = false;
  Viewport viewport{};
  std::vector<SDL_Point> curve_screen_points{};
};

struct PlaybackView {
  Playback pb{};
  std::size_t next_event = 0;
  std::array<bounce::core::engine::BallisticInit, bounce::core::engine::kMaxBalls> current{};
  std::array<double, bounce::core::engine::kMaxBalls> arc_start_t{};
  std::array<bool, bounce::core::engine::kMaxBalls> settled{};
  std::array<bounce::core::engine::Vec2, bounce::core::engine::kMaxBalls> settle_pos{};
};

struct RenderOptions {
  bool optimize = false;
  bool vsync = false;
};

void reset_playback_view(PlaybackView& view);
void seek_playback_view(PlaybackView& view, double t);
BallRenderState ball_state_in_view(const PlaybackView& view, int ball_id, double t);

void build_scene_cache(const PlaybackView& view, int window_w, int window_h, SceneCache& cache,
                       bool optimize);
void draw_scene(SDL_Renderer* renderer, const SceneCache& cache, const PlaybackView& view,
                double t, PerfStats* perf);

} // namespace bounce_view
