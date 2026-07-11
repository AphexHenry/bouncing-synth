// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/scenario/rational.hpp"

#include <charconv>
#include <cmath>
#include <cstdlib>

namespace bounce::core::scenario {

namespace {

bool parse_integer(std::string_view text, long long& out) {
  while (!text.empty() && text.front() == ' ') {
    text.remove_prefix(1);
  }
  while (!text.empty() && text.back() == ' ') {
    text.remove_suffix(1);
  }
  if (text.empty()) {
    return false;
  }
  const char* begin = text.data();
  const char* end = text.data() + text.size();
  const auto result = std::from_chars(begin, end, out);
  return result.ec == std::errc{} && result.ptr == end;
}

} // namespace

bool parse_rational(std::string_view text, double& out) {
  while (!text.empty() && text.front() == ' ') {
    text.remove_prefix(1);
  }
  while (!text.empty() && text.back() == ' ') {
    text.remove_suffix(1);
  }
  if (text.empty()) {
    return false;
  }
  const std::size_t slash = text.find('/');
  if (slash == std::string_view::npos) {
    long long whole = 0;
    if (!parse_integer(text, whole)) {
      return false;
    }
    out = static_cast<double>(whole);
    return std::isfinite(out);
  }
  long long num = 0;
  long long den = 0;
  if (!parse_integer(text.substr(0, slash), num)) {
    return false;
  }
  if (!parse_integer(text.substr(slash + 1), den) || den == 0) {
    return false;
  }
  out = static_cast<double>(num) / static_cast<double>(den);
  return std::isfinite(out);
}

} // namespace bounce::core::scenario
