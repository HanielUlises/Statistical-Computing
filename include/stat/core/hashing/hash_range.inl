#pragma once

namespace stat::core::hashing {

inline std::size_t hash_range(std::size_t h, std::size_t m) noexcept {
    // Lemire reduction: floor((h * m) / 2^64)
    return static_cast<std::size_t>(
        (static_cast<unsigned __int128>(h) * m) >> 64
    );
}

template <typename H, typename T>
requires Hash<H, T>
std::size_t hash_range(const H& h,
                       const T& value,
                       std::size_t m) noexcept {
    return hash_range(h(value), m);
}

} // namespace stat::core::hashing
