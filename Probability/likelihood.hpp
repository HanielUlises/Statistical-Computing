#pragma once

#include <vector>
#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

template <stat::concepts::Distribution Dist, stat::concepts::Floating T>
T likelihood(const Dist& dist, const std::vector<T>& data);

template <stat::concepts::Distribution Dist, stat::concepts::Floating T>
T log_likelihood(const Dist& dist, const std::vector<T>& data);

} // namespace stat::prob

#include "likelihood.inl"
