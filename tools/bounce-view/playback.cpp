// SPDX-License-Identifier: GPL-3.0-only
#include "playback.hpp"

#include <cmath>
#include <string>
#include <vector>

namespace bounce_view {

namespace {

void apply_event(Playback& pb, const bounce::core::events::CollisionEvent& event) {
  if (pb.scenario.curve_family == bounce::core::scenario::ScenarioCurveFamily::Polynomial) {
    const int idx = event.ball_id;
    if (idx < 0 || idx >= bounce::core::engine::kMaxBalls) {
      return;
    }
    auto& state = pb.current[static_cast<std::size_t>(idx)];
    const auto curve_y = bounce::core::curve::compile_polynomial(
        std::vector<double>(pb.scenario.coeffs.begin(),
                            pb.scenario.coeffs.begin() + pb.scenario.coeff_count));
    const double dt = event.t - pb.arc_start_t[static_cast<std::size_t>(idx)];
    const double vy_contact = state.vy - state.g * dt;
    const auto reflected =
        bounce::core::engine::reflect_velocity(curve_y, event.s, state.vx, vy_contact,
                                               pb.scenario.balls[static_cast<std::size_t>(idx)].restitution);
    if (reflected.normal_speed_out < bounce::core::engine::kVSettle) {
      pb.settled[static_cast<std::size_t>(idx)] = true;
      pb.settle_pos[static_cast<std::size_t>(idx)] = bounce::core::engine::position_at_time(state, dt);
      return;
    }
    state.x0 = event.s;
    state.y0 = bounce::core::curve::eval(curve_y, event.s);
    state.vx = reflected.vx;
    state.vy = reflected.vy;
    pb.arc_start_t[static_cast<std::size_t>(idx)] = event.t;
    return;
  }
  const int idx = event.ball_id;
  if (idx < 0 || idx >= bounce::core::engine::kMaxBalls) {
    return;
  }
  auto& state = pb.current[static_cast<std::size_t>(idx)];
  const double dt = event.t - pb.arc_start_t[static_cast<std::size_t>(idx)];
  const double vy_contact = state.vy - state.g * dt;
  const auto& curve = pb.scenario.piecewise_bezier;
  const auto pos = bounce::core::curve::eval(curve.segments.front(), event.s);
  const auto n = bounce::core::curve::normal(curve.segments.front(), event.s);
  const double vn = state.vx * n.nx + vy_contact * n.ny;
  const double restitution = pb.scenario.balls[static_cast<std::size_t>(idx)].restitution;
  bounce::core::engine::ReflectedVelocity reflected{};
  reflected.vx = state.vx - (1.0 + restitution) * vn * n.nx;
  reflected.vy = vy_contact - (1.0 + restitution) * vn * n.ny;
  reflected.normal_speed_out = std::abs(vn);
  if (reflected.normal_speed_out < bounce::core::engine::kVSettle) {
    pb.settled[static_cast<std::size_t>(idx)] = true;
    pb.settle_pos[static_cast<std::size_t>(idx)] = bounce::core::engine::position_at_time(state, dt);
    return;
  }
  state.x0 = pos.x;
  state.y0 = pos.y;
  state.vx = reflected.vx;
  state.vy = reflected.vy;
  pb.arc_start_t[static_cast<std::size_t>(idx)] = event.t;
}

} // namespace

bool load_and_simulate(const char* scenario_path, Playback& out, int max_events,
                       std::string& error) {
  out = Playback{};
  if (!bounce::core::scenario::load_calibration_scenario(scenario_path, out.scenario)) {
    error = "failed to load scenario";
    return false;
  }
  for (int i = 0; i < out.scenario.ball_count; ++i) {
    out.inits[static_cast<std::size_t>(i)] = out.scenario.balls[static_cast<std::size_t>(i)].init;
    out.current[static_cast<std::size_t>(i)] = out.inits[static_cast<std::size_t>(i)];
    out.arc_start_t[static_cast<std::size_t>(i)] = 0.0;
    out.settled[static_cast<std::size_t>(i)] = out.inits[static_cast<std::size_t>(i)].vx == 0.0;
  }

  struct Ctx {
    std::vector<bounce::core::events::CollisionEvent>* events = nullptr;
  } ctx{&out.events};

  bounce::core::engine::EventEmitSink sink{};
  sink.user_data = &ctx;
  sink.on_event = [](void* user_data, const bounce::core::events::CollisionEvent& event) -> bool {
    auto* c = static_cast<Ctx*>(user_data);
    c->events->push_back(event);
    return true;
  };

  const auto result =
      bounce::core::scenario::run_calibration_scenario(out.scenario, max_events, &sink);
  if (result.count != static_cast<int>(out.events.size())) {
    error = "event stream mismatch";
    return false;
  }
  out.end_time = out.events.empty() ? 0.0 : out.events.back().t;
  reset_playback(out);
  return true;
}

void reset_playback(Playback& pb) {
  pb.next_event = 0;
  for (int i = 0; i < pb.scenario.ball_count; ++i) {
    pb.current[static_cast<std::size_t>(i)] = pb.inits[static_cast<std::size_t>(i)];
    pb.arc_start_t[static_cast<std::size_t>(i)] = 0.0;
    pb.settled[static_cast<std::size_t>(i)] = pb.inits[static_cast<std::size_t>(i)].vx == 0.0;
  }
}

void advance_playback_to(Playback& pb, double t) {
  while (pb.next_event < pb.events.size() && pb.events[pb.next_event].t <= t + 1e-15) {
    apply_event(pb, pb.events[pb.next_event]);
    ++pb.next_event;
  }
}

BallRenderState ball_state_at(const Playback& pb, int ball_id, double t) {
  BallRenderState out{};
  if (ball_id < 0 || ball_id >= pb.scenario.ball_count) {
    out.visible = false;
    return out;
  }
  Playback scratch = pb;
  advance_playback_to(scratch, t);
  const std::size_t idx = static_cast<std::size_t>(ball_id);
  if (scratch.settled[idx]) {
    out.pos = scratch.settle_pos[idx];
    return out;
  }
  const double dt = t - scratch.arc_start_t[idx];
  if (dt < 0.0) {
    out.pos = bounce::core::engine::position_at_time(scratch.inits[idx], 0.0);
    return out;
  }
  out.pos = bounce::core::engine::position_at_time(scratch.current[idx], dt);
  return out;
}

} // namespace bounce_view
