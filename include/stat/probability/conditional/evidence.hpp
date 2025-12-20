#pragma once

#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

/// Compute Bayesian evidence:
///   p(y) = ∫ p(y | x) p(x) dx
///
/// Integrator must implement:
///   integrate(f) -> scalar
///
/// where f(x) = posterior.pdf(x, y)
template <typename Posterior,
          typename Integrator,
          typename X,
          typename Y>
auto evidence(const Posterior& posterior,
              const Integrator& integrator,
              const Y& y);

} // namespace stat::prob

#include "evidence.inl"
