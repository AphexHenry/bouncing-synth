// SPDX-License-Identifier: GPL-3.0-only
#include "selftest.hpp"

#include "av_mapping.hpp"
#include "build_stamp.hpp"
#include "ppm_writer.hpp"
#include "restitution_config.hpp"
#include "scene.hpp"

#include <SDL.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace bounce_view {

namespace {

constexpr int kDefaultSelftestMaxEvents = 200;
constexpr int kFrameWidth = 800;
constexpr int kFrameHeight = 600;

std::vector<double> parse_frame_times(const char* spec) {
  std::vector<double> out;
  if (spec == nullptr || spec[0] == '\0') {
    return out;
  }
  std::stringstream ss(spec);
  std::string token;
  while (std::getline(ss, token, ',')) {
    out.push_back(std::stod(token));
  }
  return out;
}

void print_frame_checks(const std::vector<FrameCheckResult>& checks) {
  int curve_pixels = 0;
  bool printed_grid = false;
  for (const auto& row : checks) {
    if (row.ball_id >= 0) {
      std::cout << "frame_check ball_id=" << row.ball_id << " ball_px=(" << row.ball_px_x << ','
                << row.ball_px_y << ") in_viewport=" << (row.in_viewport ? "true" : "false")
                << " ball_on_curve_px_dist=" << std::setprecision(17) << row.ball_on_curve_px_dist
                << " ball_radius_px=" << row.ball_radius_px << " ball_draw_px=" << row.ball_draw_px
                << " scale=" << row.scale << " scale_x=" << row.scale_x << " scale_y=" << row.scale_y
                << " camera_level=" << row.camera_level << " camera_scale=" << row.camera_scale
                << '\n';
    }
    if (!printed_grid) {
      std::cout << "frame_check grid_step=" << std::setprecision(17) << row.grid_step
                << " grid_lines_v=" << row.grid_lines_v << " grid_lines_h=" << row.grid_lines_h
                << '\n';
      printed_grid = true;
    }
    curve_pixels = row.curve_pixels;
  }
  std::cout << "frame_check curve_pixels=" << curve_pixels << '\n';
}

SDL_Point to_screen(double x, double y, const Viewport& vp, int window_w, int window_h) {
  SDL_Point p{};
  p.x = static_cast<int>((x - vp.x_min) / (vp.x_max - vp.x_min) * static_cast<double>(window_w - 1));
  p.y = static_cast<int>((vp.y_max - y) / (vp.y_max - vp.y_min) * static_cast<double>(window_h - 1));
  return p;
}

int count_curve_pixels_rgb(const std::vector<std::uint8_t>& rgb, int width, int height) {
  int count = 0;
  for (int py = 0; py < height; ++py) {
    for (int px = 0; px < width; ++px) {
      const std::size_t idx = static_cast<std::size_t>((py * width + px) * 3);
      if (rgb[idx] == 180 && rgb[idx + 1] == 180 && rgb[idx + 2] == 200) {
        ++count;
      }
    }
  }
  return count;
}

std::vector<std::uint8_t> render_frame_rgb(const Playback& pb, double t, CameraState& camera,
                                           std::vector<FrameCheckResult>* checks_out) {
  std::vector<std::uint8_t> rgb(static_cast<std::size_t>(kFrameWidth * kFrameHeight * 3), 24);

  PlaybackView view{};
  view.pb = pb;
  reset_playback_view(view);
  SceneCache cache{};
  build_scene_cache(view, t, kFrameWidth, kFrameHeight, cache, true, &camera);

  Playback render_pb = pb;
  reset_playback(render_pb);
  advance_playback_to(render_pb, t);

  auto plot = [&](int px, int py, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    if (px < 0 || py < 0 || px >= kFrameWidth || py >= kFrameHeight) {
      return;
    }
    const std::size_t idx = static_cast<std::size_t>((py * kFrameWidth + px) * 3);
    rgb[idx] = r;
    rgb[idx + 1] = g;
    rgb[idx + 2] = b;
  };

  if (!cache.curve_screen_points.empty()) {
    int prev_x = -1;
    int prev_y = -1;
    for (const auto& p : cache.curve_screen_points) {
      if (prev_x >= 0) {
        const int steps = std::max(std::abs(p.x - prev_x), std::abs(p.y - prev_y));
        for (int s = 0; s <= steps; ++s) {
          const double u = steps == 0 ? 0.0 : static_cast<double>(s) / static_cast<double>(steps);
          plot(static_cast<int>(prev_x + u * (p.x - prev_x)),
               static_cast<int>(prev_y + u * (p.y - prev_y)), 180, 180, 200);
        }
      }
      prev_x = p.x;
      prev_y = p.y;
    }
  }

  for (int b = 0; b < render_pb.scenario.ball_count; ++b) {
    const std::size_t idx = static_cast<std::size_t>(b);
    bounce::core::engine::Vec2 pos{};
    bool settled = false;
    if (render_pb.settled[idx]) {
      pos = render_pb.settle_pos[idx];
      settled = true;
    } else {
      const double dt = t - render_pb.arc_start_t[idx];
      pos = bounce::core::engine::position_at_time(render_pb.current[idx], std::max(0.0, dt));
    }
    const auto p = to_screen(pos.x, pos.y, cache.viewport, kFrameWidth, kFrameHeight);
    const double radius_world =
        b < static_cast<int>(render_pb.display_radius.size()) ? render_pb.display_radius[idx] : 0.1;
    const double radius_px = radius_world * cache.scale;
    const double draw_px = std::max(3.0, radius_px);
    const int rcore = std::max(1, static_cast<int>(std::lround(draw_px)));
    const std::uint8_t r = settled ? 80 : 240;
    const std::uint8_t g = settled ? 140 : 90;
    const std::uint8_t bl = settled ? 180 : 60;
    for (int dy = -rcore; dy <= rcore; ++dy) {
      for (int dx = -rcore; dx <= rcore; ++dx) {
        if (dx * dx + dy * dy <= rcore * rcore) {
          plot(p.x + dx, p.y + dy, r, g, bl);
        }
      }
    }
    if (radius_px < 3.0) {
      const int ring = rcore + 2;
      for (int a = 0; a < 24; ++a) {
        const double ang = 2.0 * 3.14159265358979323846 * static_cast<double>(a) / 24.0;
        plot(p.x + static_cast<int>(std::lround(ring * std::cos(ang))),
             p.y + static_cast<int>(std::lround(ring * std::sin(ang))), 255, 220, 120);
      }
    }
    if (settled) {
      for (int dy = -(rcore + 2); dy <= rcore + 2; ++dy) {
        for (int dx = -(rcore + 2); dx <= rcore + 2; ++dx) {
          if (std::abs(dx) == rcore + 2 || std::abs(dy) == rcore + 2) {
            plot(p.x + dx, p.y + dy, 100, 180, 220);
          }
        }
      }
    }
  }

  if (checks_out != nullptr) {
    *checks_out = compute_frame_checks(cache, view, t, kFrameWidth, kFrameHeight);
    const int curve_pixels = count_curve_pixels_rgb(rgb, kFrameWidth, kFrameHeight);
    if (!checks_out->empty()) {
      for (auto& row : *checks_out) {
        row.curve_pixels = curve_pixels;
      }
    } else {
      FrameCheckResult row{};
      row.curve_pixels = curve_pixels;
      checks_out->push_back(row);
    }
  }

  return rgb;
}

} // namespace

