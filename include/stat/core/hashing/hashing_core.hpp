#pragma once

#include <cstddef>
#include <cstdint>

namespace stat::core::hashing {

// Canonical hash value type
using hash_value = std::size_t;

// Canonical seed type
using hash_seed = std::uint64_t;

// Default seed (golden ratio, good avalanche properties)
inline constexpr hash_seed default_seed =
    0x9e3779b97f4a7c15ULL;

// Mix function (SplitMix64 finalizer)
// Useful for building custom hash combiners
constexpr hash_value mix(hash_value x) noexcept {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

// Combine two hash values (order-sensitive)
constexpr hash_value combine(hash_value lhs, hash_value rhs) noexcept {
    return mix(lhs ^ (rhs + default_seed));
}

} // namespace stat::core::hashing
