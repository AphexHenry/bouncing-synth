// SPDX-License-Identifier: GPL-3.0-only
#include <doctest/doctest.h>
#include <cstring>
#include "bounce/version.hpp"

TEST_CASE("bounce-core exposes its versioned identity") {
  CHECK(std::strcmp(bounce::core::engine_version(), "0.1.0") == 0);
  CHECK(std::strcmp(bounce::core::tie_break_version(), "TB-1") == 0);
  CHECK(std::strcmp(bounce::core::contact_rule_version(), "G-1/S-1") == 0);
}
