#pragma once

namespace stat::prob {

/// Tower property (law of iterated expectations)
///
///   E[ E[X | Y] ] = E[X]
///
/// Intended use:
/// - Reasoning about expectations
/// - Simplifying expressions
/// - Enabling algebraic reductions
template <typename X, typename Given>
struct tower_property {
    using variable = X;
    using condition = Given;
};

template <typename X, typename Given>
using law_of_iterated_expectation =
    tower_property<X, Given>;

} // namespace stat::prob
