#pragma once

#include "bernoulli.hpp"

#include <random>

namespace stat::prob {

template <stat::concepts::Floating T>
BernoulliRV<T>::BernoulliRV(T p, std::size_t n_samples)
    : dist_(p), n_samples_(n_samples) {}

template <stat::concepts::Floating T>
std::vector<T> BernoulliRV<T>::samples(std::size_t n) const {
    std::vector<T> result(n);
    std::mt19937 rng(42);
    for (auto& x : result)
        x = static_cast<T>(dist_.sample(rng));
    return result;
}

template <stat::concepts::Floating T>
T BernoulliRV<T>::mean() const {
    return dist_.probability();
}

template <stat::concepts::Floating T>
T BernoulliRV<T>::theoretical_variance() const {
    T p = dist_.probability();
    return p * (1 - p);
}

}