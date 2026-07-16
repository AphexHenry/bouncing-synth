// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/collision_sim.hpp"
#include "bounce/engine/vca.hpp"
#include "bounce/curve/polynomial.hpp"
#include "bounce/scenario/calibration_loader.hpp"

#include "bounce/numerics/double_double.hpp"

#include <doctest/doctest.h>
#include <cmath>
#include <limits>

namespace {

constexpr const char* kE4aPath =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t18/CF-E4a-wwell-e1.json";
constexpr const char* kE4bPath =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t18/CF-E4b-bezier-valley-e1.json";
constexpr const char* kE4aRef50Path =
    BOUNCE_SOURCE_DIR "/data/scenarios/calibration/t18/CF-E4a-wwell-e1-ref50.json";

bounce::core::engine::MultiBallSimResult run_fixture(const char* path, int max_events) {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(path, scenario));
  return bounce::core::scenario::run_calibration_scenario(scenario, max_events);
}

double eval_curve_dd(const bounce::core::curve::CompiledPolynomial& p, double x) {
  using bounce::core::numerics::dd_add;
  using bounce::core::numerics::dd_from_double;
  using bounce::core::numerics::dd_mul;
  using bounce::core::numerics::to_double;
  bounce::core::numerics::DoubleDouble acc =
      dd_from_double(p.coeffs[static_cast<std::size_t>(p.degree)]);
  for (int k = p.degree - 1; k >= 0; --k) {
    acc = dd_add(dd_mul(acc, dd_from_double(x)),
                 dd_from_double(p.coeffs[static_cast<std::size_t>(k)]));
  }
  return to_double(acc);
}

double energy_at_contact(double g, double y, double vx, double vy) {
  using bounce::core::numerics::dd_add;
  using bounce::core::numerics::dd_from_double;
  using bounce::core::numerics::dd_mul;
  using bounce::core::numerics::to_double;
  const auto gy = dd_mul(dd_from_double(g), dd_from_double(y));
  const auto ke =
      dd_mul(dd_from_double(0.5), dd_add(dd_mul(dd_from_double(vx), dd_from_double(vx)),
                                         dd_mul(dd_from_double(vy), dd_from_double(vy))));
  return to_double(dd_add(gy, ke));
}

constexpr int stored_events(const bounce::core::engine::MultiBallSimResult& result) {
  return std::min(result.count, static_cast<int>(bounce::core::engine::kMaxSimEvents));
}

struct PathAttribution {
  int x_primary = 0;
  int time_fallback = 0;
  int time_fine_scan = 0;
  double max_rel_x = 0.0;
  double max_rel_time = 0.0;
  double max_rel_fine = 0.0;
};

double energy_drift_over_run(const char* path, int max_events, double& e0_out,
                             PathAttribution* attribution = nullptr) {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(path, scenario));
  std::vector<double> coeffs(scenario.coeff_count);
  for (int i = 0; i < scenario.coeff_count; ++i) {
    coeffs[static_cast<std::size_t>(i)] = scenario.coeffs[static_cast<std::size_t>(i)];
  }
  const auto curve = bounce::core::curve::compile_polynomial(coeffs);
  bounce::core::engine::BallSpec ball = scenario.balls[0];
  const double g = ball.init.g;
  e0_out = energy_at_contact(g, ball.init.y0, ball.init.vx, ball.init.vy);
  double x_min = ball.init.x0;
  double e_ref = e0_out;
  double e_prev = 0.0;
  bool have_e_prev = false;
  double max_rel = 0.0;
  double max_step_rel = 0.0;
  int max_step_index = -1;
  int produced = 0;
  for (int i = 0; i < max_events; ++i) {
    const auto step = bounce::core::engine::step_ball_next_collision(
        curve, ball.init, x_min, scenario.domain_max);
    if (!step.found) {
      break;
    }
    if (!step.accepted) {
      const double vy_contact = ball.init.vy - ball.init.g * step.t;
      ball.init.x0 = step.x;
      ball.init.y0 = step.y;
      ball.init.vy = vy_contact;
      x_min = step.x;
      if (ball.init.vx > 0.0) {
        x_min = std::nextafter(step.x, std::numeric_limits<double>::infinity());
      } else if (ball.init.vx < 0.0) {
        x_min = std::nextafter(step.x, -std::numeric_limits<double>::infinity());
      }
      --i;
      continue;
    }
    const double vy_contact = ball.init.vy - ball.init.g * step.t;
    const double y_contact = eval_curve_dd(curve, step.x);
    const double ek = energy_at_contact(g, y_contact, ball.init.vx, vy_contact);
    const double rel = std::abs(ek - e0_out) / e0_out;
    if (have_e_prev) {
      const double step_rel = std::abs(ek - e_prev) / e_prev;
      if (step_rel > max_step_rel) {
        max_step_rel = step_rel;
        max_step_index = produced;
      }
    } else {
      e_prev = ek;
      have_e_prev = true;
    }
    e_prev = ek;
    max_rel = std::max(max_rel, rel);
    if (attribution != nullptr) {
      switch (step.root_path) {
      case bounce::core::engine::CollisionRootPath::XPrimary:
        ++attribution->x_primary;
        attribution->max_rel_x = std::max(attribution->max_rel_x, rel);
        break;
      case bounce::core::engine::CollisionRootPath::TimeFallback:
        ++attribution->time_fallback;
        attribution->max_rel_time = std::max(attribution->max_rel_time, rel);
        break;
      case bounce::core::engine::CollisionRootPath::TimeFineScan:
        ++attribution->time_fine_scan;
        attribution->max_rel_fine = std::max(attribution->max_rel_fine, rel);
        break;
      default:
        break;
      }
    }
    ++produced;
    const auto reflected = bounce::core::engine::reflect_velocity(
        curve, step.x, ball.init.vx, vy_contact, ball.restitution);
    ball.init.x0 = step.x;
    ball.init.y0 = step.y;
    ball.init.vx = reflected.vx;
    ball.init.vy = reflected.vy;
    x_min = step.x;
    if (ball.init.vx > 0.0) {
      x_min = std::nextafter(step.x, std::numeric_limits<double>::infinity());
    } else if (ball.init.vx < 0.0) {
      x_min = std::nextafter(step.x, -std::numeric_limits<double>::infinity());
    }
  }
  CHECK(produced == max_events);
  MESSAGE("max_step_rel=", max_step_rel, " at_event=", max_step_index);
  (void)e_ref;
  return max_rel;
}

} // namespace

