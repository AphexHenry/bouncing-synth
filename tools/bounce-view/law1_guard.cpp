// SPDX-License-Identifier: GPL-3.0-only
#include "law1_guard.hpp"

namespace bounce_view {

bool is_heldout_path(std::string_view path) {
  return path.find("data/scenarios/heldout/") != std::string_view::npos;
}

} // namespace bounce_view
