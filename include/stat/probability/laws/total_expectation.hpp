#pragma once

#include <stat/probability/conditional/conditional_expectation.hpp>
#include <stat/probability/expectation/expectation.hpp>

namespace stat::prob {

/// Law of total expectation:
///
///   E[X] = E_Y[ E[X | Y] ]
///
/// 
/// Conditional distribution must expose pdf(x, y)
/// MarginalY must expose pdf(y)
/// IntegratorX integrates over x
/// IntegratorY integrates over y
template <typename ConditionalDist,
          typename MarginalY,
          typename IntegratorX,
          typename IntegratorY,
          typename X,
          typename Y>
auto total_expectation(const ConditionalDist& cond_dist,
                       const MarginalY& marginal_y,
                       const IntegratorX& integrator_x,
                       const IntegratorY& integrator_y);

} // namespace stat::prob

#include "total_expectation.inl"
