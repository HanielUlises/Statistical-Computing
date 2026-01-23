#pragma once

#include <cstddef>
#include <functional>

#include <stat/core/hashing/hash_combine.hpp>
#include <stat/probability/graphical/assignment.hpp>

namespace std {

template <typename Value>
struct hash<stat::prob::graphical::assignment<Value>> {
    std::size_t operator()(
        const stat::prob::graphical::assignment<Value>& a
    ) const noexcept
    {
        std::size_t seed = 0;

        for (const auto& [var, val] : a.values()) {
            std::size_t pair_hash = 0;

            stat::core::hashing::hash_combine(pair_hash, var);
            stat::core::hashing::hash_combine(pair_hash, val);

            stat::core::hashing::hash_combine(seed, pair_hash);
        }

        return seed;
    }
};

} // namespace std
