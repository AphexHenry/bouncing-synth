// SPDX-License-Identifier: GPL-3.0-only
#include "interactive.hpp"

#include "av_mapping.hpp"
#include "playback.hpp"
#include "selftest.hpp"

#include <SDL.h>

#include <cmath>
#include <iostream>
#include <vector>

namespace bounce_view {

namespace {

constexpr int kWindowW = 800;
constexpr int kWindowH = 600;

struct BlipVoice {
  double start_ms = 0.0;
  double freq_hz = 440.0;
  double amp = 0.0;
  bool active = false;
};

void draw_scene(SDL_Renderer* renderer, const Playback& pb, double t) {
  SDL_SetRenderDrawColor(renderer, 18, 20, 28, 255);
  SDL_RenderClear(renderer);

  double x_min = pb.scenario.domain_min;
  double x_max = pb.scenario.domain_max;
  double y_min = 0.0;
  double y_max = 1.0;
  bounce::core::curve::CompiledPolynomial curve_y{};
  if (pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    curve_y = bounce::core::curve::compile_polynomial(
        std::vector<double>(pb.scenario.coeffs.begin(),
                            pb.scenario.coeffs.begin() + pb.scenario.coeff_count));
    for (int i = 0; i <= 128; ++i) {
      const double x = x_min + (x_max - x_min) * static_cast<double>(i) / 128.0;
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

  auto to_px = [&](double x, double y) -> SDL_Point {
    SDL_Point p{};
    p.x = static_cast<int>((x - x_min) / (x_max - x_min) * static_cast<double>(kWindowW - 1));
    p.y = static_cast<int>((y_max - y) / (y_max - y_min) * static_cast<double>(kWindowH - 1));
    return p;
  };

  SDL_SetRenderDrawColor(renderer, 180, 180, 200, 255);
  if (pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    int prev_x = -1;
    int prev_y = -1;
    for (int i = 0; i < kWindowW; ++i) {
      const double x = x_min + (x_max - x_min) * static_cast<double>(i) / static_cast<double>(kWindowW - 1);
      const auto p = to_px(x, bounce::core::curve::eval(curve_y, x));
      if (prev_x >= 0) {
        SDL_RenderDrawLine(renderer, prev_x, prev_y, p.x, p.y);
      }
      prev_x = p.x;
      prev_y = p.y;
    }
  }

  SDL_SetRenderDrawColor(renderer, 240, 90, 60, 255);
  for (int b = 0; b < pb.scenario.ball_count; ++b) {
    const auto state = ball_state_at(pb, b, t);
    const auto p = to_px(state.pos.x, state.pos.y);
    SDL_Rect rect{p.x - 5, p.y - 5, 10, 10};
    SDL_RenderFillRect(renderer, &rect);
  }
}

} // namespace

int run_interactive(const char* scenario_path) {
  Playback pb{};
  std::string error;
  if (!load_and_simulate(scenario_path, pb, 200, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
    std::cerr << SDL_GetError() << '\n';
    return 1;
  }

  SDL_Window* window =
      SDL_CreateWindow("bounce-view", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowW, kWindowH,
                       SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_AudioSpec want{};
  want.freq = 44100;
  want.format = AUDIO_F32SYS;
  want.channels = 1;
  want.samples = 512;
  want.callback = nullptr;

  std::vector<BlipVoice> voices(32);
  std::size_t next_voice = 0;
  std::size_t next_event = 0;
  Uint32 start_ticks = SDL_GetTicks();
  double sim_duration = std::max(pb.end_time, 0.5);
  const double pace = 1.0;

  bool running = true;
  while (running) {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }
        if (event.key.keysym.sym == SDLK_r) {
          reset_playback(pb);
          next_event = 0;
          start_ticks = SDL_GetTicks();
          for (auto& v : voices) {
            v.active = false;
          }
        }
      }
    }

    const double elapsed_s = static_cast<double>(SDL_GetTicks() - start_ticks) / 1000.0 * pace;
    const double t = std::fmod(elapsed_s, sim_duration + 0.25);

    while (next_event < pb.events.size() && pb.events[next_event].t <= t) {
      const auto& ev = pb.events[next_event];
      const auto blip = blip_params(pb.scenario, ev);
      if (blip.amp > 0.0) {
        auto& voice = voices[next_voice % voices.size()];
        voice.start_ms = static_cast<double>(SDL_GetTicks());
        voice.freq_hz = blip.f_hz;
        voice.amp = blip.amp;
        voice.active = true;
        ++next_voice;
      }
      ++next_event;
    }
    if (t < 0.05) {
      next_event = 0;
    }

    draw_scene(renderer, pb, t);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

} // namespace bounce_view
