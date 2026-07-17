// SPDX-License-Identifier: GPL-3.0-only
#include "build_stamp.hpp"

#include "build_stamp_generated.hpp"

#include <iostream>
#include <string>

namespace bounce_view {

void print_build_stamp() {
  std::cout << "bounce-view build " << build_stamp::kShortCommit << " (" << build_stamp::kBranch
            << build_stamp::kDirty << ")\n";
}

std::string build_stamp_short_commit() { return build_stamp::kShortCommit; }

std::string build_stamp_window_title() {
  return std::string("bounce-view ") + build_stamp::kShortCommit;
}

} // namespace bounce_view
