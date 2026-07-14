// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/scenario/calibration_loader.hpp"

#include "bounce/curve/bezier.hpp"
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

bool parse_numeric_field(const char*& p, double& out) {
  p = skip_ws(p);
  if (*p == '"') {
    return parse_rational_field(p, out);
  }
  char* end = nullptr;
  const double value = std::strtod(p, &end);
  if (end == p) {
    return false;
  }
  p = end;
  out = value;
  return std::isfinite(out);
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

bool parse_array_section(const std::string& json, const char* key, std::string& section) {
  const char* p = find_key(json, key);
  if (p == nullptr) {
    return false;
  }
  p = strchr(p, '[');
  if (p == nullptr) {
    return false;
  }
  int depth = 0;
  const char* start = p;
  for (; *p != '\0'; ++p) {
    if (*p == '[') {
      ++depth;
    } else if (*p == ']') {
      --depth;
      if (depth == 0) {
        section.assign(start, static_cast<std::size_t>(p - start + 1));
        return true;
      }
    }
  }
  return false;
}

bool parse_coeffs_in_section(const std::string& section, CalibrationScenario& out) {
  const char* p = find_key(section, "coeffs");
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

bool parse_domain_in_section(const std::string& section, CalibrationScenario& out) {
  const char* p = find_key(section, "domain");
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
  std::string physics;
  if (parse_object_section(json, "physics", physics)) {
    const char* p = find_key(physics, "gravity");
    if (p != nullptr) {
      p = strchr(p, ':');
      if (p != nullptr) {
        ++p;
        return parse_rational_field(p, gravity);
      }
    }
  }
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

bool parse_curve_family(const std::string& curve_json, ScenarioCurveFamily& family) {
  const char* p = find_key(curve_json, "family");
  if (p == nullptr) {
    return false;
  }
  std::string text;
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_quoted_string(p, text)) {
    return false;
  }
  if (text == "polynomial") {
    family = ScenarioCurveFamily::Polynomial;
    return true;
  }
  if (text == "piecewise-bezier") {
    family = ScenarioCurveFamily::PiecewiseBezier;
    return true;
  }
  return false;
}

bool parse_bezier_segment(const std::string& segment_json, curve::CompiledBezierSegment& out) {
  const char* p = find_key(segment_json, "kind");
  if (p == nullptr) {
    return false;
  }
  std::string kind;
  p = strchr(p, ':');
  if (p == nullptr) {
    return false;
  }
  ++p;
  if (!parse_quoted_string(p, kind)) {
    return false;
  }
  std::string control_section;
  if (!parse_array_section(segment_json, "control", control_section)) {
    return false;
  }
  const char* cp = control_section.c_str() + 1;
  std::vector<curve::Vec2> points;
  while (true) {
    cp = skip_ws(cp);
    if (*cp == ']') {
      break;
    }
    if (*cp != '[') {
      return false;
    }
    ++cp;
    double x = 0.0;
    double y = 0.0;
    if (!parse_numeric_field(cp, x)) {
      return false;
    }
    cp = skip_ws(cp);
    if (*cp != ',') {
      return false;
    }
    ++cp;
    if (!parse_numeric_field(cp, y)) {
      return false;
    }
    cp = skip_ws(cp);
    if (*cp != ']') {
      return false;
    }
    ++cp;
    points.push_back({x, y});
    cp = skip_ws(cp);
    if (*cp == ',') {
      ++cp;
      continue;
    }
    if (*cp == ']') {
      break;
    }
    return false;
  }
  if (kind == "quadratic") {
    if (points.size() != 3) {
      return false;
    }
    out = curve::compile_quadratic_bezier(points[0], points[1], points[2]);
    return true;
  }
  if (kind == "cubic") {
    if (points.size() != 4) {
      return false;
    }
    out = curve::compile_cubic_bezier(points[0], points[1], points[2], points[3]);
    return true;
  }
  return false;
}

bool parse_piecewise_bezier(const std::string& curve_json, CalibrationScenario& out) {
  std::string segments_section;
  if (!parse_array_section(curve_json, "segments", segments_section)) {
    return false;
  }
  std::vector<curve::CompiledBezierSegment> segments;
  const char* p = segments_section.c_str() + 1;
  while (true) {
    p = skip_ws(p);
    if (*p == ']') {
      break;
    }
    if (*p != '{') {
      return false;
    }
    if (static_cast<int>(segments.size()) >= kMaxBezierSegments) {
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
          break;
        }
      }
    }
    if (*p != '}') {
      return false;
    }
    const std::string segment_json(start, static_cast<std::size_t>(p - start + 1));
    curve::CompiledBezierSegment segment{};
    if (!parse_bezier_segment(segment_json, segment)) {
      return false;
    }
    segments.push_back(segment);
    ++p;
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
  if (segments.empty()) {
    return false;
  }
  out.piecewise_bezier = curve::compile_piecewise_bezier(std::move(segments));
  return true;
}

bool parse_curve(const std::string& json, CalibrationScenario& out) {
  std::string curve_json;
  if (!parse_object_section(json, "curve", curve_json)) {
    return false;
  }
  ScenarioCurveFamily family{};
  if (!parse_curve_family(curve_json, family)) {
    return false;
  }
  out.curve_family = family;
  if (!parse_domain_in_section(curve_json, out)) {
    return false;
  }
  if (family == ScenarioCurveFamily::Polynomial) {
    return parse_coeffs_in_section(curve_json, out);
  }
  return parse_piecewise_bezier(curve_json, out);
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
  return true;
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
  if (!parse_curve(json, out) || !parse_gravity(json, gravity) ||
      !parse_initial_state(json, out, gravity) || !parse_reference_events(json, out)) {
    out = CalibrationScenario{};
    return false;
  }
  return true;
}

engine::MultiBallSimResult run_calibration_scenario(const CalibrationScenario& scenario,
                                                    int max_events,
                                                    engine::EventEmitSink* sink) {
  if (scenario.curve_family == ScenarioCurveFamily::PiecewiseBezier) {
    return engine::simulate_multi_ball_collisions_bezier(scenario.piecewise_bezier,
                                                         scenario.balls.data(),
                                                         scenario.ball_count, scenario.domain_max,
                                                         max_events, sink);
  }
  std::vector<double> coeff_vec(static_cast<std::size_t>(scenario.coeff_count));
  for (int i = 0; i < scenario.coeff_count; ++i) {
    coeff_vec[static_cast<std::size_t>(i)] =
        scenario.coeffs[static_cast<std::size_t>(i)];
  }
  const auto curve = curve::compile_polynomial(coeff_vec);
  return engine::simulate_multi_ball_collisions(curve, scenario.balls.data(), scenario.ball_count,
                                                scenario.domain_max, max_events, sink);
}

bool events_equal(const engine::MultiBallSimResult& a, const engine::MultiBallSimResult& b) {
  if (a.count != b.count) {
    return false;
  }
  for (int i = 0; i < a.count; ++i) {
    const auto& ea = a.events[static_cast<std::size_t>(i)];
    const auto& eb = b.events[static_cast<std::size_t>(i)];
    if (ea.t != eb.t || ea.ball_id != eb.ball_id || ea.s != eb.s ||
        ea.impact_speed != eb.impact_speed || ea.normal_x != eb.normal_x ||
        ea.normal_y != eb.normal_y || ea.seq != eb.seq ||
        ea.schema_version != eb.schema_version) {
      return false;
    }
  }
  return true;
}

int extract_collision_intervals(const engine::MultiBallSimResult& result,
                                std::array<double, kMaxCollisionIntervals>& intervals) {
  if (result.count < 2) {
    return 0;
  }
  const int interval_count = result.count - 1;
  for (int i = 0; i < interval_count; ++i) {
    intervals[static_cast<std::size_t>(i)] =
        result.events[static_cast<std::size_t>(i + 1)].t -
        result.events[static_cast<std::size_t>(i)].t;
  }
  return interval_count;
}

bool intervals_equal(const std::array<double, kMaxCollisionIntervals>& a,
                     const std::array<double, kMaxCollisionIntervals>& b, int count) {
  for (int i = 0; i < count; ++i) {
    if (a[static_cast<std::size_t>(i)] != b[static_cast<std::size_t>(i)]) {
      return false;
    }
  }
  return true;
}

bool agrees_with_tier1_reference(const CalibrationScenario& scenario,
                                 const engine::MultiBallSimResult& result) {
  if (result.count != scenario.ref_event_count) {
    return false;
  }
  for (int i = 0; i < scenario.ref_event_count; ++i) {
    const auto& ref = scenario.reference_events[static_cast<std::size_t>(i)];
    const auto& event = result.events[static_cast<std::size_t>(i)];
    const double t_err = event.t - ref.t;
    const double s_err = event.s - ref.contact_x;
    if (t_err > kTier1ReferenceEpsilon || t_err < -kTier1ReferenceEpsilon ||
        s_err > kTier1ReferenceEpsilon || s_err < -kTier1ReferenceEpsilon ||
        event.ball_id != ref.ball_id || event.seq != ref.seq) {
      return false;
    }
  }
  return true;
}

} // namespace bounce::core::scenario
