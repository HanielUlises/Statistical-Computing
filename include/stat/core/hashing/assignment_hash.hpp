#pragma once
#include <cstddef>
#include <functional>

namespace stat::core::hashing {

template<typename Value>
struct assignment_hash {
    std::size_t operator()(
        const stat::prob::graphical::assignment<Value>& a
    ) const noexcept {

        std::size_t seed = 0;

        for (const auto& [k, v] : a.values()) {
            seed ^= std::hash<std::size_t>{}(k)
                  + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            seed ^= std::hash<Value>{}(v)
                  + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

} // namespace stat::core::hashing
