// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace bounce_view {

bool write_ppm(const char* path, int width, int height, const std::vector<std::uint8_t>& rgb);

} // namespace bounce_view