TEST_CASE("T18 CF-E4a sustains 2000 confined lossless events") {
  const auto result = run_fixture(kE4aPath, 2000);
  CHECK(result.count == 2000);
}

TEST_CASE("T18 CF-E4b premature stream recorded") {
  const auto result = run_fixture(kE4bPath, 2000);
  MESSAGE("E4b events=", result.count);
  CHECK(result.count > 0);
  CHECK(result.count < 2000);
}

TEST_CASE("T18 CF-E4a per-ball times strictly increasing") {
  const auto result = run_fixture(kE4aPath, 2000);
  REQUIRE(result.count == 2000);
  const int n = stored_events(result);
  for (int i = 1; i < n; ++i) {
    const double t_prev = result.events[static_cast<std::size_t>(i - 1)].t;
    const double t_cur = result.events[static_cast<std::size_t>(i)].t;
    CHECK(t_cur > t_prev);
  }
}

TEST_CASE("T18 CF-E4a no consecutive duplicate t_hex s_hex per ball") {
  const auto result = run_fixture(kE4aPath, 2000);
  REQUIRE(result.count == 2000);
  const int n = stored_events(result);
  for (int i = 1; i < n; ++i) {
    const auto& a = result.events[static_cast<std::size_t>(i - 1)];
    const auto& b = result.events[static_cast<std::size_t>(i)];
    const bool dup = (a.t == b.t) && (a.s == b.s);
    CHECK_FALSE(dup);
  }
}

TEST_CASE("T18 CF-E4a e=1 energy drift invariant") {
  double e0 = 0.0;
  PathAttribution attribution{};
  const double max_rel = energy_drift_over_run(kE4aPath, 2000, e0, &attribution);
  MESSAGE("max_rel_energy_drift=", max_rel);
  MESSAGE("path_counts x=", attribution.x_primary, " time=", attribution.time_fallback,
          " fine=", attribution.time_fine_scan);
  MESSAGE("path_max_rel x=", attribution.max_rel_x, " time=", attribution.max_rel_time,
          " fine=", attribution.max_rel_fine);
  CHECK(max_rel <= 1e-9);
  (void)e0;
}

TEST_CASE("T18 CF-E4a agrees with tier-2 50-event reference window") {
  bounce::core::scenario::CalibrationScenario scenario{};
  REQUIRE(bounce::core::scenario::load_calibration_scenario(kE4aRef50Path, scenario));
  const auto result = run_fixture(kE4aPath, scenario.ref_event_count);
  REQUIRE(result.count == scenario.ref_event_count);
  double worst_dt = 0.0;
  double worst_ds = 0.0;
  for (int i = 0; i < scenario.ref_event_count; ++i) {
    const auto& ref = scenario.reference_events[static_cast<std::size_t>(i)];
    const auto& eng = result.events[static_cast<std::size_t>(i)];
    worst_dt = std::max(worst_dt, std::abs(eng.t - ref.t));
    worst_ds = std::max(worst_ds, std::abs(eng.s - ref.contact_x));
    CHECK(eng.ball_id == ref.ball_id);
    CHECK(eng.seq == ref.seq);
  }
  MESSAGE("worst_dt=", worst_dt, " worst_ds=", worst_ds);
  CHECK(worst_dt <= 1e-9);
  CHECK(worst_ds <= 1e-9);
}
