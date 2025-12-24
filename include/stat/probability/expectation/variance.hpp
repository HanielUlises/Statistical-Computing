#pragma once

#include <stat/probability/expectation/expectation.hpp>

namespace stat::prob {

// Variance:
//
//   Var(X) = E[(X - E[X])²]
template <typename Dist,
          typename Integrator,
          typename X>
auto variance(const Dist& dist,
              const Integrator& integrator);

} // namespace stat::prob

#include "variance.inl"
