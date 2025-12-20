#pragma once

namespace stat::prob {

template <typename Posterior,
          typename Integrator,
          typename X,
          typename Y>
auto evidence(const Posterior& posterior,
              const Integrator& integrator,
              const Y& y)
{
    return integrator.integrate(
        [&](const X& x) {
            return posterior.pdf(x, y);
        }
    );
}

} // namespace stat::prob
