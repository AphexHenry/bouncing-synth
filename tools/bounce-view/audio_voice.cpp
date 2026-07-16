// SPDX-License-Identifier: GPL-3.0-only
#include "audio_voice.hpp"

#include <algorithm>
#include <cmath>

namespace bounce_view {

namespace {

constexpr double kTwoPi = 6.283185307179586;

double waveform_sample(double f_hz, double tau_ms, double k, double tau_s) {
  const double norm = 1.0 + 0.75 * k;
  const double f = f_hz;
  const double s1 = std::sin(kTwoPi * f * tau_s);
  const double s2 = 0.5 * k * std::sin(kTwoPi * 2.0 * f * tau_s);
  const double s3 = 0.25 * k * std::sin(kTwoPi * 3.0 * f * tau_s);
  return (s1 + s2 + s3) / norm;
}

} // namespace

double sample_av2_voice(const BlipParams& params, double elapsed_ms) {
  if (params.amp <= 0.0) {
    return 0.0;
  }
  constexpr double kAttackMs = 2.0;
  double env = 1.0;
  if (elapsed_ms < kAttackMs) {
    env = elapsed_ms / kAttackMs;
  }
  const double tau_s = elapsed_ms / 1000.0;
  const double decay = std::exp(-tau_s / (params.tau_ms / 1000.0));
  return params.amp * env * decay * waveform_sample(params.f_hz, params.tau_ms, params.k, tau_s);
}

} // namespace bounce_view
