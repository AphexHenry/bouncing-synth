// SPDX-License-Identifier: GPL-3.0-only
#include "scene.hpp"

#include "bezier_display_geometry.hpp"
#include "perf.hpp"

#include <SDL.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace bounce_view {

double nice_grid_step_for_viewport(const Viewport& vp); // defined below

namespace {

using Clock = std::chrono::steady_clock;

constexpr double kZoomBase = 1.25;
constexpr double kComfortHi = 0.98; // zoom out only when content nearly overflows
constexpr double kComfortLo = 0.35; // zoom in only when content is sparse
constexpr double kPanAlpha = 0.12;
constexpr double kMinBallDrawPx = 3.0;

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
        eval_bezier_at_contact_x(pb.scenario.piecewise_bezier, event.s);
    return;
  }
  const auto curve_pos = eval_bezier_at_contact_x(pb.scenario.piecewise_bezier, event.s);
  state.x0 = curve_pos.x;
  state.y0 = curve_pos.y;
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

double point_segment_distance_px(int px, int py, int x0, int y0, int x1, int y1) {
  const double dx = static_cast<double>(x1 - x0);
  const double dy = static_cast<double>(y1 - y0);
  if (dx == 0.0 && dy == 0.0) {
    return std::hypot(static_cast<double>(px - x0), static_cast<double>(py - y0));
  }
  const double t = std::clamp(((px - x0) * dx + (py - y0) * dy) / (dx * dx + dy * dy), 0.0, 1.0);
  const double cx = static_cast<double>(x0) + t * dx;
  const double cy = static_cast<double>(y0) + t * dy;
  return std::hypot(static_cast<double>(px) - cx, static_cast<double>(py) - cy);
}

double min_curve_pixel_distance(int px, int py, const std::vector<SDL_Point>& curve_points) {
  if (curve_points.empty()) {
    return 0.0;
  }
  double best = std::numeric_limits<double>::infinity();
  int prev_x = -1;
  int prev_y = -1;
  for (const auto& p : curve_points) {
    if (prev_x >= 0) {
      best = std::min(best, point_segment_distance_px(px, py, prev_x, prev_y, p.x, p.y));
    }
    prev_x = p.x;
    prev_y = p.y;
  }
  return best;
}

double scale_at_level(double s_base, int level) {
  return s_base * std::pow(kZoomBase, static_cast<double>(level));
}

void rebuild_viewport_from_camera(CameraState& camera, int window_w, int window_h) {
  camera.scale = scale_at_level(camera.s_base, camera.level);
  const double view_w = static_cast<double>(window_w - 1) / std::max(1e-12, camera.scale);
  const double view_h = static_cast<double>(window_h - 1) / std::max(1e-12, camera.scale);
  camera.current.x_min = camera.center_x - 0.5 * view_w;
  camera.current.x_max = camera.center_x + 0.5 * view_w;
  camera.current.y_min = camera.center_y - 0.5 * view_h;
  camera.current.y_max = camera.center_y + 0.5 * view_h;
  camera.scale_x = camera.scale;
  camera.scale_y = camera.scale;
  camera.grid_step = nice_grid_step_for_viewport(camera.current);
  count_grid_lines(camera.current, camera.grid_step, camera.grid_lines_v, camera.grid_lines_h);
}

// Minimal 5x7 glyphs: digits, minus, dot, 'e'. Bits row-major, MSB left.
constexpr int kGlyphW = 5;
constexpr int kGlyphH = 7;

const char* glyph_bits(char c) {
  switch (c) {
  case '0':
    return "01110"
           "10001"
           "10011"
           "10101"
           "11001"
           "10001"
           "01110";
  case '1':
    return "00100"
           "01100"
           "00100"
           "00100"
           "00100"
           "00100"
           "01110";
  case '2':
    return "01110"
           "10001"
           "00001"
           "00010"
           "00100"
           "01000"
           "11111";
  case '3':
    return "01110"
           "10001"
           "00001"
           "00110"
           "00001"
           "10001"
           "01110";
  case '4':
    return "00010"
           "00110"
           "01010"
           "10010"
           "11111"
           "00010"
           "00010";
  case '5':
    return "11111"
           "10000"
           "11110"
           "00001"
           "00001"
           "10001"
           "01110";
  case '6':
    return "00110"
           "01000"
           "10000"
           "11110"
           "10001"
           "10001"
           "01110";
  case '7':
    return "11111"
           "00001"
           "00010"
           "00100"
           "01000"
           "01000"
           "01000";
  case '8':
    return "01110"
           "10001"
           "10001"
           "01110"
           "10001"
           "10001"
           "01110";
  case '9':
    return "01110"
           "10001"
           "10001"
           "01111"
           "00001"
           "00010"
           "01100";
  case '-':
    return "00000"
           "00000"
           "00000"
           "11111"
           "00000"
           "00000"
           "00000";
  case '.':
    return "00000"
           "00000"
           "00000"
           "00000"
           "00000"
           "00100"
           "00100";
  case 'e':
    return "00000"
           "00000"
           "01110"
           "10001"
           "11111"
           "10000"
           "01110";
  case ' ':
    return "00000"
           "00000"
           "00000"
           "00000"
           "00000"
           "00000"
           "00000";
  default:
    return "11111"
           "10001"
           "10001"
           "10001"
           "10001"
           "10001"
           "11111";
  }
}

