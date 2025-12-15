#pragma once

#include <cmath>
#include <random>
#include <stat/core/error.hpp>

namespace stat::prob {

// Normal

template <stat::concepts::Floating T>
Normal<T>::Normal(T mean, T stddev)
    : mean_(mean), stddev_(stddev)
{
    if (stddev <= T(0)) {
        throw stat::domain_error("Normal: stddev must be positive");
    }
}

template <stat::concepts::Floating T>
T Normal<T>::pdf(T x) const {
    T coeff = T(1) / (stddev_ * std::sqrt(T(2) * M_PI));
    T exponent = -((x - mean_) * (x - mean_)) / (T(2) * stddev_ * stddev_);
    return coeff * std::exp(exponent);
}

template <stat::concepts::Floating T>
T Normal<T>::log_pdf(T x) const {
    return -std::log(stddev_) - T(0.5) * std::log(T(2) * M_PI)
           - ((x - mean_) * (x - mean_)) / (T(2) * stddev_ * stddev_);
}

template <stat::concepts::Floating T>
template <stat::concepts::URBG RNG>
T Normal<T>::sample(RNG& rng) const {
    std::normal_distribution<T> dist(mean_, stddev_);
    return dist(rng);
}

template <stat::concepts::Floating T>
T Normal<T>::mean() const noexcept { return mean_; }

template <stat::concepts::Floating T>
T Normal<T>::stddev() const noexcept { return stddev_; }

// Bernoulli
template <stat::concepts::Floating T>
Bernoulli<T>::Bernoulli(T p) : p_(p) {
    if (p < T(0) || p > T(1)) {
        throw stat::domain_error("Bernoulli: probability must be in [0,1]");
    }
}

template <stat::concepts::Floating T>
T Bernoulli<T>::pmf(bool x) const {
    return x ? p_ : T(1) - p_;
}

template <stat::concepts::Floating T>
T Bernoulli<T>::log_pmf(bool x) const {
    return std::log(pmf(x));
}

template <stat::concepts::Floating T>
template <stat::concepts::URBG RNG>
bool Bernoulli<T>::sample(RNG& rng) const {
    std::bernoulli_distribution dist(p_);
    return dist(rng);
}

template <stat::concepts::Floating T>
T Bernoulli<T>::probability() const noexcept { return p_; }

// Poisson
template <stat::concepts::Floating T>
Poisson<T>::Poisson(T lambda) : lambda_(lambda) {
    if (lambda <= T(0)) {
        throw stat::domain_error("Poisson: lambda must be positive");
    }
}

template <stat::concepts::Floating T>
T Poisson<T>::pmf(unsigned int k) const {
    return std::exp(-lambda_) * std::pow(lambda_, T(k)) / std::tgamma(T(k + 1));
}

template <stat::concepts::Floating T>
T Poisson<T>::log_pmf(unsigned int k) const {
    return -lambda_ + T(k) * std::log(lambda_) - std::lgamma(T(k + 1));
}

template <stat::concepts::Floating T>
template <stat::concepts::URBG RNG>
unsigned int Poisson<T>::sample(RNG& rng) const {
    std::poisson_distribution<unsigned int> dist(lambda_);
    return dist(rng);
}

template <stat::concepts::Floating T>
T Poisson<T>::lambda() const noexcept { return lambda_; }

} // namespace stat::prob
