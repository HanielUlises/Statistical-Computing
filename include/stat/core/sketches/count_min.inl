#pragma once

#include "count_min.hpp"

namespace stat::core::sketches {

template <typename Key, typename Count>
CountMinSketch<Key, Count>::CountMinSketch(std::size_t width,
                                           std::size_t depth,
                                           std::size_t seed)
    : width_(width),
      depth_(depth),
      table_(width * depth, Count{}),
      hash_(seed) {}

template <typename Key, typename Count>
void CountMinSketch<Key, Count>::clear() noexcept {
    std::fill(table_.begin(), table_.end(), Count{});
}

template <typename Key, typename Count>
std::size_t
CountMinSketch<Key, Count>::index(std::size_t row,
                                  const key_type& key) const noexcept {

    using namespace stat::core::hashing;

    // Row-specific hash via composition
    std::size_t h =
        hash_combine(hash_, row, key);

    // Map into [0, width_)
    return row * width_ + hash_range(h, width_);
}

template <typename Key, typename Count>
void CountMinSketch<Key, Count>::update(const key_type& key,
                                        count_type delta) noexcept {
    for (std::size_t r = 0; r < depth_; ++r) {
        table_[index(r, key)] += delta;
    }
}

template <typename Key, typename Count>
Count
CountMinSketch<Key, Count>::query(const key_type& key) const noexcept {
    Count min = std::numeric_limits<Count>::max();

    for (std::size_t r = 0; r < depth_; ++r) {
        Count v = table_[index(r, key)];
        if (v < min)
            min = v;
    }

    return min;
}

} // namespace stat::core::sketches