void draw_glyph(SDL_Renderer* renderer, int x, int y, char c, int scale) {
  const char* bits = glyph_bits(c);
  for (int row = 0; row < kGlyphH; ++row) {
    for (int col = 0; col < kGlyphW; ++col) {
      if (bits[row * kGlyphW + col] == '1') {
        SDL_Rect r{x + col * scale, y + row * scale, scale, scale};
        SDL_RenderFillRect(renderer, &r);
      }
    }
  }
}

void draw_text(SDL_Renderer* renderer, int x, int y, const std::string& text, int scale = 1) {
  int cursor = x;
  for (char c : text) {
    draw_glyph(renderer, cursor, y, c, scale);
    cursor += (kGlyphW + 1) * scale;
  }
}

std::string format_tick(double v) {
  // Compact label: prefer fixed, fall back to scientific-ish with 'e'.
  char buf[64];
  const double av = std::abs(v);
  if (av != 0.0 && (av >= 1e4 || av < 1e-3)) {
    std::snprintf(buf, sizeof(buf), "%.2e", v);
  } else {
    std::snprintf(buf, sizeof(buf), "%.3g", v);
  }
  std::string s(buf);
  for (char& c : s) {
    if (c == 'E') {
      c = 'e';
    }
  }
  return s;
}

void draw_grid_and_axes(SDL_Renderer* renderer, const CameraState& camera, int window_w,
                        int window_h) {
  const Viewport& vp = camera.current;
  const double step = camera.grid_step;
  if (!(step > 0.0)) {
    return;
  }

  const double x0 = std::ceil(vp.x_min / step) * step;
  const double y0 = std::ceil(vp.y_min / step) * step;

  SDL_SetRenderDrawColor(renderer, 40, 44, 56, 255);
  for (double x = x0; x <= vp.x_max + 1e-12; x += step) {
    const auto a = to_screen(x, vp.y_min, vp, window_w, window_h);
    const auto b = to_screen(x, vp.y_max, vp, window_w, window_h);
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
  }
  for (double y = y0; y <= vp.y_max + 1e-12; y += step) {
    const auto a = to_screen(vp.x_min, y, vp, window_w, window_h);
    const auto b = to_screen(vp.x_max, y, vp, window_w, window_h);
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
  }

  // Emphasize world axes when in view.
  SDL_SetRenderDrawColor(renderer, 90, 100, 130, 255);
  if (vp.x_min <= 0.0 && vp.x_max >= 0.0) {
    const auto a = to_screen(0.0, vp.y_min, vp, window_w, window_h);
    const auto b = to_screen(0.0, vp.y_max, vp, window_w, window_h);
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
  }
  if (vp.y_min <= 0.0 && vp.y_max >= 0.0) {
    const auto a = to_screen(vp.x_min, 0.0, vp, window_w, window_h);
    const auto b = to_screen(vp.x_max, 0.0, vp, window_w, window_h);
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
  }

  SDL_SetRenderDrawColor(renderer, 160, 170, 190, 255);
  for (double x = x0; x <= vp.x_max + 1e-12; x += step) {
    const auto p = to_screen(x, std::clamp(0.0, vp.y_min, vp.y_max), vp, window_w, window_h);
    draw_text(renderer, p.x + 2, std::min(window_h - 12, p.y + 2), format_tick(x), 1);
  }
  for (double y = y0; y <= vp.y_max + 1e-12; y += step) {
    const auto p = to_screen(std::clamp(0.0, vp.x_min, vp.x_max), y, vp, window_w, window_h);
    draw_text(renderer, std::max(2, p.x + 2), p.y - 8, format_tick(y), 1);
  }

  // Screen-space scale bar (bottom-left).
  const double bar_world = step;
  const int bar_px = std::max(1, static_cast<int>(std::lround(bar_world * camera.scale)));
  const int bar_x = 16;
  const int bar_y = window_h - 28;
  SDL_SetRenderDrawColor(renderer, 220, 220, 230, 255);
  SDL_RenderDrawLine(renderer, bar_x, bar_y, bar_x + bar_px, bar_y);
  SDL_RenderDrawLine(renderer, bar_x, bar_y - 3, bar_x, bar_y + 3);
  SDL_RenderDrawLine(renderer, bar_x + bar_px, bar_y - 3, bar_x + bar_px, bar_y + 3);
  draw_text(renderer, bar_x, bar_y + 6, format_tick(bar_world), 1);
}

