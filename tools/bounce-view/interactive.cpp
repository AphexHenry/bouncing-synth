// SPDX-License-Identifier: GPL-3.0-only
#include "interactive.hpp"

#include "audio_voice.hpp"
#include "av_mapping.hpp"
#include "build_stamp.hpp"
#include "law1_guard.hpp"
#include "perf.hpp"
#include "playback.hpp"
#include "restitution_config.hpp"
#include "scene.hpp"
#include "selftest.hpp"

#include <SDL.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace bounce_view {

namespace {

constexpr int kWindowW = 800;
constexpr int kWindowH = 600;

bool g_render_optimized = false;

using Clock = std::chrono::steady_clock;
namespace fs = std::filesystem;

double elapsed_ms(Clock::time_point start) {
  return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

struct VoiceState {
  BlipParams params{};
  double start_ms = 0.0;
  bool active = false;
};


std::string restitution_short(const RunConfig& cfg) {
  switch (cfg.mode) {
  case RestitutionMode::ScenarioFaithful:
    return "scenario";
  case RestitutionMode::InteractiveDefault:
    return "1";
  case RestitutionMode::OverrideUniform: {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%g", cfg.override_r);
    return buf;
  }
  }
  return "?";
}

int count_events_at_or_before(const Playback& pb, double t) {
  int n = 0;
  for (const auto& ev : pb.events) {
    if (ev.t <= t + 1e-15) {
      ++n;
    } else {
      break;
    }
  }
  return n;
}

bool step_to_next_event(const Playback& pb, double& sim_t, int& event_count) {
  for (const auto& ev : pb.events) {
    if (ev.t > sim_t + 1e-15) {
      sim_t = ev.t;
      event_count = count_events_at_or_before(pb, sim_t);
      return true;
    }
  }
  return false;
}


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
  if (build_scene_cache(view, t, kWindowW, kWindowH, cache, false, &camera)) {
    print_camera_line(camera);
  }
  draw_scene(renderer, cache, view, t, kWindowW, kWindowH, perf);
}

void draw_optimized(SDL_Renderer* renderer, SceneCache& cache, Playback& render_pb, double t,
                    CameraState& camera, PerfStats* perf) {
  PlaybackView view{};
  view.pb = render_pb;
  reset_playback_view(view);
  if (build_scene_cache(view, t, kWindowW, kWindowH, cache, true, &camera)) {
    print_camera_line(camera);
  }
  draw_scene(renderer, cache, view, t, kWindowW, kWindowH, perf);
}

void collect_json_files(const fs::path& root, std::vector<std::string>& out) {
  std::error_code ec;
  if (!fs::exists(root, ec)) {
    return;
  }
  for (fs::recursive_directory_iterator it(root, ec), end; it != end && !ec; it.increment(ec)) {
    if (!it->is_regular_file(ec)) {
      continue;
    }
    if (it->path().extension() == ".json") {
      out.push_back(it->path().generic_string());
    }
  }
}

std::vector<std::string> enumerate_picker_paths() {
  std::vector<std::string> paths;
  collect_json_files(fs::path("tools/bounce-view/scenarios"), paths);
  collect_json_files(fs::path("data/scenarios/calibration"), paths);
  std::sort(paths.begin(), paths.end());
  return paths;
}

void print_picker_list(const std::vector<std::string>& paths, int selected) {
  std::cout << "picker: " << paths.size() << " scenarios (Up/Down, Enter load, Esc cancel)\n";
  for (std::size_t i = 0; i < paths.size(); ++i) {
    const char* mark = static_cast<int>(i) == selected ? ">" : " ";
    std::cout << "picker: " << mark << " [" << i << "] " << paths[i] << '\n';
  }
}

enum class LoadAttempt : int { Ok = 0, Law1Refused = 1, Failed = 2 };

LoadAttempt attempt_runtime_load(const std::string& path, Playback& pb, const RunConfig& cfg,
                                 std::string& active_path, std::size_t& next_event,
                                 Uint32& start_ticks, std::vector<VoiceState>& voices,
                                 Playback& render_pb, CameraState& camera, bool sdl_ready) {
  if (is_heldout_path(path)) {
    std::cout << "LAW1: held-out scenario refused\n";
    return LoadAttempt::Law1Refused;
  }

  Playback next{};
  std::string error;
  const int max_events =
      effective_lossless(cfg) ? static_cast<int>(bounce::core::engine::kMaxSimEvents) : 200;
  if (!load_and_simulate(path.c_str(), next, max_events, cfg, error)) {
    std::cout << "load error: " << error << '\n';
    return LoadAttempt::Failed;
  }

  pb = std::move(next);
  active_path = path;
  next_event = 0;
  start_ticks = sdl_ready ? SDL_GetTicks() : 0;
  for (auto& v : voices) {
    v.active = false;
  }
  render_pb = pb;
  reset_playback(render_pb);
  camera = CameraState{};

  std::cout << "loaded: " << path << '\n';
  print_restitution_line(cfg);
  print_build_stamp();
  return LoadAttempt::Ok;
}

void draw_picker_overlay(SDL_Renderer* renderer, int selected, int count) {
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 160);
  SDL_Rect dim{0, 0, kWindowW, kWindowH};
  SDL_RenderFillRect(renderer, &dim);

