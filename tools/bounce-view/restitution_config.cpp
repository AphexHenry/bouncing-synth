// SPDX-License-Identifier: GPL-3.0-only
#include "restitution_config.hpp"

#include <cmath>
#include <iostream>

namespace bounce_view {

RestitutionMode default_restitution_mode(RunKind kind) {
  return kind == RunKind::Interactive ? RestitutionMode::InteractiveDefault
                                      : RestitutionMode::ScenarioFaithful;
}

void apply_restitution_override(bounce::core::scenario::CalibrationScenario& scenario,
                                const RunConfig& cfg) {
  switch (cfg.mode) {
  case RestitutionMode::ScenarioFaithful:
    return;
  case RestitutionMode::InteractiveDefault:
    for (int i = 0; i < scenario.ball_count; ++i) {
      scenario.balls[static_cast<std::size_t>(i)].restitution = 1.0;
    }
    return;
  case RestitutionMode::OverrideUniform:
    for (int i = 0; i < scenario.ball_count; ++i) {
      scenario.balls[static_cast<std::size_t>(i)].restitution = cfg.override_r;
    }
    return;
  }
}

void print_restitution_line(const RunConfig& cfg) {
  switch (cfg.mode) {
  case RestitutionMode::ScenarioFaithful:
    std::cout << "restitution: scenario-faithful (file values used)\n";
    return;
  case RestitutionMode::InteractiveDefault:
    std::cout << "restitution: override=1 (scenario values ignored; use "
                 "--scenario-restitution to respect file)\n";
    return;
  case RestitutionMode::OverrideUniform:
    std::cout << "restitution: override=" << cfg.override_r
              << " (scenario values ignored; use --scenario-restitution to respect file)\n";
    return;
  }
}

void print_config_defaults() {
  std::cout << "path: interactive — restitution: override=1 (scenario values ignored; use "
               "--scenario-restitution to respect file)\n";
  std::cout << "path: evidence (--selftest, --perf-seconds) — restitution: "
               "scenario-faithful (file values used)\n";
}

bool effective_lossless(const RunConfig& cfg) {
  switch (cfg.mode) {
  case RestitutionMode::InteractiveDefault:
    return true;
  case RestitutionMode::OverrideUniform:
    return std::abs(cfg.override_r - 1.0) < 1e-15;
  case RestitutionMode::ScenarioFaithful:
    return false;
  }
}

} // namespace bounce_view
