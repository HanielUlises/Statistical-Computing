#pragma once

#include <tuple>
#include <utility>
#include <stat/core/hashing/hash_concepts.hpp>
#include <stat/core/hashing/hash_combine.hpp>

namespace stat::core::hashing {

// Hash a std::tuple using a given hash function
template <typename H, typename... Ts>
requires (Hash<H, Ts> && ...)
std::size_t hash_tuple(const H& h,
                       const std::tuple<Ts...>& t,
                       std::size_t seed = 0) noexcept;

} // namespace stat::core::hashing

#include "tuple_hash.inl"
