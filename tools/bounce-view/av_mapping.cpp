// SPDX-License-Identifier: GPL-3.0-only
#include "av_mapping.hpp"

#include <algorithm>
#include <cmath>

namespace bounce_view {

BlipParams blip_params(const bounce::core::scenario::CalibrationScenario& scenario,
                       const bounce::core::events::CollisionEvent& event) {
  const double span = scenario.domain_max - scenario.domain_min;
  double u = 0.0;
  if (span > 0.0) {
    u = (event.s - scenario.domain_min) / span;
  }
  u = std::clamp(u, 0.0, 1.0);
  const double k = std::min(1.0, std::abs(event.impact_speed) / 10.0);
  BlipParams out{};
  out.f_hz = 220.0 * std::pow(2.0, 2.0 * u);
  out.k = k;
  out.amp = 0.3 * k;
  out.tau_ms = 80.0 * (0.5 + 0.5 * k);
  return out;
}

} // namespace bounce_view
