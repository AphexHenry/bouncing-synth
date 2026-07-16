// SPDX-License-Identifier: GPL-3.0-only
#include "interactive.hpp"

#include "audio_voice.hpp"
#include "av_mapping.hpp"
#include "perf.hpp"
#include "playback.hpp"
#include "restitution_config.hpp"
#include "scene.hpp"
#include "selftest.hpp"

#include <SDL.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

namespace bounce_view {

namespace {

constexpr int kWindowW = 800;
constexpr int kWindowH = 600;

SDL_Point to_screen(double x, double y, const Viewport& vp, int window_w, int window_h) {
  SDL_Point p{};
  p.x = static_cast<int>((x - vp.x_min) / (vp.x_max - vp.x_min) * static_cast<double>(window_w - 1));
  p.y = static_cast<int>((vp.y_max - y) / (vp.y_max - vp.y_min) * static_cast<double>(window_h - 1));
  return p;
}

bool g_render_optimized = false;

using Clock = std::chrono::steady_clock;

double elapsed_ms(Clock::time_point start) {
  return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

struct VoiceState {
  BlipParams params{};
  double start_ms = 0.0;
  bool active = false;
};

struct AudioContext {
  std::vector<VoiceState>* voices = nullptr;
};

void SDLCALL audio_callback(void* userdata, Uint8* stream, int len) {
  auto* ctx = static_cast<AudioContext*>(userdata);
  auto* out = reinterpret_cast<float*>(stream);
  const int samples = len / static_cast<int>(sizeof(float));
  const double now_ms = static_cast<double>(SDL_GetTicks());
  for (int i = 0; i < samples; ++i) {
    double mix = 0.0;
    for (auto& voice : *ctx->voices) {
      if (!voice.active) {
        continue;
      }
      const double elapsed = now_ms - voice.start_ms + static_cast<double>(i) * 1000.0 / 44100.0;
      const double sample = sample_av2_voice(voice.params, elapsed);
      mix += sample;
      if (elapsed > voice.params.tau_ms * 6.0) {
        voice.active = false;
      }
    }
    out[i] = static_cast<float>(std::clamp(0.5 * mix, -1.0, 1.0));
  }
}

void draw_unoptimized(SDL_Renderer* renderer, const Playback& pb, double t, PerfStats* perf) {
  SDL_SetRenderDrawColor(renderer, 18, 20, 28, 255);
  SDL_RenderClear(renderer);

  const auto engine_start = Clock::now();
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
  if (perf != nullptr) {
    record_subsystem(perf->engine_query, elapsed_ms(engine_start));
  }

  auto to_px = [&](double x, double y) -> SDL_Point {
    SDL_Point p{};
    p.x = static_cast<int>((x - x_min) / (x_max - x_min) * static_cast<double>(kWindowW - 1));
    p.y = static_cast<int>((y_max - y) / (y_max - y_min) * static_cast<double>(kWindowH - 1));
    return p;
  };

  const auto curve_start = Clock::now();
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
  if (perf != nullptr) {
    record_subsystem(perf->curve_draw, elapsed_ms(curve_start));
  }

  const auto ball_start = Clock::now();
  for (int b = 0; b < pb.scenario.ball_count; ++b) {
    const auto state = ball_state_at(pb, b, t);
    const auto p = to_px(state.pos.x, state.pos.y);
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

void draw_optimized(SDL_Renderer* renderer, SceneCache& cache, Playback& render_pb, double t,
                    PerfStats* perf) {
  const auto engine_start = Clock::now();
  advance_playback_to(render_pb, t);
  std::vector<BallRenderState> balls(static_cast<std::size_t>(render_pb.scenario.ball_count));
  for (int b = 0; b < render_pb.scenario.ball_count; ++b) {
    const std::size_t idx = static_cast<std::size_t>(b);
    if (render_pb.settled[idx]) {
      balls[idx].pos = render_pb.settle_pos[idx];
      balls[idx].settled = true;
    } else {
      const double dt = t - render_pb.arc_start_t[idx];
      balls[idx].pos =
          bounce::core::engine::position_at_time(render_pb.current[idx], std::max(0.0, dt));
    }
  }
  if (perf != nullptr) {
    record_subsystem(perf->engine_query, elapsed_ms(engine_start));
  }

  SDL_SetRenderDrawColor(renderer, 18, 20, 28, 255);
  SDL_RenderClear(renderer);

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
  for (int b = 0; b < render_pb.scenario.ball_count; ++b) {
    const auto& state = balls[static_cast<std::size_t>(b)];
    const auto p = to_screen(state.pos.x, state.pos.y, cache.viewport, kWindowW, kWindowH);
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

int run_loop(const char* scenario_path, int perf_seconds, const RunConfig& cfg) {
  print_restitution_line(cfg);

  Playback pb{};
  std::string error;
  const int max_events = effective_lossless(cfg)
                             ? static_cast<int>(bounce::core::engine::kMaxSimEvents)
                             : 200;
  if (!load_and_simulate(scenario_path, pb, max_events, cfg, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
    std::cerr << SDL_GetError() << '\n';
    return 1;
  }

  const Uint32 renderer_flags =
      SDL_RENDERER_ACCELERATED | (g_render_optimized ? SDL_RENDERER_PRESENTVSYNC : 0);
  SDL_Window* window =
      SDL_CreateWindow("bounce-view", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowW, kWindowH,
                       SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderer_flags);

  SDL_DisplayMode mode{};
  int refresh_hz = 60;
  if (SDL_GetCurrentDisplayMode(0, &mode) == 0 && mode.refresh_rate > 0) {
    refresh_hz = mode.refresh_rate;
  }

  std::vector<VoiceState> voices(32);
  std::size_t next_voice = 0;
  std::size_t next_event = 0;
  AudioContext audio_ctx{&voices};
  SDL_AudioSpec want{};
  want.freq = 44100;
  want.format = AUDIO_F32SYS;
  want.channels = 1;
  want.samples = 512;
  want.callback = audio_callback;
  want.userdata = &audio_ctx;
  SDL_AudioDeviceID audio_dev = SDL_OpenAudioDevice(nullptr, 0, &want, nullptr, 0);
  if (audio_dev != 0) {
    SDL_PauseAudioDevice(audio_dev, 0);
  }

  PlaybackView bootstrap{};
  bootstrap.pb = pb;
  reset_playback_view(bootstrap);
  SceneCache cache{};
  Playback render_pb = pb;
  reset_playback(render_pb);
  if (g_render_optimized) {
    build_scene_cache(bootstrap, kWindowW, kWindowH, cache, true);
  }

  PerfStats perf{};
  perf.display_w = kWindowW;
  perf.display_h = kWindowH;
  perf.refresh_hz = refresh_hz;

  Uint32 start_ticks = SDL_GetTicks();
  const Uint32 end_ticks = perf_seconds > 0 ? start_ticks + static_cast<Uint32>(perf_seconds * 1000) : 0;
  bool running = true;
  bool have_present_anchor = false;
  Clock::time_point last_present_time{};
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
          reset_playback(render_pb);
          next_event = 0;
          start_ticks = SDL_GetTicks();
          for (auto& v : voices) {
            v.active = false;
          }
        }
      }
    }

    if (perf_seconds > 0 && SDL_GetTicks() >= end_ticks) {
      running = false;
    }

    const double elapsed_s = static_cast<double>(SDL_GetTicks() - start_ticks) / 1000.0;
    const double t = std::max(0.0, elapsed_s);

    while (next_event < pb.events.size() && pb.events[next_event].t <= t) {
      const auto& ev = pb.events[next_event];
      const auto blip = blip_params(pb.scenario, ev);
      if (blip.amp > 0.0) {
        auto& voice = voices[next_voice % voices.size()];
        voice.params = blip;
        voice.start_ms = static_cast<double>(SDL_GetTicks());
        voice.active = true;
        ++next_voice;
      }
      ++next_event;
    }

    if (perf_seconds == 0 && effective_lossless(cfg) && next_event + 8 >= pb.events.size()) {
      roll_event_stream(scenario_path, pb, cfg, error);
    }

    if (g_render_optimized) {
      draw_optimized(renderer, cache, render_pb, t, perf_seconds > 0 ? &perf : nullptr);
    } else {
      draw_unoptimized(renderer, pb, t, perf_seconds > 0 ? &perf : nullptr);
    }

    const auto present_start = Clock::now();
    SDL_RenderPresent(renderer);
    if (perf_seconds > 0) {
      record_subsystem(perf.present, elapsed_ms(present_start));
      const auto audio_start = Clock::now();
      record_subsystem(perf.audio, elapsed_ms(audio_start));
      if (have_present_anchor) {
        perf.frame_times_ms.push_back(
            std::chrono::duration<double, std::milli>(present_start - last_present_time).count());
      } else {
        have_present_anchor = true;
      }
      last_present_time = present_start;
      ++perf.frame_count;
    }

    if (!g_render_optimized) {
      SDL_Delay(16);
    }
  }

  if (perf_seconds > 0) {
    perf.measured_duration_s = static_cast<double>(SDL_GetTicks() - start_ticks) / 1000.0;
    print_perf_report(perf);
  }

  if (audio_dev != 0) {
    SDL_CloseAudioDevice(audio_dev);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

} // namespace

void set_render_optimized(bool enabled) { g_render_optimized = enabled; }

int run_interactive(const char* scenario_path, const RunConfig& cfg) {
  return run_loop(scenario_path, 0, cfg);
}

int run_perf_seconds(const char* scenario_path, int seconds, const RunConfig& cfg) {
  return run_loop(scenario_path, seconds, cfg);
}

} // namespace bounce_view
