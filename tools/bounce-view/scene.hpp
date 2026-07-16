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

struct CameraState {
  Viewport current{};
  bool initialized = false;
};

struct SceneCache {
  bounce::core::curve::CompiledPolynomial curve_y{};
  bounce::core::curve::CompiledPiecewiseBezier curve_bezier{};
  bool has_polynomial = false;
  bool has_bezier = false;
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

struct FrameCheckResult {
  int ball_id = 0;
  int ball_px_x = 0;
  int ball_px_y = 0;
  bool in_viewport = false;
  int curve_pixels = 0;
};

void reset_playback_view(PlaybackView& view);
void seek_playback_view(PlaybackView& view, double t);
BallRenderState ball_state_in_view(const PlaybackView& view, int ball_id, double t);

Viewport compute_viewport_targets(const PlaybackView& view, double t);
Viewport smooth_viewport(CameraState& camera, const Viewport& target, double alpha = 0.12);

void build_scene_cache(const PlaybackView& view, double t, int window_w, int window_h,
                       SceneCache& cache, bool optimize, CameraState* camera = nullptr);

void draw_scene(SDL_Renderer* renderer, const SceneCache& cache, const PlaybackView& view,
                double t, int window_w, int window_h, PerfStats* perf);

std::vector<FrameCheckResult> compute_frame_checks(const SceneCache& cache,
                                                   const PlaybackView& view, double t,
                                                   int window_w, int window_h);

} // namespace bounce_view
