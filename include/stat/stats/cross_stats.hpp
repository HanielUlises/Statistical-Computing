#pragma once

#include <vector>
#include <cstddef>
#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::stats {

/// Covariance between two datasets
template <stat::concepts::Floating T>
T covariance(const std::vector<T>& x,
             const std::vector<T>& y,
             bool unbiased = true);

/// Correlation coefficient (Pearson)
template <stat::concepts::Floating T>
T correlation(const std::vector<T>& x,
              const std::vector<T>& y);

/// Covariance matrix for multivariate data
/// data[i][j] = j-th variable of i-th observation
template <stat::concepts::Floating T>
std::vector<std::vector<T>>
covariance_matrix(const std::vector<std::vector<T>>& data,
                  bool unbiased = true);

/// Correlation matrix for multivariate data
template <stat::concepts::Floating T>
std::vector<std::vector<T>>
correlation_matrix(const std::vector<std::vector<T>>& data);

} // namespace stat::stats

#include "cross_stats.inl"
