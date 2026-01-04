#pragma once

#include <stat/probability/conditional/conditional_expectation.hpp>
#include <stat/probability/expectation/variance.hpp>

namespace stat::prob {

/// Law of total variance:
///
///   Var(X) = E[Var(X | Y)] + Var(E[X | Y])
template <typename ConditionalDist,
          typename MarginalY,
          typename IntegratorX,
          typename IntegratorY,
          typename X,
          typename Y>
auto total_variance(const ConditionalDist& cond_dist,
                    const MarginalY& marginal_y,
                    const IntegratorX& integrator_x,
                    const IntegratorY& integrator_y);

} // namespace stat::prob

#include "total_variance.inl"
