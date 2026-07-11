// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/scenario/calibration_loader.hpp"

#include "bounce/curve/polynomial.hpp"
#include "bounce/scenario/rational.hpp"

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace bounce::core::scenario {

namespace {

const char* find_key(const std::string& json, const char* key) {
  const std::string needle = std::string("\"") + key + "\"";
  std::size_t pos = 0;
  while ((pos = json.find(needle, pos)) != std::string::npos) {
    const std::size_t after = pos + needle.size();
    if (after < json.size() && json[after] == ':') {
      return json.c_str() + after;
    }
    pos += 1;
  }
  return nullptr;
}

const char* skip_ws(const char* p) {
  while (*p != '\0' && std::isspace(static_cast<unsigned char>(*p))) {
    ++p;
  }
  return p;
}

bool parse_quoted_string(const char*& p, std::string& out) {
  p = skip_ws(p);
  if (*p != '"') {
    return false;
  }
  ++p;
  out.clear();
  while (*p != '\0' && *p != '"') {
    out.push_back(*p);
    ++p;
  }
  if (*p != '"') {
    return false;
  }
  ++p;
  return true;
}

bool parse_rational_field(const char*& p, double& out) {
  std::string text;
  if (!parse_quoted_string(p, text)) {
    return false;
  }
  return parse_rational(text, out);
}

bool parse_int_field(const char*& p, int& out) {
  p = skip_ws(p);
  if (!std::isdigit(static_cast<unsigned char>(*p)) && *p != '-') {
    return false;
  }
  char* end = nullptr;
  const long value = std::strtol(p, &end, 10);
  if (end == p) {
    return false;
  }
  p = end;
  out = static_cast<int>(value);
  return true;
}

bool parse_coeffs(const std::string& json, CalibrationScenario& out) {
  const char* p = find_key(json, "coeffs");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, '[');
  if (p == nullptr) {
    return false;
  }
  ++p;
  out.coeff_count = 0;
  while (true) {
    p = skip_ws(p);
    if (*p == ']') {
      break;
    }
    if (out.coeff_count >= kMaxScenarioCoeffs) {
      return false;
    }
    double coeff = 0.0;
    if (!parse_rational_field(p, coeff)) {
      return false;
    }
    out.coeffs[static_cast<std::size_t>(out.coeff_count++)] = coeff;
    p = skip_ws(p);
    if (*p == ',') {
      ++p;
      continue;
    }
    if (*p == ']') {
      break;
    }
    return false;
  }
  return out.coeff_count > 0;
}

bool parse_domain(const std::string& json, CalibrationScenario& out) {
  const char* p = find_key(json, "domain");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, '[');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, out.domain_min)) {
    return false;
  }
  p = skip_ws(p);
  if (*p != ',') {
    return false;
  }
  ++p;
  return parse_rational_field(p, out.domain_max);
}

bool parse_gravity(const std::string& json, double& gravity) {
  const char* p = find_key(json, "gravity");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  return parse_rational_field(p, gravity);
}

bool parse_object_section(const std::string& json, const char* key, std::string& section) {
  const char* p = find_key(json, key);
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, '{');
  if (p == nullptr) {
    return false;
  }
  int depth = 0;
  const char* start = p;
  for (; *p != '\0'; ++p) {
    if (*p == '{') {
      ++depth;
    } else if (*p == '}') {
      --depth;
      if (depth == 0) {
        section.assign(start, static_cast<std::size_t>(p - start + 1));
        return true;
      }
    }
  }
  return false;
}

bool parse_ball_block(const std::string& ball_json, engine::BallSpec& ball, double gravity) {
  const char* p = find_key(ball_json, "ball_id");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_int_field(p, ball.ball_id)) {
    return false;
  }
  std::string pos_section;
  if (!parse_object_section(ball_json, "pos", pos_section)) {
    return false;
  }
  p = find_key(pos_section, "x");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ball.init.x0)) {
    return false;
  }
  p = find_key(pos_section, "y");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ball.init.y0)) {
    return false;
  }
  std::string vel_section;
  if (!parse_object_section(ball_json, "vel", vel_section)) {
    return false;
  }
  p = find_key(vel_section, "vx");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ball.init.vx)) {
    return false;
  }
  p = find_key(vel_section, "vy");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ball.init.vy)) {
    return false;
  }
  p = find_key(ball_json, "restitution");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ball.restitution)) {
    return false;
  }
  ball.init.g = gravity;
  return true;
}

