#pragma once

#include <stat/probability/distributions/normal.hpp>
#include <stat/probability/random_variable.hpp>
#include <random>

namespace stat::prob {

template <stat::concepts::Floating T>
struct NormalRV : RandomVariable<T> {
    NormalRV(T mean, T stddev, std::size_t n_samples = 1000);

    std::vector<T> samples(std::size_t n) const override;

    T mean() const override;
    T theoretical_variance() const override;

private:
    Normal<T> dist_;
    std::size_t n_samples_;
};

#include "normal_rv.inl"
} // namespace stat::prob
