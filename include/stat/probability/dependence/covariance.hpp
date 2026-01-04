#pragma once

#include <stat/probability/expectation/expectation.hpp>

namespace stat::prob {

/// Covariance between two random variables:
///
///   Cov(X, Y) = E[(X - E[X])(Y - E[Y])]
///
/// 
/// Joint Distribution must expose joint pdf: pdf(x, y)
/// Integrator must integrate over the joint domain
template <typename JointDist,
          typename Integrator,
          typename X,
          typename Y>
auto covariance(const JointDist& joint_dist,
                const Integrator& integrator);

} // namespace stat::prob

#include "covariance.inl"
