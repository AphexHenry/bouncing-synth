// SPDX-License-Identifier: GPL-3.0-only
#include "scene.hpp"

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
  const auto& curve = pb.scenario.piecewise_bezier;
  const auto pos = bounce::core::curve::eval(curve.segments.front(), event.s);
  const auto n = bounce::core::curve::normal(curve.segments.front(), event.s);
  const double vn = state.vx * n.nx + vy_contact * n.ny;
  const double restitution = pb.scenario.balls[static_cast<std::size_t>(idx)].restitution;
  bounce::core::engine::ReflectedVelocity reflected{};
  reflected.vx = state.vx - (1.0 + restitution) * vn * n.nx;
  reflected.vy = vy_contact - (1.0 + restitution) * vn * n.ny;
  reflected.normal_speed_out = std::abs(vn);
  if (reflected.normal_speed_out < bounce::core::engine::kVSettle) {
    view.settled[static_cast<std::size_t>(idx)] = true;
    view.settle_pos[static_cast<std::size_t>(idx)] =
        bounce::core::engine::position_at_time(state, dt);
    return;
  }
  state.x0 = pos.x;
  state.y0 = pos.y;
  state.vx = reflected.vx;
  state.vy = reflected.vy;
  view.arc_start_t[static_cast<std::size_t>(idx)] = event.t;
}

Viewport compute_viewport(const PlaybackView& view, double t) {
  const auto& pb = view.pb;
  Viewport vp{};
  vp.x_min = pb.scenario.domain_min;
  vp.x_max = pb.scenario.domain_max;
  vp.y_min = 0.0;
  vp.y_max = 1.0;
  if (pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    const auto curve_y = bounce::core::curve::compile_polynomial(
        std::vector<double>(pb.scenario.coeffs.begin(),
                            pb.scenario.coeffs.begin() + pb.scenario.coeff_count));
    for (int i = 0; i <= 128; ++i) {
      const double x = vp.x_min + (vp.x_max - vp.x_min) * static_cast<double>(i) / 128.0;
      vp.y_min = std::min(vp.y_min, bounce::core::curve::eval(curve_y, x));
      vp.y_max = std::max(vp.y_max, bounce::core::curve::eval(curve_y, x));
    }
  }
  for (int b = 0; b < pb.scenario.ball_count; ++b) {
    const auto state = ball_state_in_view(view, b, t);
    if (!state.visible) {
      continue;
    }
    vp.x_min = std::min(vp.x_min, state.pos.x);
    vp.x_max = std::max(vp.x_max, state.pos.x);
    vp.y_min = std::min(vp.y_min, state.pos.y);
    vp.y_max = std::max(vp.y_max, state.pos.y);
  }
  if (vp.y_max <= vp.y_min) {
    vp.y_max = vp.y_min + 1.0;
  }
  if (vp.x_max <= vp.x_min) {
    vp.x_max = vp.x_min + 1.0;
  }
  const double pad_x = 0.05 * (vp.x_max - vp.x_min);
  const double pad_y = 0.05 * (vp.y_max - vp.y_min);
  vp.x_min -= pad_x;
  vp.x_max += pad_x;
  vp.y_min -= pad_y;
  vp.y_max += pad_y;
  return vp;
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

void build_scene_cache(const PlaybackView& view, int window_w, int window_h, SceneCache& cache,
                       bool optimize) {
  cache.viewport = compute_viewport(view, view.pb.end_time);
  cache.curve_screen_points.clear();
  if (view.pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    cache.has_polynomial = true;
    if (optimize) {
      cache.curve_y = bounce::core::curve::compile_polynomial(
          std::vector<double>(view.pb.scenario.coeffs.begin(),
                              view.pb.scenario.coeffs.begin() + view.pb.scenario.coeff_count));
    }
    const int samples = optimize ? window_w : window_w;
    for (int i = 0; i < samples; ++i) {
      const double x = cache.viewport.x_min +
                       (cache.viewport.x_max - cache.viewport.x_min) * static_cast<double>(i) /
                           static_cast<double>(samples - 1);
      double y = 0.0;
      if (optimize) {
        y = bounce::core::curve::eval(cache.curve_y, x);
      } else {
        const auto curve_y = bounce::core::curve::compile_polynomial(
            std::vector<double>(view.pb.scenario.coeffs.begin(),
                                view.pb.scenario.coeffs.begin() + view.pb.scenario.coeff_count));
        y = bounce::core::curve::eval(curve_y, x);
      }
      cache.curve_screen_points.push_back(to_screen(x, y, cache.viewport, window_w, window_h));
    }
  } else {
    cache.has_polynomial = false;
  }
}

void draw_scene(SDL_Renderer* renderer, const SceneCache& cache, const PlaybackView& view,
                double t, PerfStats* perf) {
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
  if (cache.has_polynomial && !cache.curve_screen_points.empty()) {
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
    const auto p = to_screen(state.pos.x, state.pos.y, cache.viewport, 800, 600);
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

} // namespace bounce_view
