// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include "bounce/events/collision_event.hpp"
#include "bounce/scenario/calibration_loader.hpp"

namespace bounce_view {

struct BlipParams {
  double f_hz = 0.0;
  double amp = 0.0;
};

BlipParams blip_params(const bounce::core::scenario::CalibrationScenario& scenario,
                       const bounce::core::events::CollisionEvent& event);

} // namespace bounce_view
