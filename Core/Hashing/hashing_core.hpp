#pragma once

#include <cstddef>
#include <concepts>
#include <type_traits>

namespace stat::core::hashing {

// A Hash must be callable with a key and return a size_t
template <typename H, typename Key>
concept Hash =
    requires(const H& h, const Key& k) {
        { h(k) } -> std::convertible_to<std::size_t>;
    };

// A seeded hash can be constructed from an explicit seed
template <typename H>
concept SeededHash =
    requires(std::size_t seed) {
        H{seed};
    };

// A statelss has has no internal state beyond construction
template <typename H>
concept StatelessHash =
    std::is_trivially_copyable_v<H> &&
    std::is_trivially_destructible_v<H>;

// A StatefulHash explicitly carries internal state
template <typename H>
concept StatefulHash =
    !StatelessHash<H>;

// A deterministic hash produces the same output for the same input
// given the same constructed instance
template <typename H, typename Key>
concept DeterministicHash =
    Hash<H, Key> &&
    requires(const H& h, const Key& k) {
        { h(k) } noexcept;
    };

// A UniversalHash models a member of a universal hash family
// (parameterized by a seed)
template <typename H>
concept UniversalHash =
    SeededHash<H> &&
    StatelessHash<H>;

} // namespace stat::core::hashing
