// SPDX-License-Identifier: GPL-3.0-only
#include "selftest.hpp"

#include "av_mapping.hpp"
#include "ppm_writer.hpp"

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

constexpr int kSelftestMaxEvents = 200;
constexpr int kFrameWidth = 800;
constexpr int kFrameHeight = 600;

std::vector<std::uint8_t> render_frame_rgb(const Playback& pb, double t) {
  std::vector<std::uint8_t> rgb(static_cast<std::size_t>(kFrameWidth * kFrameHeight * 3), 24);

  double x_min = pb.scenario.domain_min;
  double x_max = pb.scenario.domain_max;
  double y_min = 0.0;
  double y_max = 1.0;

  if (pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    const auto curve_y = bounce::core::curve::compile_polynomial(
        std::vector<double>(pb.scenario.coeffs.begin(),
                            pb.scenario.coeffs.begin() + pb.scenario.coeff_count));
    const int samples = 128;
    for (int i = 0; i <= samples; ++i) {
      const double x = x_min + (x_max - x_min) * static_cast<double>(i) / static_cast<double>(samples);
      y_min = std::min(y_min, bounce::core::curve::eval(curve_y, x));
      y_max = std::max(y_max, bounce::core::curve::eval(curve_y, x));
    }
  }
  for (int b = 0; b < pb.scenario.ball_count; ++b) {
    const auto state = ball_state_at(pb, b, t);
    x_min = std::min(x_min, state.pos.x);
    x_max = std::max(x_max, state.pos.x);
    y_min = std::min(y_min, state.pos.y);
    y_max = std::max(y_max, state.pos.y);
  }
  if (y_max <= y_min) {
    y_max = y_min + 1.0;
  }
  if (x_max <= x_min) {
    x_max = x_min + 1.0;
  }
  const double pad_x = 0.05 * (x_max - x_min);
  const double pad_y = 0.05 * (y_max - y_min);
  x_min -= pad_x;
  x_max += pad_x;
  y_min -= pad_y;
  y_max += pad_y;

  auto to_px = [&](double x, double y) {
    const int px = static_cast<int>((x - x_min) / (x_max - x_min) * static_cast<double>(kFrameWidth - 1));
    const int py = static_cast<int>((y_max - y) / (y_max - y_min) * static_cast<double>(kFrameHeight - 1));
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

  if (pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    const auto curve_y = bounce::core::curve::compile_polynomial(
        std::vector<double>(pb.scenario.coeffs.begin(),
                            pb.scenario.coeffs.begin() + pb.scenario.coeff_count));
    for (int i = 0; i < kFrameWidth; ++i) {
      const double x = x_min + (x_max - x_min) * static_cast<double>(i) / static_cast<double>(kFrameWidth - 1);
      const auto [px, py] = to_px(x, bounce::core::curve::eval(curve_y, x));
      plot(px, py, 180, 180, 200);
    }
  }

  for (int b = 0; b < pb.scenario.ball_count; ++b) {
    const auto state = ball_state_at(pb, b, t);
    const auto [px, py] = to_px(state.pos.x, state.pos.y);
    for (int dy = -4; dy <= 4; ++dy) {
      for (int dx = -4; dx <= 4; ++dx) {
        if (dx * dx + dy * dy <= 16) {
          plot(px + dx, py + dy, 240, 90, 60);
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

  Playback pb{};
  std::string error;
  if (!load_and_simulate(opts.scenario_path, pb, kSelftestMaxEvents, error)) {
    std::cerr << error << '\n';
    SDL_Quit();
    return 1;
  }

  for (const auto& event : pb.events) {
    const auto blip = blip_params(pb.scenario, event);
    std::cout << event.seq << ' ' << event.ball_id << ' ' << std::setprecision(17) << event.t
              << ' ' << event.s << ' ' << blip.f_hz << ' ' << blip.amp << '\n';
  }
  std::cout << "selftest ok events=" << pb.events.size() << '\n';

  if (opts.frames > 0 && opts.outdir != nullptr) {
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
