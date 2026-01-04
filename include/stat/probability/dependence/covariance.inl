#pragma once

#include "covariance.hpp"

namespace stat::prob {

template <typename JointDist,
          typename Integrator,
          typename X,
          typename Y>
auto covariance(const JointDist& joint_dist,
                const Integrator& integrator)
{
    // E[X]
    auto Ex = integrator.integrate(
        [&](const X& x, const Y& y) {
            return x * joint_dist.pdf(x, y);
        }
    );

    // E[Y]
    auto Ey = integrator.integrate(
        [&](const X& x, const Y& y) {
            return y * joint_dist.pdf(x, y);
        }
    );

    // E[(X - Ex)(Y - Ey)]
    return integrator.integrate(
        [&](const X& x, const Y& y) {
            return (x - Ex) * (y - Ey) * joint_dist.pdf(x, y);
        }
    );
}

} // namespace stat::prob
