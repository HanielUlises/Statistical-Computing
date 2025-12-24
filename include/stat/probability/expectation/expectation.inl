#pragma once

namespace stat::prob {

template <typename Dist,
          typename Integrator,
          typename Function,
          typename X>
auto expectation(const Dist& dist,
                 const Integrator& integrator,
                 const Function& g)
{
    return integrator.integrate(
        [&](const X& x) {
            return g(x) * dist.pdf(x);
        }
    );
}

} // namespace stat::prob
