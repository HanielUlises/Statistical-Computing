#pragma once

#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

// Conditional distribution P(X | Y)
//
// Interpreted as:
//   y ↦ Distribution<X>
template <typename Given, typename Value>
class ConditionalDistribution {
public:
    using given_type  = Given;
    using value_type  = Value;

    ConditionalDistribution() = default;
    virtual ~ConditionalDistribution() = default;

    /// Probability mass/density P(X = x | Y = y)
    virtual value_type pdf(const value_type& x,
                            const given_type& y) const = 0;
};

} // namespace stat::prob
