#pragma once

#include "normal_rv.hpp"

#include <random>

namespace stat::prob {

template <stat::concepts::Floating T>
NormalRV<T>::NormalRV(T mean, T stddev, std::size_t n_samples)
    : dist_(mean, stddev), n_samples_(n_samples) {}

template <stat::concepts::Floating T>
std::vector<T> NormalRV<T>::samples(std::size_t n) const {
    std::vector<T> result(n);
    std::mt19937 rng(42); 
    for (auto& x : result)
        x = dist_.sample(rng);
    return result;
}

template <stat::concepts::Floating T>
T NormalRV<T>::mean() const {
    return dist_.mean();
}

template <stat::concepts::Floating T>
T NormalRV<T>::theoretical_variance() const {
    T s = dist_.stddev();
    return s * s;
}


}