bool parse_initial_state(const std::string& json, CalibrationScenario& out, double gravity) {
  const char* block = find_key(json, "initial_state");
  if (block == nullptr) {
    return false;
  }
  block = strchr(block, '[');
  if (block == nullptr) {
    return false;
  }
  ++block;
  out.ball_count = 0;
  while (true) {
    block = skip_ws(block);
    if (*block == ']') {
      break;
    }
    if (*block != '{') {
      return false;
    }
    if (out.ball_count >= kMaxScenarioBalls) {
      return false;
    }
    int depth = 0;
    const char* start = block;
    for (; *block != '\0'; ++block) {
      if (*block == '{') {
        ++depth;
      } else if (*block == '}') {
        --depth;
        if (depth == 0) {
          break;
        }
      }
    }
    if (*block != '}') {
      return false;
    }
    const std::string ball_json(start, static_cast<std::size_t>(block - start + 1));
    auto& ball = out.balls[static_cast<std::size_t>(out.ball_count)];
    if (!parse_ball_block(ball_json, ball, gravity)) {
      return false;
    }
    ++out.ball_count;
    ++block;
    block = skip_ws(block);
    if (*block == ',') {
      ++block;
      continue;
    }
    if (*block == ']') {
      break;
    }
    return false;
  }
  return out.ball_count > 0;
}

bool parse_reference_event_block(const std::string& event_json, ReferenceEvent& ref) {
  const char* p = find_key(event_json, "t");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ref.t)) {
    return false;
  }
  p = find_key(event_json, "ball_id");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_int_field(p, ref.ball_id)) {
    return false;
  }
  std::string contact_section;
  if (!parse_object_section(event_json, "contact", contact_section)) {
    return false;
  }
  p = find_key(contact_section, "x");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ref.contact_x)) {
    return false;
  }
  p = find_key(contact_section, "y");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_rational_field(p, ref.contact_y)) {
    return false;
  }
  p = find_key(event_json, "seq");
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  return parse_int_field(p, ref.seq);
}

bool parse_reference_events(const std::string& json, CalibrationScenario& out) {
  const char* block = find_key(json, "reference_events");
  if (block == nullptr) {
    return false;
  }
  block = strchr(block, '[');
  if (block == nullptr) {
    return false;
  }
  ++block;
  out.ref_event_count = 0;
  while (true) {
    block = skip_ws(block);
    if (*block == ']') {
      break;
    }
    if (*block != '{') {
      return false;
    }
    if (out.ref_event_count >= kMaxScenarioRefEvents) {
      return false;
    }
    int depth = 0;
    const char* start = block;
    for (; *block != '\0'; ++block) {
      if (*block == '{') {
        ++depth;
      } else if (*block == '}') {
        --depth;
        if (depth == 0) {
          break;
        }
      }
    }
    if (*block != '}') {
      return false;
    }
    const std::string event_json(start, static_cast<std::size_t>(block - start + 1));
    auto& ref = out.reference_events[static_cast<std::size_t>(out.ref_event_count)];
    if (!parse_reference_event_block(event_json, ref)) {
      return false;
    }
    ++out.ref_event_count;
    ++block;
    block = skip_ws(block);
    if (*block == ',') {
      ++block;
      continue;
    }
    if (*block == ']') {
      break;
    }
    return false;
  }
  return out.ref_event_count > 0;
}

} // namespace

bool load_calibration_scenario(const char* path, CalibrationScenario& out) {
  std::ifstream in(path);
  if (!in) {
    return false;
  }
  std::ostringstream buffer;
  buffer << in.rdbuf();
  const std::string json = buffer.str();
  out = CalibrationScenario{};
  double gravity = 0.0;
  if (!parse_coeffs(json, out) || !parse_domain(json, out) || !parse_gravity(json, gravity) ||
      !parse_initial_state(json, out, gravity) || !parse_reference_events(json, out)) {
    out = CalibrationScenario{};
    return false;
  }
  return true;
}

engine::MultiBallSimResult run_calibration_scenario(const CalibrationScenario& scenario,
                                                    int max_events) {
  std::vector<double> coeff_vec(static_cast<std::size_t>(scenario.coeff_count));
  for (int i = 0; i < scenario.coeff_count; ++i) {
    coeff_vec[static_cast<std::size_t>(i)] =
        scenario.coeffs[static_cast<std::size_t>(i)];
  }
  const auto curve = curve::compile_polynomial(coeff_vec);
  return engine::simulate_multi_ball_collisions(curve, scenario.balls.data(),
                                                scenario.ball_count, scenario.domain_max,
                                                max_events);
}

} // namespace bounce::core::scenario
