#pragma once

#include "conditional_entropy.hpp"

namespace stat::prob {

template <stat::concepts::Floating T,
          typename X,
          typename Y>
T conditional_entropy(
    const ConditionalDistribution<Y, X>& cond,
    const std::vector<X>& xs,
    const std::vector<Y>& ys)
{
    if (xs.size() != ys.size())
        throw stat::core::error(
            "conditional_entropy: sample size mismatch");

    T H = T{0};

    for (std::size_t i = 0; i < xs.size(); ++i) {
        T p = cond.pdf(xs[i], ys[i]);
        if (p > T{0})
            H -= std::log(p);
    }

    return H / static_cast<T>(xs.size());
}

} // namespace stat::prob
