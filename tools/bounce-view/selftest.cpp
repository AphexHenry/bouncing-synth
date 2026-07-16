// SPDX-License-Identifier: GPL-3.0-only
#include "selftest.hpp"

#include "av_mapping.hpp"
#include "ppm_writer.hpp"
#include "restitution_config.hpp"
#include "scene.hpp"

#include <SDL.h>

#include <algorithm>
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

std::vector<std::uint8_t> render_frame_rgb(const Playback& pb, double t) {
  std::vector<std::uint8_t> rgb(static_cast<std::size_t>(kFrameWidth * kFrameHeight * 3), 24);

  PlaybackView view{};
  view.pb = pb;
  reset_playback_view(view);
  SceneCache cache{};
  build_scene_cache(view, kFrameWidth, kFrameHeight, cache, true);

  Playback render_pb = pb;
  reset_playback(render_pb);
  advance_playback_to(render_pb, t);

  auto to_px = [&](double x, double y) {
    const int px = static_cast<int>((x - cache.viewport.x_min) /
                                    (cache.viewport.x_max - cache.viewport.x_min) *
                                    static_cast<double>(kFrameWidth - 1));
    const int py = static_cast<int>((cache.viewport.y_max - y) /
                                    (cache.viewport.y_max - cache.viewport.y_min) *
                                    static_cast<double>(kFrameHeight - 1));
    return std::pair<int, int>{px, py};
  };

  auto plot = [&](int px, int py, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    if (px < 0 || py < 0 || px >= kFrameWidth || py >= kFrameHeight) {
      return;
    }
    const std::size_t idx = static_cast<std::size_t>((py * kFrameWidth + px) * 3);
    rgb[idx] = r;
    rgb[idx + 1] = g;
    rgb[idx + 2] = b;
  };

  if (cache.has_polynomial) {
    for (const auto& p : cache.curve_screen_points) {
      plot(p.x, p.y, 180, 180, 200);
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
    const auto [px, py] = to_px(pos.x, pos.y);
    const std::uint8_t r = settled ? 80 : 240;
    const std::uint8_t g = settled ? 140 : 90;
    const std::uint8_t bl = settled ? 180 : 60;
    for (int dy = -4; dy <= 4; ++dy) {
      for (int dx = -4; dx <= 4; ++dx) {
        if (dx * dx + dy * dy <= 16) {
          plot(px + dx, py + dy, r, g, bl);
        }
      }
    }
    if (settled) {
      for (int dy = -6; dy <= 6; ++dy) {
        for (int dx = -6; dx <= 6; ++dx) {
          if (std::abs(dx) == 6 || std::abs(dy) == 6) {
            plot(px + dx, py + dy, 100, 180, 220);
          }
        }
      }
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
  std::cout << "selftest ok events=" << pb.events.size() << " t_last=" << std::setprecision(17)
            << t_last << '\n';

  const auto times = parse_frame_times(opts.frame_times);
  if (!times.empty() && opts.outdir != nullptr) {
    std::filesystem::create_directories(opts.outdir);
    for (std::size_t i = 0; i < times.size(); ++i) {
      const double t = times[i];
      const auto rgb = render_frame_rgb(pb, t);
      std::ostringstream name;
      name << opts.outdir << "/frame_" << i << ".ppm";
      if (!write_ppm(name.str().c_str(), kFrameWidth, kFrameHeight, rgb)) {
        std::cerr << "failed to write frame\n";
        SDL_Quit();
        return 1;
      }
      std::cout << "frame_dump index=" << i << " t_frame=" << std::setprecision(17) << t << '\n';
    }
  } else if (opts.frames > 0 && opts.outdir != nullptr) {
    std::filesystem::create_directories(opts.outdir);
    const double t_end = std::max(pb.end_time, 0.1);
    for (int i = 0; i < opts.frames; ++i) {
      const double t = opts.frames == 1 ? 0.0
                                        : t_end * static_cast<double>(i) / static_cast<double>(opts.frames - 1);
      const auto rgb = render_frame_rgb(pb, t);
      std::ostringstream name;
      name << opts.outdir << "/frame_" << i << ".ppm";
      if (!write_ppm(name.str().c_str(), kFrameWidth, kFrameHeight, rgb)) {
        std::cerr << "failed to write frame\n";
        SDL_Quit();
        return 1;
      }
    }
  }

  SDL_Quit();
  return 0;
}

} // namespace bounce_view
