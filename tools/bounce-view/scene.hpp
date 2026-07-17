// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "playback.hpp"
#include "perf.hpp"

#include <SDL.h>

#include <string>
#include <vector>

namespace bounce_view {

struct Viewport {
  double x_min = 0.0;
  double x_max = 1.0;
  double y_min = 0.0;
  double y_max = 1.0;
};

// S15 assessment camera: uniform aspect-preserving scale, quantized hysteretic zoom.
struct CameraState {
  double s_base = 1.0;
  int level = 0;
  double scale = 1.0; // s_base * 1.25^level
  double center_x = 0.0;
  double center_y = 0.0;
  bool initialized = false;
  bool locked = false;
  Viewport current{};
  double scale_x = 0.0;
  double scale_y = 0.0;
  double grid_step = 1.0;
  int grid_lines_v = 0;
  int grid_lines_h = 0;
};

struct SceneCache {
  bounce::core::curve::CompiledPolynomial curve_y{};
  bounce::core::curve::CompiledPiecewiseBezier curve_bezier{};
  bool has_polynomial = false;
  bool has_bezier = false;
  Viewport viewport{};
  std::vector<SDL_Point> curve_screen_points{};
  double scale = 1.0;
  double scale_x = 0.0;
  double scale_y = 0.0;
  int camera_level = 0;
  double grid_step = 1.0;
  int grid_lines_v = 0;
  int grid_lines_h = 0;
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
  double ball_on_curve_px_dist = 0.0;
  double ball_radius_px = 0.0;
  double ball_draw_px = 0.0;
  double scale = 0.0;
  double scale_x = 0.0;
  double scale_y = 0.0;
  int camera_level = 0;
  double camera_scale = 0.0;
  double grid_step = 0.0;
  int grid_lines_v = 0;
  int grid_lines_h = 0;
};

struct HudState {
  double sim_t = 0.0;
  int event_count = 0;
  std::string restitution;
  bool camera_locked = false;
  int camera_level = 0;
  std::string build_short;
};

void reset_playback_view(PlaybackView& view);
void seek_playback_view(PlaybackView& view, double t);
BallRenderState ball_state_in_view(const PlaybackView& view, int ball_id, double t);

Viewport compute_viewport_targets(const PlaybackView& view, double t);

// Returns true when level/scale changed (caller should print `camera: level=… scale=…`).
bool update_camera(CameraState& camera, const Viewport& content, int window_w, int window_h);

// Returns true when camera level/scale changed (stdout `camera:` line may be printed by caller).
bool build_scene_cache(const PlaybackView& view, double t, int window_w, int window_h,
                       SceneCache& cache, bool optimize, CameraState* camera = nullptr);

void draw_scene(SDL_Renderer* renderer, const SceneCache& cache, const PlaybackView& view,
                double t, int window_w, int window_h, PerfStats* perf);

void draw_hud_overlay(SDL_Renderer* renderer, const HudState& hud, int window_w, int window_h);

void print_hud_line(const HudState& hud);
void print_camera_line(const CameraState& camera);

std::vector<FrameCheckResult> compute_frame_checks(const SceneCache& cache,
                                                   const PlaybackView& view, double t,
                                                   int window_w, int window_h);

double nice_grid_step(double view_span);
void count_grid_lines(const Viewport& vp, double step, int& lines_v, int& lines_h);

} // namespace bounce_view
