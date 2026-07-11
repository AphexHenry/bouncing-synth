// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <string_view>

namespace bounce::core::scenario {

bool parse_rational(std::string_view text, double& out);

} // namespace bounce::core::scenario
