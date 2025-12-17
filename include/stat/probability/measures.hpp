#pragma once

#include <vector>
#include <numeric>
#include <cmath>
#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

template <stat::concepts::Floating T>
T mean(const std::vector<T>& data);

template <stat::concepts::Floating T>
T variance(const std::vector<T>& data, bool sample = true);

template <stat::concepts::Floating T>
T standard_deviation(const std::vector<T>& data, bool sample = true);

#include "probability_utils.inl"
} // namespace stat::prob