  const int row_h = 18;
  const int visible = std::min(count, 24);
  for (int i = 0; i < visible; ++i) {
    if (i == selected) {
      SDL_SetRenderDrawColor(renderer, 80, 140, 220, 220);
    } else {
      SDL_SetRenderDrawColor(renderer, 40, 40, 50, 200);
    }
    SDL_Rect row{40, 40 + i * row_h, kWindowW - 80, row_h - 2};
    SDL_RenderFillRect(renderer, &row);
  }
}

int run_s13_proof_session(const RunConfig& cfg, Playback& pb, std::string& active_path) {
  std::vector<VoiceState> voices(32);
  std::size_t next_event = 0;
  Uint32 start_ticks = 0;
  CameraState camera{};
  Playback render_pb = pb;
  reset_playback(render_pb);

  auto picker_paths = enumerate_picker_paths();
  // Prefer a lightweight assessment scene for the picker-load transcript (calibration
  // streams under e=1 can run for a long time at kMaxSimEvents).
  int picker_selected = 0;
  const std::string preferred = "tools/bounce-view/scenarios/twowell-poly4.json";
  for (std::size_t i = 0; i < picker_paths.size(); ++i) {
    if (picker_paths[i] == preferred) {
      picker_selected = static_cast<int>(i);
      break;
    }
  }
  print_picker_list(picker_paths, picker_selected);
  if (!picker_paths.empty()) {
    const std::string chosen = picker_paths[static_cast<std::size_t>(picker_selected)];
    std::cout << "picker: loading " << chosen << '\n';
    (void)attempt_runtime_load(chosen, pb, cfg, active_path, next_event, start_ticks, voices,
                               render_pb, camera, false);
  }

  std::cout << "s13-proof: attempting held-out nonexistent path\n";
  (void)attempt_runtime_load("data/scenarios/heldout/NONEXISTENT.json", pb, cfg, active_path,
                             next_event, start_ticks, voices, render_pb, camera, false);
  std::cout << "s13-proof: scene still active path=" << active_path << '\n';

  const fs::path malformed = fs::temp_directory_path() / "bounce-view-s13-malformed.txt";
  {
    std::ofstream out(malformed);
    out << "this is not json\n";
  }
  std::cout << "s13-proof: attempting malformed file " << malformed.generic_string() << '\n';
  (void)attempt_runtime_load(malformed.generic_string(), pb, cfg, active_path, next_event,
                             start_ticks, voices, render_pb, camera, false);
  std::cout << "s13-proof: scene still active path=" << active_path << '\n';
  return 0;
}


