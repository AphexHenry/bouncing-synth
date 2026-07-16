// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/scenario/calibration_loader.hpp"

namespace bounce_view {

enum class RunKind { Interactive, Evidence };

enum class RestitutionMode {
  ScenarioFaithful,
  OverrideUniform,
  InteractiveDefault,
};

struct RunConfig {
  RunKind kind = RunKind::Interactive;
  RestitutionMode mode = RestitutionMode::InteractiveDefault;
  double override_r = 1.0;
  int max_events = 200;
};

RestitutionMode default_restitution_mode(RunKind kind);

void apply_restitution_override(bounce::core::scenario::CalibrationScenario& scenario,
                                const RunConfig& cfg);

void print_restitution_line(const RunConfig& cfg);

void print_config_defaults();

bool effective_lossless(const RunConfig& cfg);

} // namespace bounce_view
