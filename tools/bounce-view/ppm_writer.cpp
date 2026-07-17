// SPDX-License-Identifier: GPL-3.0-only
#include "ppm_writer.hpp"

#include <fstream>

namespace bounce_view {

bool write_ppm(const char* path, int width, int height, const std::vector<std::uint8_t>& rgb) {
  if (width <= 0 || height <= 0) {
    return false;
  }
  const std::size_t expected = static_cast<std::size_t>(width) * static_cast<std::size_t>(height) * 3;
  if (rgb.size() != expected) {
    return false;
  }
  std::ofstream out(path, std::ios::binary);
  if (!out) {
    return false;
  }
  out << "P6\n" << width << ' ' << height << "\n255\n";
  out.write(reinterpret_cast<const char*>(rgb.data()), static_cast<std::streamsize>(rgb.size()));
  return static_cast<bool>(out);
}

} // namespace bounce_view