int run_s15_proof_session(const char* mode, const RunConfig& cfg, Playback& pb) {
  CameraState camera{};
  PlaybackView view{};
  view.pb = pb;
  reset_playback_view(view);
  constexpr int kW = kWindowW;
  constexpr int kH = kWindowH;
  const std::string build = build_stamp_short_commit();

  if (std::strcmp(mode, "zoom") == 0) {
    // Bounded scripted drive: presentation-like time steps over a capped horizon.
    std::cout << "s15-proof: zoom drive on current scene (bounded)\n";
    const double t_end = pb.events.empty() ? 1.0 : std::min(pb.events.back().t, 30.0);
    constexpr double kDt = 1.0 / 30.0; // 30 Hz presentation-equivalent
    const int max_steps = 900;        // hard bound (30s * 30Hz)
    int printed = 0;
    int steps = 0;
    for (double t = 0.0; t <= t_end + 1e-15 && steps < max_steps; t += kDt, ++steps) {
      const Viewport target = compute_viewport_targets(view, t);
      if (update_camera(camera, target, kW, kH)) {
        print_camera_line(camera);
        ++printed;
      }
    }
    std::cout << "s15-proof: zoom drive done camera_lines=" << printed << " steps=" << steps
              << " t_end=" << t_end << '\n';
    return 0;
  }

  if (std::strcmp(mode, "pause") == 0) {
    std::cout << "s15-proof: pause/step session\n";
    double sim_t = 0.0;
    int event_count = 0;
    bool paused = true;
    HudState hud{};
    hud.sim_t = sim_t;
    hud.event_count = event_count;
    hud.restitution = restitution_short(cfg);
    hud.camera_locked = false;
    hud.camera_level = camera.level;
    hud.build_short = build;
    std::cout << "pause: engaged\n";
    print_hud_line(hud);
    for (int step = 0; step < 3; ++step) {
      if (!step_to_next_event(pb, sim_t, event_count)) {
        std::cerr << "s15-proof: no next event for step " << step << '\n';
        return 1;
      }
      std::cout << "step: .\n";
      hud.sim_t = sim_t;
      hud.event_count = event_count;
      hud.camera_level = camera.level;
      print_hud_line(hud);
    }
    (void)paused;
    return 0;
  }

  if (std::strcmp(mode, "lock") == 0) {
    std::cout << "s15-proof: camera lock session\n";
    // Warm camera at first event, then lock.
    if (!pb.events.empty()) {
      const Viewport target = compute_viewport_targets(view, pb.events.front().t);
      (void)update_camera(camera, target, kW, kH);
      print_camera_line(camera);
    }
    camera.locked = true;
    std::cout << "camera: lock engaged\n";
    print_camera_line(camera);

    auto dump_at = [&](double t, int index) {
      SceneCache cache{};
      build_scene_cache(view, t, kW, kH, cache, true, &camera);
      const auto checks = compute_frame_checks(cache, view, t, kW, kH);
      for (const auto& row : checks) {
        if (row.ball_id >= 0) {
          std::cout << "frame_check ball_id=" << row.ball_id
                    << " camera_level=" << row.camera_level
                    << " camera_scale=" << std::setprecision(17) << row.camera_scale
                    << " scale_x=" << row.scale_x << " scale_y=" << row.scale_y << '\n';
          break;
        }
      }
      std::cout << "frame_dump index=" << index << " t_frame=" << std::setprecision(17) << t
                << '\n';
      print_camera_line(camera);
    };

    double t0 = pb.events.size() > 5 ? pb.events[5].t : (pb.events.empty() ? 0.1 : pb.events.back().t);
    double t1 = pb.events.size() > 20 ? pb.events[20].t : t0 + 1.0;
    dump_at(t0, 0);
    dump_at(t1, 1);
    return 0;
  }

  std::cerr << "s15-proof: unknown mode '" << mode << "' (want zoom|pause|lock)\n";
  return 1;
}

