#pragma once

#include "total_expectation.hpp"

namespace stat::prob {

template <typename ConditionalDist,
          typename MarginalY,
          typename IntegratorX,
          typename IntegratorY,
          typename X,
          typename Y>
auto total_expectation(const ConditionalDist& cond_dist,
                       const MarginalY& marginal_y,
                       const IntegratorX& integrator_x,
                       const IntegratorY& integrator_y)
{
    return integrator_y.integrate(
        [&](const Y& y) {
            auto inner = conditional_expectation<
                ConditionalDist,
                IntegratorX,
                decltype([](const X& x){ return x; }),
                X,
                Y
            >(
                cond_dist,
                integrator_x,
                [](const X& x) { return x; },
                y
            );

            return inner * marginal_y.pdf(y);
        }
    );
}

} // namespace stat::prob
