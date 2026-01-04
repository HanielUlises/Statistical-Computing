#pragma once

#include "correlation.hpp"

namespace stat::prob {

template <typename JointDist,
          typename Integrator,
          typename X,
          typename Y>
auto correlation(const JointDist& joint_dist,
                 const Integrator& integrator)
{
    auto cov = covariance<JointDist, Integrator, X, Y>(
        joint_dist, integrator
    );

    auto var_x = variance<
        decltype(joint_dist.marginal_x()),
        Integrator,
        X
    >(joint_dist.marginal_x(), integrator);

    auto var_y = variance<
        decltype(joint_dist.marginal_y()),
        Integrator,
        Y
    >(joint_dist.marginal_y(), integrator);

    return cov / std::sqrt(var_x * var_y);
}

} // namespace stat::prob
