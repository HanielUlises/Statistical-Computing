#pragma once

#include "poisson_rv.hpp"

#include <random>

namespace stat::prob {

template <stat::concepts::Floating T>
PoissonRV<T>::PoissonRV(T lambda, std::size_t n_samples)
    : dist_(lambda), n_samples_(n_samples) {}

template <stat::concepts::Floating T>
std::vector<T> PoissonRV<T>::samples(std::size_t n) const {
    std::vector<T> result(n);
    std::mt19937 rng(42);
    for (auto& x : result)
        x = static_cast<T>(dist_.sample(rng));
    return result;
}

template <stat::concepts::Floating T>
T PoissonRV<T>::mean() const {
    return dist_.lambda();
}

template <stat::concepts::Floating T>
T PoissonRV<T>::theoretical_variance() const {
    return dist_.lambda();
}

}