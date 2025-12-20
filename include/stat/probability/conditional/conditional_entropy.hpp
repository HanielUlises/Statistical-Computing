#pragma once

#include <vector>
#include <stat/core/concepts.hpp>
#include "conditional_distribution.hpp"

namespace stat::prob {

template <stat::concepts::Floating T,
          typename X,
          typename Y>
T conditional_entropy(
    const ConditionalDistribution<Y, X>& cond,
    const std::vector<X>& x_samples,
    const std::vector<Y>& y_samples);

} // namespace stat::prob

#include "conditional_entropy.inl"
