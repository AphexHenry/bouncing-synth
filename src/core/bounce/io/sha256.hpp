// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace bounce::core::io {

constexpr std::size_t kSha256DigestBytes = 32;

bool sha256_file(const char* path, std::array<unsigned char, kSha256DigestBytes>& digest);

std::string sha256_hex(const std::array<unsigned char, kSha256DigestBytes>& digest);

} // namespace bounce::core::io