int run_selftest(const SelftestOptions& opts) {
  SDL_setenv("SDL_VIDEODRIVER", "dummy", 1);
  SDL_setenv("SDL_AUDIODRIVER", "dummy", 1);
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
    return 1;
  }

  print_build_stamp();
  print_restitution_line(opts.run_cfg);

  Playback pb{};
  std::string error;
  const int max_events =
      opts.run_cfg.max_events > 0 ? opts.run_cfg.max_events : kDefaultSelftestMaxEvents;
  if (!load_and_simulate(opts.scenario_path, pb, max_events, opts.run_cfg, error)) {
    std::cerr << error << '\n';
    SDL_Quit();
    return 1;
  }

  for (const auto& event : pb.events) {
    const auto blip = blip_params(pb.scenario, event);
    std::cout << event.seq << ' ' << event.ball_id << ' ' << std::setprecision(17) << event.t
              << ' ' << event.s << ' ' << blip.f_hz << ' ' << blip.amp << ' ' << blip.tau_ms << ' '
              << blip.k << '\n';
  }
  const double t_last = pb.events.empty() ? 0.0 : pb.events.back().t;
  if (static_cast<int>(pb.events.size()) < max_events) {
    std::cout << "diagnostic stream_ended_early=true events=" << pb.events.size()
              << " cap=" << max_events << '\n';
    if (!pb.events.empty()) {
      const auto& last = pb.events.back();
      std::cout << "diagnostic last_event ball_id=" << last.ball_id << " t=" << std::setprecision(17)
                << last.t << " s=" << last.s << " |vn|=" << last.impact_speed << '\n';
      Playback diag = pb;
      advance_playback_to(diag, last.t);
      for (int b = 0; b < pb.scenario.ball_count; ++b) {
        const auto state = ball_state_at(diag, b, last.t);
        std::cout << "diagnostic ball_id=" << b << " pos=(" << std::setprecision(17) << state.pos.x
                  << ',' << state.pos.y << ") domain=[" << pb.scenario.domain_min << ','
                  << pb.scenario.domain_max << "] settled="
                  << (diag.settled[static_cast<std::size_t>(b)] ? "true" : "false") << '\n';
      }
    }
  }
  std::cout << "selftest ok events=" << pb.events.size() << " t_last=" << std::setprecision(17)
            << t_last << '\n';

  CameraState camera{};
  const auto times = parse_frame_times(opts.frame_times);
  if (!times.empty() && opts.outdir != nullptr) {
    std::filesystem::create_directories(opts.outdir);
    for (std::size_t i = 0; i < times.size(); ++i) {
      const double t = times[i];
      std::vector<FrameCheckResult> checks;
      const auto rgb = render_frame_rgb(pb, t, camera, &checks);
      std::ostringstream name;
      name << opts.outdir << "/frame_" << i << ".ppm";
      if (!write_ppm(name.str().c_str(), kFrameWidth, kFrameHeight, rgb)) {
        std::cerr << "failed to write frame\n";
        SDL_Quit();
        return 1;
      }
      print_frame_checks(checks);
      std::cout << "frame_dump index=" << i << " t_frame=" << std::setprecision(17) << t << '\n';
    }
  } else if (opts.frames > 0 && opts.outdir != nullptr) {
    std::filesystem::create_directories(opts.outdir);
    const double t_end = std::max(pb.end_time, 0.1);
    for (int i = 0; i < opts.frames; ++i) {
      const double t = opts.frames == 1 ? 0.0
                                        : t_end * static_cast<double>(i) / static_cast<double>(opts.frames - 1);
      std::vector<FrameCheckResult> checks;
      const auto rgb = render_frame_rgb(pb, t, camera, &checks);
      std::ostringstream name;
      name << opts.outdir << "/frame_" << i << ".ppm";
      if (!write_ppm(name.str().c_str(), kFrameWidth, kFrameHeight, rgb)) {
        std::cerr << "failed to write frame\n";
        SDL_Quit();
        return 1;
      }
      print_frame_checks(checks);
    }
  }

  SDL_Quit();
  return 0;
}

} // namespace bounce_view
