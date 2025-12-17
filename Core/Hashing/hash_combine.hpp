#pragma once

#include <cstddef>
#include <utility>
#include <stat/core/hashing/hash_concepts.hpp>

namespace stat::core::hashing {

/// Combine two hash values deterministically
///
/// This is suitable for:
/// - composite keys
/// - tuples
/// - probabilistic sketches
inline std::size_t hash_combine(std::size_t h1, std::size_t h2) noexcept;

/// Combine a hash with a value using a provided hash function
template <typename H, typename T>
requires Hash<H, T>
std::size_t hash_combine(const H& h, std::size_t seed, const T& value) noexcept;

/// Variadic hash combine
template <typename H, typename T, typename... Ts>
requires Hash<H, T>
std::size_t hash_combine(const H& h,
                         std::size_t seed,
                         const T& value,
                         const Ts&... rest) noexcept;

} // namespace stat::core::hashing

#include "hash_combine.inl"