void draw_ball_at(SDL_Renderer* renderer, int cx, int cy, double radius_world, double scale,
                  bool settled) {
  const double radius_px = radius_world * scale;
  const double draw_px = std::max(kMinBallDrawPx, radius_px);
  const bool marker = radius_px < kMinBallDrawPx;
  const int r = std::max(1, static_cast<int>(std::lround(draw_px)));

  if (settled) {
    SDL_SetRenderDrawColor(renderer, 100, 180, 220, 255);
    SDL_Rect outer{cx - r - 2, cy - r - 2, 2 * r + 4, 2 * r + 4};
    SDL_RenderDrawRect(renderer, &outer);
    SDL_SetRenderDrawColor(renderer, 80, 140, 180, 255);
  } else {
    SDL_SetRenderDrawColor(renderer, 240, 90, 60, 255);
  }
  for (int dy = -r; dy <= r; ++dy) {
    for (int dx = -r; dx <= r; ++dx) {
      if (dx * dx + dy * dy <= r * r) {
        SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
      }
    }
  }
  if (marker) {
    SDL_SetRenderDrawColor(renderer, 255, 220, 120, 255);
    const int ring = r + 2;
    for (int a = 0; a < 32; ++a) {
      const double ang = 2.0 * 3.14159265358979323846 * static_cast<double>(a) / 32.0;
      const int px = cx + static_cast<int>(std::lround(ring * std::cos(ang)));
      const int py = cy + static_cast<int>(std::lround(ring * std::sin(ang)));
      SDL_RenderDrawPoint(renderer, px, py);
    }
  }
}

} // namespace

double nice_grid_step(double view_span) {
  if (!(view_span > 0.0) || !std::isfinite(view_span)) {
    return 1.0;
  }
  // Target ~8 lines on the provided span; snap to 1-2-5 and adjust until [4,12].
  double approx = view_span / 8.0;
  auto snap = [](double v) {
    const double exp10 = std::floor(std::log10(v));
    const double base = std::pow(10.0, exp10);
    const double m = v / base;
    double nice_m = 1.0;
    if (m <= 1.5) {
      nice_m = 1.0;
    } else if (m <= 3.5) {
      nice_m = 2.0;
    } else if (m <= 7.5) {
      nice_m = 5.0;
    } else {
      return 10.0 * base;
    }
    return nice_m * base;
  };
  auto next_larger = [](double step) {
    const double exp10 = std::floor(std::log10(step) + 1e-12);
    const double base = std::pow(10.0, exp10);
    const double m = step / base;
    if (m < 1.5) {
      return 2.0 * base;
    }
    if (m < 3.5) {
      return 5.0 * base;
    }
    if (m < 7.5) {
      return 10.0 * base;
    }
    return 20.0 * base;
  };
  auto next_smaller = [](double step) {
    const double exp10 = std::floor(std::log10(step) + 1e-12);
    const double base = std::pow(10.0, exp10);
    const double m = step / base;
    if (m > 4.5) {
      return 2.0 * base;
    }
    if (m > 1.5) {
      return 1.0 * base;
    }
    return 0.5 * base;
  };

  double step = snap(approx);
  for (int i = 0; i < 8; ++i) {
    const int lines = static_cast<int>(std::floor(view_span / step)) + 1;
    if (lines < 4) {
      step = next_smaller(step);
    } else if (lines > 12) {
      step = next_larger(step);
    } else {
      break;
    }
  }
  return step;
}

