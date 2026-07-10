// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/engine/ballistic.hpp"

#include "bounce/numerics/double_double.hpp"

#include <stdexcept>
#include <vector>

namespace bounce::core::engine {

using bounce::core::numerics::dd_add;
using bounce::core::numerics::dd_div;
using bounce::core::numerics::dd_from_double;
using bounce::core::numerics::dd_mul;
using bounce::core::numerics::to_double;

BallisticParabola ballistic_parabola_px(const BallisticInit& init) {
  if (init.vx == 0.0) {
    throw std::invalid_argument("ballistic parabola P(x) requires vx != 0");
  }
  const auto x0 = dd_from_double(init.x0);
  const auto y0 = dd_from_double(init.y0);
  const auto vx = dd_from_double(init.vx);
  const auto vy = dd_from_double(init.vy);
  const auto g = dd_from_double(init.g);

  const auto inv_vx = dd_div(dd_from_double(1.0), vx);
  const auto inv_vx2 = dd_mul(inv_vx, inv_vx);
  const auto g_over_2vx2 = dd_mul(dd_mul(dd_from_double(0.5), g), inv_vx2);

  const auto c2 = dd_mul(dd_from_double(-1.0), g_over_2vx2);
  const auto c1 = dd_add(dd_mul(vy, inv_vx), dd_mul(dd_mul(g, x0), inv_vx2));
  const auto c0 = dd_add(
      dd_add(y0, dd_mul(dd_mul(dd_from_double(-1.0), vy), dd_mul(x0, inv_vx))),
      dd_mul(dd_mul(dd_from_double(-1.0), g_over_2vx2), dd_mul(x0, x0)));

  BallisticParabola out{};
  out.x0 = init.x0;
  out.vx = init.vx;
  out.poly = bounce::core::curve::compile_polynomial(
      {to_double(c0), to_double(c1), to_double(c2)});
  return out;
}

Vec2 position_at_time(const BallisticInit& init, double t) {
  return {init.x0 + init.vx * t, init.y0 + init.vy * t - 0.5 * init.g * t * t};
}

} // namespace bounce::core::engine
