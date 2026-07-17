// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <string_view>

namespace bounce_view {

// S6: refuse held-out paths before any file open.
bool is_heldout_path(std::string_view path);

} // namespace bounce_view