// Choose one 1-2-5 step so BOTH axes land in [4,12] (window aspect is fixed 4:3).
double nice_grid_step_for_viewport(const Viewport& vp) {
  const double span_x = std::max(1e-12, vp.x_max - vp.x_min);
  const double span_y = std::max(1e-12, vp.y_max - vp.y_min);
  const double longer = std::max(span_x, span_y);
  double step = nice_grid_step(longer);
  auto next_larger = [](double s) {
    const double exp10 = std::floor(std::log10(s) + 1e-12);
    const double base = std::pow(10.0, exp10);
    const double m = s / base;
    if (m < 1.5) {
      return 2.0 * base;
    }
    if (m < 3.5) {
      return 5.0 * base;
    }
    if (m < 7.5) {
      return 10.0 * base;
    }
    return 20.0 * base;
  };
  auto next_smaller = [](double s) {
    const double exp10 = std::floor(std::log10(s) + 1e-12);
    const double base = std::pow(10.0, exp10);
    const double m = s / base;
    if (m > 4.5) {
      return 2.0 * base;
    }
    if (m > 1.5) {
      return 1.0 * base;
    }
    return 0.5 * base;
  };
  for (int i = 0; i < 12; ++i) {
    int lv = 0;
    int lh = 0;
    count_grid_lines(vp, step, lv, lh);
    const int mn = std::min(lv, lh);
    const int mx = std::max(lv, lh);
    if (mn < 4) {
      step = next_smaller(step);
    } else if (mx > 12) {
      step = next_larger(step);
    } else {
      break;
    }
  }
  return step;
}

void count_grid_lines(const Viewport& vp, double step, int& lines_v, int& lines_h) {
  lines_v = 0;
  lines_h = 0;
  if (!(step > 0.0)) {
    return;
  }
  const double x0 = std::ceil(vp.x_min / step) * step;
  const double y0 = std::ceil(vp.y_min / step) * step;
  for (double x = x0; x <= vp.x_max + 1e-12; x += step) {
    ++lines_v;
  }
  for (double y = y0; y <= vp.y_max + 1e-12; y += step) {
    ++lines_h;
  }
}

bool update_camera(CameraState& camera, const Viewport& content, int window_w, int window_h) {
  Viewport padded = content;
  pad_viewport(padded);
  const double content_w = std::max(1e-9, padded.x_max - padded.x_min);
  const double content_h = std::max(1e-9, padded.y_max - padded.y_min);
  const double target_cx = 0.5 * (padded.x_min + padded.x_max);
  const double target_cy = 0.5 * (padded.y_min + padded.y_max);

  const int prev_level = camera.level;
  const double prev_scale = camera.scale;

  if (!camera.initialized) {
    camera.center_x = target_cx;
    camera.center_y = target_cy;
    const double fit =
        std::min(static_cast<double>(window_w - 1) / content_w,
                 static_cast<double>(window_h - 1) / content_h);
    // Level 0 targets ~70% fill (content inside view with margin).
    constexpr double kInitFill = 0.70;
    camera.s_base = std::max(1e-12, fit * kInitFill);
    camera.level = 0;
    camera.initialized = true;
    rebuild_viewport_from_camera(camera, window_w, window_h);
    return true;
  }

  if (!camera.locked) {
    camera.center_x = camera.center_x + kPanAlpha * (target_cx - camera.center_x);
    camera.center_y = camera.center_y + kPanAlpha * (target_cy - camera.center_y);

    // Fill fraction at current scale (max of axis fills).
    const double view_w =
        static_cast<double>(window_w - 1) / std::max(1e-12, scale_at_level(camera.s_base, camera.level));
    const double view_h =
        static_cast<double>(window_h - 1) / std::max(1e-12, scale_at_level(camera.s_base, camera.level));
    const double fill = std::max(content_w / view_w, content_h / view_h);
    // At most one level change per update (presentation-frame cadence).
    if (fill > kComfortHi) {
      --camera.level; // zoom out
    } else if (fill < kComfortLo) {
      ++camera.level; // zoom in
    }
  }

  rebuild_viewport_from_camera(camera, window_w, window_h);
  return camera.level != prev_level || std::abs(camera.scale - prev_scale) > 1e-15;
}

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
  return vp;
}

