#pragma once

#include <stat/probability/distributions/bernoulli.hpp>
#include "../../random_variable.hpp"
#include <random>

namespace stat::prob {

template <stat::concepts::Floating T>
struct BernoulliRV : RandomVariable<T> {
    explicit BernoulliRV(T p, std::size_t n_samples = 1000);

    std::vector<T> samples(std::size_t n) const override;

    T mean() const override;
    T theoretical_variance() const override;

private:
    Bernoulli<T> dist_;
    std::size_t n_samples_;
};

#include "bernoulli_rv.inl"
} // namespace stat::prob
