#pragma once

#include <stat/probability/expectation/expectation.hpp>
#include <stat/probability/conditional/conditional_distribution.hpp>

namespace stat::prob {

/// Conditional expectation:
///
///   E[g(X) | Y = y] = ∫ g(x) p(x | y) dx
///
/// Requirements:
/// - ConditionalDist must expose pdf(x, y)
/// - Integrator must implement integrate(f)
///
/// This is a *function-valued* expectation in theory,
/// but here we evaluate it at a fixed y.
template <typename ConditionalDist,
          typename Integrator,
          typename Function,
          typename X,
          typename Y>
auto conditional_expectation(const ConditionalDist& cond_dist,
                             const Integrator& integrator,
                             const Function& g,
                             const Y& y);

} // namespace stat::prob

#include "conditional_expectation.inl"
