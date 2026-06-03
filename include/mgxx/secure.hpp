#ifndef MGXX_SECURE_HPP
#define MGXX_SECURE_HPP

#include <mongoose.h>

#include <array>
#include <cstddef>
#include <optional>
#include <string>

namespace mgxx::secure {
namespace random {
inline bool generate_bytes(void* buffer, const size_t size) {
  return mg_random(buffer, size);
}

template <size_t N>
std::array<std::byte, N> generate_bytes() {
  std::array<std::byte, N> buffer;
  if (!generate_bytes(buffer.data(), N)) {
    return {};
  }

  return buffer;
}

template <size_t N>
std::optional<std::string> generate_hex() {
  const auto bytes = generate_bytes<N>();
  if (bytes.empty()) {
    return std::nullopt;
  }

  static constexpr char base16[] = "0123456789abcdef";

  std::string buffer;
  buffer.resize(2 * N);
  for (size_t i = 0, j = 0; i < N; ++i) {
    const auto byte = std::to_integer<uint8_t>(bytes[i]);
    buffer[j++] = base16[(byte >> 4) & 0x0F];  // High nibble
    buffer[j++] = base16[byte & 0x0F];         // Low nibble
  }
  return buffer;
}
}  // namespace random
}  // namespace mgxx::secure

#endif  // MGXX_SECURE_HPP
