// SPDX-License-Identifier: GPL-3.0-only
#pragma once

namespace bounce::core::numerics {

// Double-double: head + tail, built without FMA (DELIVERABLE_B §4).
struct DoubleDouble {
  double hi = 0.0;
  double lo = 0.0;
};

DoubleDouble dd_from_double(double value);
double to_double(const DoubleDouble& value);

DoubleDouble dd_add(const DoubleDouble& a, const DoubleDouble& b);
DoubleDouble dd_sub(const DoubleDouble& a, const DoubleDouble& b);
DoubleDouble dd_mul(const DoubleDouble& a, const DoubleDouble& b);
DoubleDouble dd_div(const DoubleDouble& a, const DoubleDouble& b);

} // namespace bounce::core::numerics