bool build_scene_cache(const PlaybackView& view, double t, int window_w, int window_h,
                       SceneCache& cache, bool optimize, CameraState* camera) {
  const Viewport target = compute_viewport_targets(view, t);
  CameraState local{};
  CameraState* cam = camera != nullptr ? camera : &local;
  const bool changed = update_camera(*cam, target, window_w, window_h);
  cache.viewport = cam->current;
  cache.scale = cam->scale;
  cache.scale_x = cam->scale_x;
  cache.scale_y = cam->scale_y;
  cache.camera_level = cam->level;
  cache.grid_step = cam->grid_step;
  cache.grid_lines_v = cam->grid_lines_v;
  cache.grid_lines_h = cam->grid_lines_h;

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
  return changed;
}

void draw_scene(SDL_Renderer* renderer, const SceneCache& cache, const PlaybackView& view,
                double t, int window_w, int window_h, PerfStats* perf) {
  SDL_SetRenderDrawColor(renderer, 18, 20, 28, 255);
  SDL_RenderClear(renderer);

  // Reconstruct camera fields for overlays from cache.
  CameraState overlay{};
  overlay.current = cache.viewport;
  overlay.scale = cache.scale;
  overlay.scale_x = cache.scale_x;
  overlay.scale_y = cache.scale_y;
  overlay.level = cache.camera_level;
  overlay.grid_step = cache.grid_step;
  overlay.grid_lines_v = cache.grid_lines_v;
  overlay.grid_lines_h = cache.grid_lines_h;
  overlay.initialized = true;
  draw_grid_and_axes(renderer, overlay, window_w, window_h);

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
    const double radius_world =
        b < static_cast<int>(view.pb.display_radius.size())
            ? view.pb.display_radius[static_cast<std::size_t>(b)]
            : 0.1;
    draw_ball_at(renderer, p.x, p.y, radius_world, cache.scale, state.settled);
  }
  if (perf != nullptr) {
    record_subsystem(perf->ball_draw, elapsed_ms(ball_start));
  }
}

void draw_hud_overlay(SDL_Renderer* renderer, const HudState& hud, int window_w, int window_h) {
  (void)window_w;
  char buf[256];
  std::snprintf(buf, sizeof(buf), "t=%.6g ev=%d r=%s cam=%s L=%d %s", hud.sim_t, hud.event_count,
                hud.restitution.c_str(), hud.camera_locked ? "locked" : "auto", hud.camera_level,
                hud.build_short.c_str());
  SDL_SetRenderDrawColor(renderer, 210, 215, 225, 255);
  draw_text(renderer, 8, 8, buf, 1);
  (void)window_h;
}

void print_hud_line(const HudState& hud) {
  std::cout << "hud: t=" << std::setprecision(17) << hud.sim_t << " events=" << hud.event_count
            << " restitution=" << hud.restitution
            << " camera=" << (hud.camera_locked ? "locked" : "auto")
            << " level=" << hud.camera_level << " build=" << hud.build_short << '\n';
}

void print_camera_line(const CameraState& camera) {
  std::cout << "camera: level=" << camera.level << " scale=" << std::setprecision(17)
            << camera.scale << '\n';
}

std::vector<FrameCheckResult> compute_frame_checks(const SceneCache& cache,
                                                   const PlaybackView& view, double t,
                                                   int window_w, int window_h) {
  const double scale_x = cache.scale_x;
  const double scale_y = cache.scale_y;
  const double scale = cache.scale;

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
    row.scale = scale;
    row.scale_x = scale_x;
    row.scale_y = scale_y;
    row.camera_level = cache.camera_level;
    row.camera_scale = cache.scale;
    row.grid_step = cache.grid_step;
    row.grid_lines_v = cache.grid_lines_v;
    row.grid_lines_h = cache.grid_lines_h;
    const double radius_world =
        b < static_cast<int>(view.pb.display_radius.size())
            ? view.pb.display_radius[static_cast<std::size_t>(b)]
            : 0.1;
    row.ball_radius_px = radius_world * scale;
    row.ball_draw_px = std::max(kMinBallDrawPx, row.ball_radius_px);
    row.ball_on_curve_px_dist = min_curve_pixel_distance(p.x, p.y, cache.curve_screen_points);
    results.push_back(row);
  }

  int curve_pixels = 0;
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
    row.scale_x = scale_x;
    row.scale_y = scale_y;
    row.camera_level = cache.camera_level;
    row.camera_scale = cache.scale;
    row.grid_step = cache.grid_step;
    row.grid_lines_v = cache.grid_lines_v;
    row.grid_lines_h = cache.grid_lines_h;
    results.push_back(row);
  }
  return results;
}

} // namespace bounce_view
