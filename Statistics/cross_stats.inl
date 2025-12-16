#pragma once

#include "cross_stats.hpp"

namespace stat::stats {

namespace detail {

template <stat::concepts::Floating T>
T mean(const std::vector<T>& v) {
    if (v.empty())
        throw stat::domain_error("mean: empty data");

    T sum = std::accumulate(v.begin(), v.end(), T(0));
    return sum / static_cast<T>(v.size());
}

} // namespace detail

// Covariance

template <stat::concepts::Floating T>
T covariance(const std::vector<T>& x,
             const std::vector<T>& y,
             bool unbiased) {

    if (x.size() != y.size())
        throw stat::domain_error("covariance: size mismatch");

    if (x.size() < 2)
        throw stat::domain_error("covariance: need at least two observations");

    T mx = detail::mean(x);
    T my = detail::mean(y);

    T sum = T(0);
    for (std::size_t i = 0; i < x.size(); ++i)
        sum += (x[i] - mx) * (y[i] - my);

    T denom = unbiased ? static_cast<T>(x.size() - 1)
                       : static_cast<T>(x.size());

    return sum / denom;
}


// Correlation
template <stat::concepts::Floating T>
T correlation(const std::vector<T>& x,
              const std::vector<T>& y) {

    T cov = covariance(x, y, true);
    T vx  = covariance(x, x, true);
    T vy  = covariance(y, y, true);

    if (vx <= T(0) || vy <= T(0))
        throw stat::domain_error("correlation: zero variance");

    return cov / std::sqrt(vx * vy);
}

// Covariance matrix
template <stat::concepts::Floating T>
std::vector<std::vector<T>>
covariance_matrix(const std::vector<std::vector<T>>& data,
                  bool unbiased) {

    if (data.empty())
        throw stat::domain_error("covariance_matrix: empty data");

    std::size_t n_obs = data.size();
    std::size_t dim   = data[0].size();

    if (dim == 0)
        throw stat::domain_error("covariance_matrix: zero dimension");

    for (const auto& row : data)
        if (row.size() != dim)
            throw stat::domain_error("covariance_matrix: inconsistent row size");

    // transpose: variables as vectors
    std::vector<std::vector<T>> vars(dim, std::vector<T>(n_obs));
    for (std::size_t i = 0; i < n_obs; ++i)
        for (std::size_t j = 0; j < dim; ++j)
            vars[j][i] = data[i][j];

    std::vector<std::vector<T>> cov(dim, std::vector<T>(dim, T(0)));

    for (std::size_t i = 0; i < dim; ++i)
        for (std::size_t j = i; j < dim; ++j) {
            T c = covariance(vars[i], vars[j], unbiased);
            cov[i][j] = c;
            cov[j][i] = c;
        }

    return cov;
}

// Correlation matrix
template <stat::concepts::Floating T>
std::vector<std::vector<T>>
correlation_matrix(const std::vector<std::vector<T>>& data) {

    auto cov = covariance_matrix(data, true);
    std::size_t dim = cov.size();

    std::vector<T> stddev(dim);
    for (std::size_t i = 0; i < dim; ++i) {
        if (cov[i][i] <= T(0))
            throw stat::domain_error("correlation_matrix: zero variance");
        stddev[i] = std::sqrt(cov[i][i]);
    }

    std::vector<std::vector<T>> corr(dim, std::vector<T>(dim, T(0)));

    for (std::size_t i = 0; i < dim; ++i)
        for (std::size_t j = 0; j < dim; ++j)
            corr[i][j] = cov[i][j] / (stddev[i] * stddev[j]);

    return corr;
}

} // namespace stat::stats