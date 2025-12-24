#pragma once

namespace stat::prob {

template <typename Posterior,
          typename Integrator,
          typename X,
          typename Y,
          typename F>
auto expectation(const Posterior& posterior,
                 const Integrator& integrator,
                 const Y& y,
                 F&& f)
{
    auto Z = evidence<Posterior, Integrator, X, Y>(
        posterior, integrator, y
    );

    return integrator.integrate(
        [&](const X& x) {
            return f(x) * posterior.pdf(x, y);
        }
    ) / Z;
}

} // namespace stat::prob
