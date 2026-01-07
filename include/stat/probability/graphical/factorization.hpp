#pragma once

namespace stat::prob::graphical {

/// Joint distribution factorization for Bayesian networks:
///
///   p(x₁,...,xₙ) = ∏ᵢ p(xᵢ | parents(xᵢ))
///
template <typename Joint,
          typename NodeConditionals>
struct graph_factorization {
    using joint = Joint;
    using conditionals = NodeConditionals;
};

} // namespace stat::prob::graphical
