// SPDX-License-Identifier: GPL-3.0-only
#pragma once

namespace bounce::core::events {

// PROJECT §6 CollisionEvent schema (explicit-polynomial: s is the x contact parameter).
struct CollisionEvent {
  double t = 0.0;
  int ball_id = 0;
  double s = 0.0;
  double impact_speed = 0.0;
  double normal_x = 0.0;
  double normal_y = 0.0;
  int seq = 0;
  int schema_version = 1;
};

} // namespace bounce::core::events
