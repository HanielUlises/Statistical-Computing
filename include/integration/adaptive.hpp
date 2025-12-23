#pragma once

#include <stat/core/concepts.hpp>

namespace stat::analysis::integration {

template <stat::concepts::Floating T>
class AdaptiveSimpson {
public:
    AdaptiveSimpson(T tol, std::size_t max_depth = 10);

    template <typename F>
    T integrate(F&& f) const;

private:
    T tol_;
    std::size_t max_depth_;

    template <typename F>
    T recurse(F&& f, T a, T b, T fa, T fb, T fm,
              T whole, std::size_t depth) const;
};

} // namespace stat::analysis::integration

#include "adaptive.inl"
