#pragma once

namespace stat::prob {

template <typename Dist,
          typename Integrator,
          typename X>
auto variance(const Dist& dist,
              const Integrator& integrator)
{
    auto mean = expectation<Dist, Integrator, X>(
        dist,
        integrator,
        [](const X& x) { return x; }
    );

    return expectation<Dist, Integrator, X>(
        dist,
        integrator,
        [&](const X& x) {
            auto d = x - mean;
            return d * d;
        }
    );
}

} // namespace stat::prob
