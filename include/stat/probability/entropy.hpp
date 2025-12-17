#pragma once

#include <vector>
#include <cmath>
#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

template <stat::concepts::Distribution Dist, stat::concepts::Floating T>
T entropy(const Dist& dist, const std::vector<T>& samples);

template <stat::concepts::Distribution Dist1, stat::concepts::Distribution Dist2, stat::concepts::Floating T>
T kl_divergence(const Dist1& p, const Dist2& q, const std::vector<T>& samples);

} // namespace stat::prob

#include "entropy.inl"
