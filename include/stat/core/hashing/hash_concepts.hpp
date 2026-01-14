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

// A stateless hash has no internal state beyond its type
template <typename H>
concept StatelessHash =
    std::is_trivially_copyable_v<H> &&
    std::is_trivially_destructible_v<H>;

// A stateful hash explicitly carries internal parameters
template <typename H>
concept StatefulHash =
    !StatelessHash<H>;

// A deterministic hash produces identical outputs
// for identical inputs given the same constructed instance
template <typename H, typename Key>
concept DeterministicHash =
    Hash<H, Key>;

// A UniversalHash models a member of a universal hash family
// (i.e. parameterized by a seed / random choice)
template <typename H>
concept UniversalHash =
    SeededHash<H> &&
    StatefulHash<H>;

} // namespace stat::core::hashing
