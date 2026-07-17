// SPDX-License-Identifier: GPL-3.0-only
//
// Canonical bounce-events-v1 JSONL serialization (PROJECT §6 CollisionEvent).
// Fixed per-event key order (hexfloat authoritative for all floating-point fields):
//   t_hex, t, ball_id, s_hex, s, impact_speed_hex, impact_speed,
//   normal_x_hex, normal_x, normal_y_hex, normal_y, seq, schema_version
#pragma once

#include "bounce/engine/collision_sim.hpp"
#include "bounce/events/collision_event.hpp"

#include <array>
#include <fstream>
#include <string>

namespace bounce::core::io {

constexpr int kMaxOfflineEvents = engine::kMaxOfflineEvents;

struct EventFileData {
  std::array<events::CollisionEvent, engine::kMaxSimEvents> events{};
  int count = 0;
  std::string scenario_sha256;
};

struct EventStreamWriter {
  std::ofstream body_stream{};
  std::string body_temp_path;
  std::string final_path;
  std::string scenario_sha256;
  int count = 0;
};

bool events_equal(const events::CollisionEvent& a, const events::CollisionEvent& b);

bool events_equal(const EventFileData& file_data, const engine::MultiBallSimResult& result);

bool write_event_file(const char* path, const char* scenario_path,
                      const engine::MultiBallSimResult& result, std::string& error);

bool begin_event_stream(const char* path, const char* scenario_path, EventStreamWriter& writer,
                        std::string& error);

bool emit_event_stream(EventStreamWriter& writer, const events::CollisionEvent& event);

bool finish_event_stream(EventStreamWriter& writer, std::string& error);

bool read_event_file(const char* path, EventFileData& out, std::string& error);

} // namespace bounce::core::io
