#pragma once

#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>
#include <vector>
#include "rv_traits.hpp"

namespace stat::prob {

template <stat::concepts::Floating T>
class RandomVariable {
public:
    RandomVariable() = default;
    virtual ~RandomVariable() = default;

    template <typename Func>
    T expectation(Func f) const;

    // Variance
    T variance() const;

    // Standard deviation
    T standard_deviation() const;

    virtual std::vector<T> samples(std::size_t n) const = 0;

    // Theoretical mean and variance
    virtual T mean() const = 0;
    virtual T theoretical_variance() const = 0;
};

} // namespace stat::prob

#include "random_variable.inl"
