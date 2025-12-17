#pragma once

#include <cstddef>
#include <limits>
#include <stat/core/hashing/hash_concepts.hpp>

namespace stat::core::hashing {

// Map a hash value uniformly into [0, m)
//
// Uses Lemire's fast modulo reduction to avoid bias.
//
// Preconditions:
// - m > 0
inline std::size_t hash_range(std::size_t h, std::size_t m) noexcept;

// Hash a value and map it into [0, m)
template <typename H, typename T>
requires Hash<H, T>
std::size_t hash_range(const H& h,
                       const T& value,
                       std::size_t m) noexcept;

} // namespace stat::core::hashing

#include "hash_range.inl"
