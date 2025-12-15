#pragma once

#include <concepts>
#include <random>

namespace stat::concepts {

template <typename T>
concept Floating =
    std::floating_point<T>;

template <typename RNG>
concept URBG =
    std::uniform_random_bit_generator<RNG>;

template <typename Dist, typename T>
concept Distribution =
    requires(const Dist& d, T x) {
        { d.log_pdf(x) } -> Floating;
        { d.pdf(x) }     -> Floating;
    };

template <typename Estimator, typename Data>
concept Estimator =
    requires(Estimator e, const Data& d) {
        { e.fit(d) };
        { e.estimate() };
    };

} // namespace stat::concepts
