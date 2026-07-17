// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <string>

namespace bounce_view {

// S14: values come from the generated header produced at configure/build from git.
void print_build_stamp();
std::string build_stamp_short_commit();
std::string build_stamp_window_title();

} // namespace bounce_view
