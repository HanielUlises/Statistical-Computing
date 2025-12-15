#pragma once

#include <stat/probability/distributions/poisson.hpp>
#include <stat/probability/random_variable.hpp>
#include <random>

namespace stat::prob {

template <stat::concepts::Floating T>
struct PoissonRV : RandomVariable<T> {
    explicit PoissonRV(T lambda, std::size_t n_samples = 1000);

    std::vector<T> samples(std::size_t n) const override;

    T mean() const override;
    T theoretical_variance() const override;

private:
    Poisson<T> dist_;
    std::size_t n_samples_;
};

#include "poisson_rv.inl"
} // namespace stat::prob
