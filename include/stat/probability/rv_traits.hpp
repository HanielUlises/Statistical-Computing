#pragma once

#include "random_variable.hpp"
#include "distributions/random_variables/bernoulli_rv.hpp"
#include "distributions/random_variables/normal_rv.hpp"
#include "distributions/random_variables/poisson_rv.hpp"

#include <type_traits>
#include <stat/core/concepts.hpp>

namespace stat::prob {

// Default traits: unknown type
template <typename RV>
struct rv_traits {
    static constexpr bool is_discrete = false;
    static constexpr bool is_continuous = false;
};

// Base RandomVariable<T> is continuous
template <stat::concepts::Floating T>
struct rv_traits<RandomVariable<T>> {
    static constexpr bool is_discrete = false;
    static constexpr bool is_continuous = true;
};

// Concrete wrapper specializations
template <stat::concepts::Floating T>
struct rv_traits<NormalRV<T>> {
    static constexpr bool is_discrete = false;
    static constexpr bool is_continuous = true;
};

template <stat::concepts::Floating T>
struct rv_traits<BernoulliRV<T>> {
    static constexpr bool is_discrete = true;
    static constexpr bool is_continuous = false;
};

template <stat::concepts::Floating T>
struct rv_traits<PoissonRV<T>> {
    static constexpr bool is_discrete = true;
    static constexpr bool is_continuous = false;
};

} // namespace stat::prob
