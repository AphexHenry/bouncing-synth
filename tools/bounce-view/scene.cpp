// SPDX-License-Identifier: GPL-3.0-only
#include "scene.hpp"

#include "bezier_display_geometry.hpp"
#include "perf.hpp"

#include <SDL.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <vector>

namespace bounce_view {

namespace {

using Clock = std::chrono::steady_clock;

double elapsed_ms(Clock::time_point start) {
  return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

SDL_Point to_screen(double x, double y, const Viewport& vp, int window_w, int window_h) {
  SDL_Point p{};
  p.x = static_cast<int>((x - vp.x_min) / (vp.x_max - vp.x_min) * static_cast<double>(window_w - 1));
  p.y = static_cast<int>((vp.y_max - y) / (vp.y_max - vp.y_min) * static_cast<double>(window_h - 1));
  return p;
}

void apply_event_to_view(PlaybackView& view, const bounce::core::events::CollisionEvent& event) {
  const int idx = event.ball_id;
  if (idx < 0 || idx >= bounce::core::engine::kMaxBalls) {
    return;
  }
  auto& pb = view.pb;
  if (pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    auto& state = view.current[static_cast<std::size_t>(idx)];
    const auto curve_y = bounce::core::curve::compile_polynomial(
        std::vector<double>(pb.scenario.coeffs.begin(),
                            pb.scenario.coeffs.begin() + pb.scenario.coeff_count));
    const double dt = event.t - view.arc_start_t[static_cast<std::size_t>(idx)];
    const double vy_contact = state.vy - state.g * dt;
    const auto reflected =
        bounce::core::engine::reflect_velocity(curve_y, event.s, state.vx, vy_contact,
                                               pb.scenario.balls[static_cast<std::size_t>(idx)].restitution);
    if (reflected.normal_speed_out < bounce::core::engine::kVSettle) {
      view.settled[static_cast<std::size_t>(idx)] = true;
      view.settle_pos[static_cast<std::size_t>(idx)] =
          bounce::core::engine::position_at_time(state, dt);
      return;
    }
    state.x0 = event.s;
    state.y0 = bounce::core::curve::eval(curve_y, event.s);
    state.vx = reflected.vx;
    state.vy = reflected.vy;
    view.arc_start_t[static_cast<std::size_t>(idx)] = event.t;
    return;
  }
  auto& state = view.current[static_cast<std::size_t>(idx)];
  const double dt = event.t - view.arc_start_t[static_cast<std::size_t>(idx)];
  const double vy_contact = state.vy - state.g * dt;
  const double nx = event.normal_x;
  const double ny = event.normal_y;
  const double vn = state.vx * nx + vy_contact * ny;
  const double restitution = pb.scenario.balls[static_cast<std::size_t>(idx)].restitution;
  bounce::core::engine::ReflectedVelocity reflected{};
  reflected.vx = state.vx - (1.0 + restitution) * vn * nx;
  reflected.vy = vy_contact - (1.0 + restitution) * vn * ny;
  reflected.normal_speed_out = std::abs(vn);
  if (reflected.normal_speed_out < bounce::core::engine::kVSettle) {
    view.settled[static_cast<std::size_t>(idx)] = true;
    view.settle_pos[static_cast<std::size_t>(idx)] =
        bounce::core::engine::position_at_time(state, dt);
    return;
  }
  const auto contact_pos = bounce::core::engine::position_at_time(state, dt);
  state.x0 = contact_pos.x;
  state.y0 = contact_pos.y;
  state.vx = reflected.vx;
  state.vy = reflected.vy;
  view.arc_start_t[static_cast<std::size_t>(idx)] = event.t;
}

double neighborhood_margin(const bounce::core::scenario::CalibrationScenario& scenario) {
  const double domain_span = scenario.domain_max - scenario.domain_min;
  return std::max(2.0, 0.18 * domain_span);
}

void include_curve_neighborhood_polynomial(const bounce::core::curve::CompiledPolynomial& curve_y,
                                           double x_center, double margin, double domain_min,
                                           double domain_max, Viewport& vp) {
  const double x_lo = std::max(domain_min, x_center - margin);
  const double x_hi = std::min(domain_max, x_center + margin);
  const int samples = 48;
  for (int i = 0; i <= samples; ++i) {
    const double x = x_lo + (x_hi - x_lo) * static_cast<double>(i) / static_cast<double>(samples);
    const double y = bounce::core::curve::eval(curve_y, x);
    vp.x_min = std::min(vp.x_min, x);
    vp.x_max = std::max(vp.x_max, x);
    vp.y_min = std::min(vp.y_min, y);
    vp.y_max = std::max(vp.y_max, y);
  }
}

void include_curve_neighborhood_bezier(
    const bounce::core::curve::CompiledPiecewiseBezier& curve, double x_center, double margin,
    Viewport& vp) {
  const auto anchor = locate_bezier_display_point(curve, x_center);
  if (anchor.found && anchor.segment_index < curve.segments.size()) {
    const auto pos =
        bounce::core::curve::eval(curve.segments[anchor.segment_index], anchor.segment_s);
    vp.x_min = std::min(vp.x_min, pos.x);
    vp.x_max = std::max(vp.x_max, pos.x);
    vp.y_min = std::min(vp.y_min, pos.y);
    vp.y_max = std::max(vp.y_max, pos.y);
  }
  for (const auto& segment : curve.segments) {
    for (int i = 0; i <= 64; ++i) {
      const double s = static_cast<double>(i) / 64.0;
      const auto pos = bounce::core::curve::eval(segment, s);
      if (pos.x < x_center - margin || pos.x > x_center + margin) {
        continue;
      }
      vp.x_min = std::min(vp.x_min, pos.x);
      vp.x_max = std::max(vp.x_max, pos.x);
      vp.y_min = std::min(vp.y_min, pos.y);
      vp.y_max = std::max(vp.y_max, pos.y);
    }
  }
}

void pad_viewport(Viewport& vp) {
  if (vp.y_max <= vp.y_min) {
    vp.y_max = vp.y_min + 1.0;
  }
  if (vp.x_max <= vp.x_min) {
    vp.x_max = vp.x_min + 1.0;
  }
  const double pad_x = 0.08 * (vp.x_max - vp.x_min);
  const double pad_y = 0.08 * (vp.y_max - vp.y_min);
  vp.x_min -= pad_x;
  vp.x_max += pad_x;
  vp.y_min -= pad_y;
  vp.y_max += pad_y;
}

void sample_polynomial_curve(const bounce::core::curve::CompiledPolynomial& curve_y,
                             const Viewport& vp, int window_w, int window_h,
                             std::vector<SDL_Point>& out) {
  out.clear();
  const int samples = std::max(window_w, 2);
  for (int i = 0; i < samples; ++i) {
    const double x = vp.x_min + (vp.x_max - vp.x_min) * static_cast<double>(i) /
                                    static_cast<double>(samples - 1);
    const double y = bounce::core::curve::eval(curve_y, x);
    out.push_back(to_screen(x, y, vp, window_w, window_h));
  }
}

void sample_bezier_curve(const bounce::core::curve::CompiledPiecewiseBezier& curve,
                         const Viewport& vp, int window_w, int window_h,
                         std::vector<SDL_Point>& out) {
  out.clear();
  for (const auto& segment : curve.segments) {
    for (int i = 0; i <= 128; ++i) {
      const double s = static_cast<double>(i) / 128.0;
      const auto pos = bounce::core::curve::eval(segment, s);
      out.push_back(to_screen(pos.x, pos.y, vp, window_w, window_h));
    }
  }
}

} // namespace

void reset_playback_view(PlaybackView& view) {
  view.next_event = 0;
  for (int i = 0; i < view.pb.scenario.ball_count; ++i) {
    view.current[static_cast<std::size_t>(i)] = view.pb.inits[static_cast<std::size_t>(i)];
    view.arc_start_t[static_cast<std::size_t>(i)] = 0.0;
    view.settled[static_cast<std::size_t>(i)] = view.pb.inits[static_cast<std::size_t>(i)].vx == 0.0;
    view.settle_pos[static_cast<std::size_t>(i)] = {};
  }
}

void seek_playback_view(PlaybackView& view, double t) {
  reset_playback_view(view);
  while (view.next_event < view.pb.events.size() && view.pb.events[view.next_event].t <= t + 1e-15) {
    apply_event_to_view(view, view.pb.events[view.next_event]);
    ++view.next_event;
  }
}

BallRenderState ball_state_in_view(const PlaybackView& view, int ball_id, double t) {
  BallRenderState out{};
  if (ball_id < 0 || ball_id >= view.pb.scenario.ball_count) {
    out.visible = false;
    return out;
  }
  PlaybackView scratch = view;
  seek_playback_view(scratch, t);
  const std::size_t idx = static_cast<std::size_t>(ball_id);
  if (scratch.settled[idx]) {
    out.pos = scratch.settle_pos[idx];
    out.settled = true;
    return out;
  }
  const double dt = t - scratch.arc_start_t[idx];
  if (dt < 0.0) {
    out.pos = bounce::core::engine::position_at_time(scratch.pb.inits[idx], 0.0);
    return out;
  }
  out.pos = bounce::core::engine::position_at_time(scratch.current[idx], dt);
  return out;
}

Viewport compute_viewport_targets(const PlaybackView& view, double t) {
  const auto& scenario = view.pb.scenario;
  Viewport vp{};
  bool have_bounds = false;
  const double margin = neighborhood_margin(scenario);

  bounce::core::curve::CompiledPolynomial curve_y{};
  const bool is_poly =
      scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial;
  if (is_poly) {
    curve_y = bounce::core::curve::compile_polynomial(
        std::vector<double>(scenario.coeffs.begin(),
                            scenario.coeffs.begin() + scenario.coeff_count));
  }

  for (int b = 0; b < scenario.ball_count; ++b) {
    const auto state = ball_state_in_view(view, b, t);
    if (!state.visible) {
      continue;
    }
    if (!have_bounds) {
      vp.x_min = vp.x_max = state.pos.x;
      vp.y_min = vp.y_max = state.pos.y;
      have_bounds = true;
    } else {
      vp.x_min = std::min(vp.x_min, state.pos.x);
      vp.x_max = std::max(vp.x_max, state.pos.x);
      vp.y_min = std::min(vp.y_min, state.pos.y);
      vp.y_max = std::max(vp.y_max, state.pos.y);
    }
    if (is_poly) {
      include_curve_neighborhood_polynomial(curve_y, state.pos.x, margin, scenario.domain_min,
                                            scenario.domain_max, vp);
    } else {
      include_curve_neighborhood_bezier(scenario.piecewise_bezier, state.pos.x, margin, vp);
    }
  }

  if (!have_bounds) {
    vp.x_min = scenario.domain_min;
    vp.x_max = scenario.domain_max;
    vp.y_min = 0.0;
    vp.y_max = 1.0;
  }
  pad_viewport(vp);
  return vp;
}

Viewport smooth_viewport(CameraState& camera, const Viewport& target, double alpha) {
  if (!camera.initialized) {
    camera.current = target;
    camera.initialized = true;
    return camera.current;
  }
  auto lerp = [alpha](double from, double to) { return from + alpha * (to - from); };
  camera.current.x_min = lerp(camera.current.x_min, target.x_min);
  camera.current.x_max = lerp(camera.current.x_max, target.x_max);
  camera.current.y_min = lerp(camera.current.y_min, target.y_min);
  camera.current.y_max = lerp(camera.current.y_max, target.y_max);
  return camera.current;
}

void build_scene_cache(const PlaybackView& view, double t, int window_w, int window_h,
                       SceneCache& cache, bool optimize, CameraState* camera) {
  const Viewport target = compute_viewport_targets(view, t);
  cache.viewport = camera != nullptr ? smooth_viewport(*camera, target) : target;

  cache.has_polynomial = false;
  cache.has_bezier = false;
  cache.curve_screen_points.clear();

  if (view.pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    cache.has_polynomial = true;
    if (optimize) {
      cache.curve_y = bounce::core::curve::compile_polynomial(
          std::vector<double>(view.pb.scenario.coeffs.begin(),
                              view.pb.scenario.coeffs.begin() + view.pb.scenario.coeff_count));
      sample_polynomial_curve(cache.curve_y, cache.viewport, window_w, window_h,
                            cache.curve_screen_points);
    } else {
      const auto curve_y = bounce::core::curve::compile_polynomial(
          std::vector<double>(view.pb.scenario.coeffs.begin(),
                              view.pb.scenario.coeffs.begin() + view.pb.scenario.coeff_count));
      sample_polynomial_curve(curve_y, cache.viewport, window_w, window_h,
                              cache.curve_screen_points);
    }
  } else {
    cache.has_bezier = true;
    cache.curve_bezier = view.pb.scenario.piecewise_bezier;
    sample_bezier_curve(cache.curve_bezier, cache.viewport, window_w, window_h,
                        cache.curve_screen_points);
  }
}

void draw_scene(SDL_Renderer* renderer, const SceneCache& cache, const PlaybackView& view,
                double t, int window_w, int window_h, PerfStats* perf) {
  SDL_SetRenderDrawColor(renderer, 18, 20, 28, 255);
  SDL_RenderClear(renderer);

  const auto engine_start = Clock::now();
  std::vector<BallRenderState> balls(static_cast<std::size_t>(view.pb.scenario.ball_count));
  for (int b = 0; b < view.pb.scenario.ball_count; ++b) {
    balls[static_cast<std::size_t>(b)] = ball_state_in_view(view, b, t);
  }
  if (perf != nullptr) {
    record_subsystem(perf->engine_query, elapsed_ms(engine_start));
  }

  const auto curve_start = Clock::now();
  SDL_SetRenderDrawColor(renderer, 180, 180, 200, 255);
  if (!cache.curve_screen_points.empty()) {
    int prev_x = -1;
    int prev_y = -1;
    for (const auto& p : cache.curve_screen_points) {
      if (prev_x >= 0) {
        SDL_RenderDrawLine(renderer, prev_x, prev_y, p.x, p.y);
      }
      prev_x = p.x;
      prev_y = p.y;
    }
  }
  if (perf != nullptr) {
    record_subsystem(perf->curve_draw, elapsed_ms(curve_start));
  }

  const auto ball_start = Clock::now();
  for (int b = 0; b < view.pb.scenario.ball_count; ++b) {
    const auto& state = balls[static_cast<std::size_t>(b)];
    if (!state.visible) {
      continue;
    }
    const auto p = to_screen(state.pos.x, state.pos.y, cache.viewport, window_w, window_h);
    if (state.settled) {
      SDL_SetRenderDrawColor(renderer, 100, 180, 220, 255);
      SDL_Rect outer{p.x - 7, p.y - 7, 14, 14};
      SDL_RenderDrawRect(renderer, &outer);
      SDL_SetRenderDrawColor(renderer, 80, 140, 180, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 240, 90, 60, 255);
    }
    SDL_Rect rect{p.x - 5, p.y - 5, 10, 10};
    SDL_RenderFillRect(renderer, &rect);
  }
  if (perf != nullptr) {
    record_subsystem(perf->ball_draw, elapsed_ms(ball_start));
  }
}

std::vector<FrameCheckResult> compute_frame_checks(const SceneCache& cache,
                                                   const PlaybackView& view, double t,
                                                   int window_w, int window_h) {
  std::vector<FrameCheckResult> results;
  for (int b = 0; b < view.pb.scenario.ball_count; ++b) {
    const auto state = ball_state_in_view(view, b, t);
    if (!state.visible) {
      continue;
    }
    const auto p = to_screen(state.pos.x, state.pos.y, cache.viewport, window_w, window_h);
    FrameCheckResult row{};
    row.ball_id = b;
    row.ball_px_x = p.x;
    row.ball_px_y = p.y;
    row.in_viewport = p.x >= 0 && p.x < window_w && p.y >= 0 && p.y < window_h;
    results.push_back(row);
  }

  int curve_pixels = 0;
  if (!results.empty()) {
    results.front().curve_pixels = 0;
  }
  auto mark = [&](int px, int py) {
    if (px >= 0 && px < window_w && py >= 0 && py < window_h) {
      ++curve_pixels;
    }
  };
  if (!cache.curve_screen_points.empty()) {
    int prev_x = -1;
    int prev_y = -1;
    for (const auto& p : cache.curve_screen_points) {
      if (prev_x >= 0) {
        const int steps = std::max(std::abs(p.x - prev_x), std::abs(p.y - prev_y));
        for (int s = 0; s <= steps; ++s) {
          const double u = steps == 0 ? 0.0 : static_cast<double>(s) / static_cast<double>(steps);
          mark(static_cast<int>(prev_x + u * (p.x - prev_x)),
               static_cast<int>(prev_y + u * (p.y - prev_y)));
        }
      }
      prev_x = p.x;
      prev_y = p.y;
    }
  }
  if (!results.empty()) {
    results.front().curve_pixels = curve_pixels;
  } else {
    FrameCheckResult row{};
    row.curve_pixels = curve_pixels;
    results.push_back(row);
  }
  return results;
}

} // namespace bounce_view
