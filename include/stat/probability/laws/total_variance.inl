#pragma once

#include "total_variance.hpp"

namespace stat::prob {

template <typename ConditionalDist,
          typename MarginalY,
          typename IntegratorX,
          typename IntegratorY,
          typename X,
          typename Y>
auto total_variance(const ConditionalDist& cond_dist,
                    const MarginalY& marginal_y,
                    const IntegratorX& integrator_x,
                    const IntegratorY& integrator_y)
{
    // E[Var(X | Y)]
    auto term1 = integrator_y.integrate(
        [&](const Y& y) {
            auto var_xy = integrator_x.integrate(
                [&](const X& x) {
                    auto mean_xy = conditional_expectation<
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

                    auto d = x - mean_xy;
                    return d * d * cond_dist.pdf(x, y);
                }
            );

            return var_xy * marginal_y.pdf(y);
        }
    );

    // Var(E[X | Y])
    auto mean_x = total_expectation<
        ConditionalDist,
        MarginalY,
        IntegratorX,
        IntegratorY,
        X,
        Y
    >(cond_dist, marginal_y, integrator_x, integrator_y);

    auto term2 = integrator_y.integrate(
        [&](const Y& y) {
            auto mean_xy = conditional_expectation<
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

            auto d = mean_xy - mean_x;
            return d * d * marginal_y.pdf(y);
        }
    );

    return term1 + term2;
}

} // namespace stat::prob
