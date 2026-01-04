#pragma once

#include <cmath>

#include <stat/probability/dependence/covariance.hpp>
#include <stat/probability/expectation/variance.hpp>

namespace stat::prob {

/// Pearson correlation coefficient:
///
///   ρ(X, Y) = Cov(X, Y) / sqrt(Var(X) Var(Y))
///
///
/// Joint distribution must expose pdf(x, y)
/// Marginals must be accessible from joint distribution
///   via marginal_x() and marginal_y()
template <typename JointDist,
          typename Integrator,
          typename X,
          typename Y>
auto correlation(const JointDist& joint_dist,
                 const Integrator& integrator);

} // namespace stat::prob

#include "correlation.inl"
