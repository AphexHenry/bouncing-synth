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

void draw_unoptimized(SDL_Renderer* renderer, Playback& render_pb, double t, CameraState& camera,
                    PerfStats* perf) {
  PlaybackView view{};
  view.pb = render_pb;
  reset_playback_view(view);
  SceneCache cache{};
  build_scene_cache(view, t, kWindowW, kWindowH, cache, false, &camera);
  draw_scene(renderer, cache, view, t, kWindowW, kWindowH, perf);
}

void draw_optimized(SDL_Renderer* renderer, SceneCache& cache, Playback& render_pb, double t,
                    CameraState& camera, PerfStats* perf) {
  PlaybackView view{};
  view.pb = render_pb;
  reset_playback_view(view);
  build_scene_cache(view, t, kWindowW, kWindowH, cache, true, &camera);
  draw_scene(renderer, cache, view, t, kWindowW, kWindowH, perf);
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
  CameraState camera{};
  Playback render_pb = pb;
  reset_playback(render_pb);

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

    advance_playback_to(render_pb, t);

    if (g_render_optimized) {
      draw_optimized(renderer, cache, render_pb, t, camera, perf_seconds > 0 ? &perf : nullptr);
    } else {
      draw_unoptimized(renderer, render_pb, t, camera, perf_seconds > 0 ? &perf : nullptr);
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