int run_loop(const char* scenario_path, int perf_seconds, const RunConfig& cfg) {
  print_build_stamp();
  print_restitution_line(cfg);

  Playback pb{};
  std::string error;
  std::string active_path = scenario_path;
  const int max_events =
      effective_lossless(cfg) ? static_cast<int>(bounce::core::engine::kMaxSimEvents) : 200;
  if (!load_and_simulate(scenario_path, pb, max_events, cfg, error)) {
    std::cerr << error << '\n';
    return 1;
  }

  if (std::getenv("BOUNCE_VIEW_S13_PROOF") != nullptr) {
    // Same picker / Law-1 / malformed handlers as key `l` and SDL_DROPFILE; no present loop.
    return run_s13_proof_session(cfg, pb, active_path);
  }

  if (const char* s15 = std::getenv("BOUNCE_VIEW_S15_PROOF"); s15 != nullptr) {
    // Same pause/step/lock/camera update paths as interactive keys; no present loop.
    return run_s15_proof_session(s15, cfg, pb);
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
    std::cerr << SDL_GetError() << '\n';
    return 1;
  }
  SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

  const Uint32 renderer_flags =
      SDL_RENDERER_ACCELERATED | (g_render_optimized ? SDL_RENDERER_PRESENTVSYNC : 0);
  const std::string title = build_stamp_window_title();
  SDL_Window* window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        kWindowW, kWindowH, SDL_WINDOW_SHOWN);
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

  bool picker_open = false;
  std::vector<std::string> picker_paths;
  int picker_selected = 0;
  bool paused = false;
  double sim_t = 0.0;
  int hud_event_count = 0;

  while (running) {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
      if (event.type == SDL_DROPFILE) {
        char* dropped = event.drop.file;
        if (dropped != nullptr) {
          const std::string dropped_path(dropped);
          SDL_free(dropped);
          if (perf_seconds == 0) {
            picker_open = false;
            (void)attempt_runtime_load(dropped_path, pb, cfg, active_path, next_event, start_ticks,
                                       voices, render_pb, camera, true);
            SDL_SetWindowTitle(window, build_stamp_window_title().c_str());
          }
        }
      }
      if (event.type == SDL_KEYDOWN) {
        const SDL_Keycode key = event.key.keysym.sym;
        if (picker_open) {
          if (key == SDLK_ESCAPE) {
            picker_open = false;
            std::cout << "picker: cancelled\n";
          } else if (key == SDLK_UP) {
            if (!picker_paths.empty()) {
              picker_selected =
                  (picker_selected + static_cast<int>(picker_paths.size()) - 1) %
                  static_cast<int>(picker_paths.size());
              print_picker_list(picker_paths, picker_selected);
            }
          } else if (key == SDLK_DOWN) {
            if (!picker_paths.empty()) {
              picker_selected = (picker_selected + 1) % static_cast<int>(picker_paths.size());
              print_picker_list(picker_paths, picker_selected);
            }
          } else if (key == SDLK_RETURN || key == SDLK_KP_ENTER) {
            if (!picker_paths.empty()) {
              const std::string chosen = picker_paths[static_cast<std::size_t>(picker_selected)];
              std::cout << "picker: loading " << chosen << '\n';
              picker_open = false;
              (void)attempt_runtime_load(chosen, pb, cfg, active_path, next_event, start_ticks,
                                         voices, render_pb, camera, true);
              SDL_SetWindowTitle(window, build_stamp_window_title().c_str());
            }
          }
          continue;
        }
        if (key == SDLK_q || key == SDLK_ESCAPE) {
          running = false;
        }
        if (key == SDLK_r) {
          reset_playback(render_pb);
          next_event = 0;
          start_ticks = SDL_GetTicks();
          sim_t = 0.0;
          paused = false;
          hud_event_count = 0;
          camera = CameraState{};
          print_camera_line(camera);
          for (auto& v : voices) {
            v.active = false;
          }
        }
        if (perf_seconds == 0 && key == SDLK_l) {
          picker_paths = enumerate_picker_paths();
          picker_selected = 0;
          picker_open = true;
          print_picker_list(picker_paths, picker_selected);
        }
        if (perf_seconds == 0 && key == SDLK_c) {
          camera.locked = !camera.locked;
          std::cout << "camera: " << (camera.locked ? "lock engaged" : "lock released") << '\n';
          print_camera_line(camera);
        }
        if (perf_seconds == 0 && key == SDLK_SPACE) {
          if (paused) {
            start_ticks = SDL_GetTicks() - static_cast<Uint32>(std::max(0.0, sim_t) * 1000.0);
            paused = false;
            std::cout << "pause: released\n";
          } else {
            paused = true;
            std::cout << "pause: engaged\n";
          }
        }
        if (perf_seconds == 0 && paused && key == SDLK_PERIOD) {
          int ec = hud_event_count;
          if (step_to_next_event(pb, sim_t, ec)) {
            hud_event_count = ec;
            next_event = static_cast<std::size_t>(hud_event_count);
            std::cout << "step: .\n";
            // Fire voice for the event we landed on.
            if (hud_event_count > 0) {
              const auto& ev = pb.events[static_cast<std::size_t>(hud_event_count - 1)];
              const auto blip = blip_params(pb.scenario, ev);
              if (blip.amp > 0.0) {
                auto& voice = voices[next_voice % voices.size()];
                voice.params = blip;
                voice.start_ms = static_cast<double>(SDL_GetTicks());
                voice.active = true;
                ++next_voice;
              }
            }
          }
        }
      }
    }

    if (perf_seconds > 0 && SDL_GetTicks() >= end_ticks) {
      running = false;
    }

    if (!paused) {
      sim_t = std::max(0.0, static_cast<double>(SDL_GetTicks() - start_ticks) / 1000.0);
    }
    const double t = sim_t;

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
      hud_event_count = static_cast<int>(next_event);
    }

    if (perf_seconds == 0 && !paused && effective_lossless(cfg) && next_event + 8 >= pb.events.size()) {
      roll_event_stream(active_path.c_str(), pb, cfg, error);
    }

    advance_playback_to(render_pb, t);

    if (g_render_optimized) {
      draw_optimized(renderer, cache, render_pb, t, camera, perf_seconds > 0 ? &perf : nullptr);
    } else {
      draw_unoptimized(renderer, render_pb, t, camera, perf_seconds > 0 ? &perf : nullptr);
    }

    HudState hud{};
    hud.sim_t = t;
    hud.event_count = hud_event_count;
    hud.restitution = restitution_short(cfg);
    hud.camera_locked = camera.locked;
    hud.camera_level = camera.level;
    hud.build_short = build_stamp_short_commit();
    draw_hud_overlay(renderer, hud, kWindowW, kWindowH);

    if (picker_open) {
      draw_picker_overlay(renderer, picker_selected, static_cast<int>(picker_paths.size()));
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
