#pragma once

#include "random_variable.hpp"
#include "rv_traits.hpp"

#include <numeric>
#include <cmath>
#include <stat/core/error.hpp>

namespace stat::prob {

template <stat::concepts::Floating T>
template <typename Func>
T RandomVariable<T>::expectation(Func f) const {
    auto data = samples(1'000); // default sample size for empirical expectation
    if (data.empty()) {
        throw stat::domain_error("expectation: no samples available");
    }

    T sum = std::accumulate(data.begin(), data.end(), T(0),
                            [f](T acc, T x) { return acc + f(x); });
    return sum / static_cast<T>(data.size());
}

template <stat::concepts::Floating T>
T RandomVariable<T>::variance() const {
    auto data = samples(1'000);
    if (data.size() < 2) {
        throw stat::domain_error("variance: need at least 2 samples");
    }

    T m = expectation([](T x) { return x; });
    T sum_sq = std::accumulate(data.begin(), data.end(), T(0),
                               [m](T acc, T x) { return acc + (x - m) * (x - m); });
    return sum_sq / static_cast<T>(data.size() - 1);
}

template <stat::concepts::Floating T>
T RandomVariable<T>::standard_deviation() const {
    return std::sqrt(variance());
}

} // namespace stat::prob
