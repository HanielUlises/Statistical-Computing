#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <limits>

#include <stat/core/hashing/hash_concepts.hpp>

namespace stat::core::hashing {

/// Carter–Wegman 2-universal hash family
///
/// h_{a,b}(x) = (a * x + b) mod P
/// where P is a large prime and a != 0
///
/// Properties:
/// - 2-universal
/// - deterministic given seed
/// - stateless
/// - suitable for sketching and randomized algorithms
template <typename Key>
requires std::is_integral_v<Key>
class UniversalHash {
public:
    using key_type = Key;
    using result_type = std::size_t;

    /// Construct from explicit seed
    explicit UniversalHash(std::size_t seed) noexcept;

    /// Hash function
    result_type operator()(key_type x) const noexcept;

private:
    std::uint64_t a_;
    std::uint64_t b_;

    static constexpr std::uint64_t prime();
};

static_assert(SeededHash<UniversalHash<std::uint64_t>>);
static_assert(StatelessHash<UniversalHash<std::uint64_t>>);

} // namespace stat::core::hashing

#include "universal_hash.inl"
