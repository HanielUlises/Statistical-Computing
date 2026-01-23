#pragma once

#include "hash_combine.hpp"

namespace stat::core::hashing {

inline std::size_t hash_combine(std::size_t h1, std::size_t h2) noexcept {
    constexpr std::size_t magic = 0x9e3779b97f4a7c15ULL;
    return h1 ^ (h2 + magic + (h1 << 6) + (h1 >> 2));
}

// Hash + value
template <typename H, typename T>
requires Hash<H, T>
std::size_t hash_combine(const H& h,
                         std::size_t seed,
                         const T& value) noexcept {
    return hash_combine(seed, h(value));
}

template <typename H, typename T, typename... Ts>
requires Hash<H, T>
std::size_t hash_combine(const H& h,
                         std::size_t seed,
                         const T& value,
                         const Ts&... rest) noexcept {
    std::size_t combined = hash_combine(h, seed, value);
    if constexpr (sizeof...(Ts) == 0) {
        return combined;
    } else {
        return hash_combine(h, combined, rest...);
    }
}

} // namespace stat::core::hashing
