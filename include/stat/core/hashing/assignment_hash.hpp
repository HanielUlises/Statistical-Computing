#pragma once

#include <functional>
#include <stat/probability/graphical/assignment.hpp>

namespace std {

template <typename V>
struct hash<stat::prob::graphical::assignment<V>> {
    std::size_t operator()(
        const stat::prob::graphical::assignment<V>& a
    ) const noexcept {
        std::size_t h = 0;
        for (const auto& [k, v] : a.values_) {
            h ^= std::hash<std::size_t>{}(k)
               + 0x9e3779b97f4a7c15ULL
               + (h << 6) + (h >> 2);
        }
        return h;
    }
};

} // namespace std
