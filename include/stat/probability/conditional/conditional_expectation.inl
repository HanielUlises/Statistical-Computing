#pragma once

#include "conditional_expectation.hpp"

namespace stat::prob {

template <typename ConditionalDist,
          typename Integrator,
          typename Function,
          typename X,
          typename Y>
auto conditional_expectation(const ConditionalDist& cond_dist,
                             const Integrator& integrator,
                             const Function& g,
                             const Y& y)
{
    return integrator.integrate(
        [&](const X& x) {
            return g(x) * cond_dist.pdf(x, y);
        }
    );
}

} // namespace stat::prob
