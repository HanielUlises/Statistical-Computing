#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <limits>

#include <stat/core/hashing/universal_hash.hpp>
#include <stat/core/hashing/hash_combine.hpp>
#include <stat/core/hashing/hash_range.hpp>

namespace stat::core::sketches {

/// Count–Min Sketch
///
/// Guarantees:
///   - Overestimates counts
///   - Error <= ε * ||f||₁ with probability 1 - δ
///
/// Parameters:
///   width  ~ e / ε
///   depth  ~ ln(1 / δ)
template <typename Key,
          typename Count = std::size_t>
class CountMinSketch {
public:
    using key_type   = Key;
    using count_type = Count;

    CountMinSketch(std::size_t width,
                   std::size_t depth,
                   std::size_t seed = 0);

    /// Increment count of key by delta
    void update(const key_type& key, count_type delta = 1) noexcept;

    /// Query estimated count
    count_type query(const key_type& key) const noexcept;

    /// Reset all counters
    void clear() noexcept;

    std::size_t width() const noexcept { return width_; }
    std::size_t depth() const noexcept { return depth_; }

private:
    std::size_t width_;
    std::size_t depth_;

    std::vector<count_type> table_;

    // One hash family, diversified by row index
    stat::core::hashing::UniversalHash<std::uint64_t> hash_;

    std::size_t index(std::size_t row,
                      const key_type& key) const noexcept;
};

} // namespace stat::core::sketches

#include "count_min.inl"
