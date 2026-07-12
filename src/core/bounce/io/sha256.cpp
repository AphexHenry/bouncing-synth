// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/io/sha256.hpp"

#include <cstdio>
#include <fstream>
#include <sstream>

namespace bounce::core::io {
namespace {

constexpr unsigned kInit[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                               0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
constexpr unsigned kRoundK[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

unsigned rotr(unsigned x, unsigned n) { return (x >> n) | (x << (32U - n)); }

void process_block(const unsigned char block[64], unsigned state[8]) {
  unsigned w[64];
  for (int i = 0; i < 16; ++i) {
    w[i] = (static_cast<unsigned>(block[i * 4]) << 24) |
           (static_cast<unsigned>(block[i * 4 + 1]) << 16) |
           (static_cast<unsigned>(block[i * 4 + 2]) << 8) |
           static_cast<unsigned>(block[i * 4 + 3]);
  }
  for (int i = 16; i < 64; ++i) {
    const unsigned s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
    const unsigned s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
    w[i] = w[i - 16] + s0 + w[i - 7] + s1;
  }
  unsigned a = state[0];
  unsigned b = state[1];
  unsigned c = state[2];
  unsigned d = state[3];
  unsigned e = state[4];
  unsigned f = state[5];
  unsigned g = state[6];
  unsigned h = state[7];
  for (int i = 0; i < 64; ++i) {
    const unsigned s1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
    const unsigned ch = (e & f) ^ ((~e) & g);
    const unsigned temp1 = h + s1 + ch + kRoundK[i] + w[i];
    const unsigned s0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
    const unsigned maj = (a & b) ^ (a & c) ^ (b & c);
    const unsigned temp2 = s0 + maj;
    h = g;
    g = f;
    f = e;
    e = d + temp1;
    d = c;
    c = b;
    b = a;
    a = temp1 + temp2;
  }
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;
  state[5] += f;
  state[6] += g;
  state[7] += h;
}

void finalize_digest(unsigned state[8], std::array<unsigned char, kSha256DigestBytes>& digest) {
  for (int i = 0; i < 8; ++i) {
    digest[static_cast<std::size_t>(i * 4)] = static_cast<unsigned char>((state[i] >> 24) & 0xff);
    digest[static_cast<std::size_t>(i * 4 + 1)] = static_cast<unsigned char>((state[i] >> 16) & 0xff);
    digest[static_cast<std::size_t>(i * 4 + 2)] = static_cast<unsigned char>((state[i] >> 8) & 0xff);
    digest[static_cast<std::size_t>(i * 4 + 3)] = static_cast<unsigned char>(state[i] & 0xff);
  }
}

} // namespace

bool sha256_file(const char* path, std::array<unsigned char, kSha256DigestBytes>& digest) {
  std::ifstream in(path, std::ios::binary);
  if (!in) {
    return false;
  }
  unsigned state[8];
  for (int i = 0; i < 8; ++i) {
    state[i] = kInit[i];
  }
  unsigned char block[64];
  std::uint64_t total_bits = 0;
  while (in) {
    in.read(reinterpret_cast<char*>(block), 64);
    const std::streamsize nbytes = in.gcount();
    if (nbytes == 64) {
      total_bits += 512;
      process_block(block, state);
      continue;
    }
    const auto pad_len = static_cast<std::size_t>(nbytes);
    block[pad_len] = 0x80;
    for (std::size_t i = pad_len + 1; i < 64; ++i) {
      block[i] = 0;
    }
    total_bits += static_cast<std::uint64_t>(nbytes) * 8ULL;
    if (pad_len >= 56) {
      process_block(block, state);
      for (int i = 0; i < 56; ++i) {
        block[i] = 0;
      }
    }
    for (int i = 0; i < 8; ++i) {
      block[63 - i] = static_cast<unsigned char>((total_bits >> (i * 8)) & 0xff);
    }
    process_block(block, state);
    break;
  }
  finalize_digest(state, digest);
  return true;
}

std::string sha256_hex(const std::array<unsigned char, kSha256DigestBytes>& digest) {
  std::ostringstream out;
  for (unsigned char byte : digest) {
    char buf[3];
    std::snprintf(buf, sizeof(buf), "%02x", byte);
    out << buf;
  }
  return out.str();
}

} // namespace bounce::core::io
