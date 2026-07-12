// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/io/event_file.hpp"

#include "bounce/io/sha256.hpp"

#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <string_view>

namespace bounce::core::io {
namespace {

constexpr const char* kSchema = "bounce-events-v1";

std::string format_decimal(double value) { return std::format("{:.17g}", value); }

std::string format_hexfloat(double value) {
  char buf[64];
  std::snprintf(buf, sizeof(buf), "%a", value);
  return buf;
}

bool has_hex_prefix(std::string_view text) {
  if (text.size() >= 2 && text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
    return true;
  }
  if (text.size() >= 3 && (text[0] == '-' || text[0] == '+') && text[1] == '0' &&
      (text[2] == 'x' || text[2] == 'X')) {
    return true;
  }
  return false;
}

bool parse_hex_double(std::string_view text, double& out) {
  if (text.empty()) {
    return false;
  }
  std::string copy(text);
  if (!has_hex_prefix(copy)) {
    if (!copy.empty() && (copy[0] == '-' || copy[0] == '+')) {
      copy.insert(1, "0x");
    } else {
      copy.insert(0, "0x");
    }
  }
  char* end = nullptr;
  const double value = std::strtod(copy.c_str(), &end);
  if (end == copy.c_str() || end != copy.c_str() + copy.size()) {
    return false;
  }
  out = value;
  return true;
}

bool extract_string_field(std::string_view line, std::string_view key, std::string& out) {
  const std::string needle = std::format("\"{}\":\"", key);
  const auto pos = line.find(needle);
  if (pos == std::string_view::npos) {
    return false;
  }
  const auto start = pos + needle.size();
  const auto end = line.find('"', start);
  if (end == std::string_view::npos) {
    return false;
  }
  out.assign(line.substr(start, end - start));
  return true;
}

bool extract_int_field(std::string_view line, std::string_view key, int& out) {
  const std::string needle = std::format("\"{}\":", key);
  const auto pos = line.find(needle);
  if (pos == std::string_view::npos) {
    return false;
  }
  const auto start = pos + needle.size();
  int value = 0;
  const auto parsed = std::from_chars(line.data() + start, line.data() + line.size(), value);
  if (parsed.ec != std::errc{}) {
    return false;
  }
  out = value;
  return true;
}

std::string event_line(const events::CollisionEvent& event) {
  return std::format(
      "{{\"t_hex\":\"{}\",\"t\":{},\"ball_id\":{},\"s_hex\":\"{}\",\"s\":{},"
      "\"impact_speed_hex\":\"{}\",\"impact_speed\":{},\"normal_x_hex\":\"{}\",\"normal_x\":{},"
      "\"normal_y_hex\":\"{}\",\"normal_y\":{},\"seq\":{},\"schema_version\":{}}}",
      format_hexfloat(event.t), format_decimal(event.t), event.ball_id, format_hexfloat(event.s),
      format_decimal(event.s), format_hexfloat(event.impact_speed),
      format_decimal(event.impact_speed), format_hexfloat(event.normal_x),
      format_decimal(event.normal_x), format_hexfloat(event.normal_y),
      format_decimal(event.normal_y), event.seq, event.schema_version);
}

bool parse_event_line(std::string_view line, events::CollisionEvent& event) {
  std::string hex;
  if (!extract_string_field(line, "t_hex", hex) || !parse_hex_double(hex, event.t)) {
    return false;
  }
  if (!extract_string_field(line, "s_hex", hex) || !parse_hex_double(hex, event.s)) {
    return false;
  }
  if (!extract_string_field(line, "impact_speed_hex", hex) ||
      !parse_hex_double(hex, event.impact_speed)) {
    return false;
  }
  if (!extract_string_field(line, "normal_x_hex", hex) || !parse_hex_double(hex, event.normal_x)) {
    return false;
  }
  if (!extract_string_field(line, "normal_y_hex", hex) || !parse_hex_double(hex, event.normal_y)) {
    return false;
  }
  if (!extract_int_field(line, "ball_id", event.ball_id) || !extract_int_field(line, "seq", event.seq) ||
      !extract_int_field(line, "schema_version", event.schema_version)) {
    return false;
  }
  return true;
}

} // namespace

bool events_equal(const events::CollisionEvent& a, const events::CollisionEvent& b) {
  return a.t == b.t && a.ball_id == b.ball_id && a.s == b.s && a.impact_speed == b.impact_speed &&
         a.normal_x == b.normal_x && a.normal_y == b.normal_y && a.seq == b.seq &&
         a.schema_version == b.schema_version;
}

bool events_equal(const EventFileData& file_data, const engine::MultiBallSimResult& result) {
  if (file_data.count != result.count) {
    return false;
  }
  for (int i = 0; i < file_data.count; ++i) {
    if (!events_equal(file_data.events[static_cast<std::size_t>(i)],
                      result.events[static_cast<std::size_t>(i)])) {
      return false;
    }
  }
  return true;
}

bool write_event_file(const char* path, const char* scenario_path,
                      const engine::MultiBallSimResult& result, std::string& error) {
  std::array<unsigned char, kSha256DigestBytes> digest{};
  if (!sha256_file(scenario_path, digest)) {
    error = "cannot hash scenario file";
    return false;
  }
  const std::string scenario_sha = sha256_hex(digest);
  const std::filesystem::path out_path(path);
  const std::filesystem::path temp_path = out_path.string() + ".tmp";

  std::ofstream out(temp_path, std::ios::binary);
  if (!out) {
    error = "cannot open output file";
    return false;
  }

  out << std::format(
      "{{\"schema\":\"{}\", \"scenario_sha256\":\"{}\", \"engine_events\":{}}}\n", kSchema,
      scenario_sha, result.count);
  for (int i = 0; i < result.count; ++i) {
    out << event_line(result.events[static_cast<std::size_t>(i)]) << '\n';
  }
  out.close();
  if (!out) {
    error = "write failed";
    std::error_code ec;
    std::filesystem::remove(temp_path, ec);
    return false;
  }

  std::error_code ec;
  std::filesystem::rename(temp_path, out_path, ec);
  if (ec) {
    error = "rename failed";
    std::filesystem::remove(temp_path, ec);
    return false;
  }
  return true;
}

bool read_event_file(const char* path, EventFileData& out, std::string& error) {
  std::ifstream in(path, std::ios::binary);
  if (!in) {
    error = "cannot open event file";
    return false;
  }

  std::string line;
  if (!std::getline(in, line) || line.empty()) {
    error = "missing header line";
    return false;
  }

  std::string schema;
  if (!extract_string_field(line, "schema", schema) || schema != kSchema) {
    error = "invalid schema";
    return false;
  }
  if (!extract_string_field(line, "scenario_sha256", out.scenario_sha256)) {
    error = "missing scenario_sha256";
    return false;
  }
  int declared_count = 0;
  if (!extract_int_field(line, "engine_events", declared_count) || declared_count < 0) {
    error = "invalid engine_events";
    return false;
  }

  out.count = 0;
  while (std::getline(in, line)) {
    if (line.empty()) {
      continue;
    }
    if (out.count >= static_cast<int>(engine::kMaxSimEvents)) {
      error = "too many events";
      return false;
    }
    auto& event = out.events[static_cast<std::size_t>(out.count)];
    if (!parse_event_line(line, event)) {
      error = "invalid event line";
      return false;
    }
    ++out.count;
  }

  if (out.count != declared_count) {
    error = "engine_events mismatch";
    return false;
  }
  return true;
}

} // namespace bounce::core::io
