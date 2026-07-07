// SPDX-License-Identifier: GPL-3.0-only
// Runtime assertions that the FP environment matches DELIVERABLE_B §4.
// These tests failing means the build or runtime environment violates the
// determinism surface — a gate-class failure, never something to work around.
// NOTE: std::fma is used HERE ONLY as a probe reference; bounce-core itself
// must remain libm-free (DELIVERABLE_B §4).
#include <doctest/doctest.h>
#include <cfenv>
#include <cfloat>
#include <cmath>

TEST_CASE("rounding mode is round-to-nearest-even") {
  CHECK(std::fegetround() == FE_TONEAREST);
}

TEST_CASE("no extended-precision expression evaluation") {
  CHECK(FLT_EVAL_METHOD == 0);
}

TEST_CASE("subnormals are alive (FTZ/DAZ off)") {
  volatile double t = DBL_MIN;      // smallest normal
  volatile double half = t / 2.0;   // subnormal result: flushed to 0 under FTZ
  CHECK(half > 0.0);
  volatile double quarter = half / 2.0; // subnormal operand and result (DAZ probe)
  CHECK(quarter > 0.0);
  CHECK(quarter * 4.0 == t);
}

TEST_CASE("no FP contraction: a*b + c is two IEEE roundings, not fma") {
  // (1 + 2^-29)(1 - 2^-29) = 1 - 2^-58, which rounds to exactly 1.0 in binary64.
  // Two-step:  round(a*b) + c = 1.0 - 1.0 = 0.0.
  // Contracted: fma(a,b,c)    = -2^-58 exactly.
  volatile double a = 1.0 + 0x1p-29;
  volatile double b = 1.0 - 0x1p-29;
  volatile double c = -1.0;
  double two_step = a * b + c;
  CHECK(two_step == 0.0);
  CHECK(std::fma(a, b, c) == -0x1p-58); // sanity: the probe distinguishes the cases
}
