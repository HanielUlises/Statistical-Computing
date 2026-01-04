#pragma once

namespace stat::prob {

/// Probability factorization law
///
/// Expresses valid decompositions of joint distributions.
///
///   p(X, Y)       = p(X | Y) p(Y)
///   p(X, Y | Z)   = p(X | Z) p(Y | Z)   if X ⟂ Y | Z
template <typename Joint,
          typename Left,
          typename Right>
struct factorization {
    using joint  = Joint;
    using left   = Left;
    using right  = Right;
};

/// Conditional factorization:
///   p(X, Y | Z) = p(X | Z) p(Y | Z)
template <typename Joint,
          typename Left,
          typename Right,
          typename Given>
struct conditional_factorization {
    using joint  = Joint;
    using left   = Left;
    using right  = Right;
    using given  = Given;
};

} // namespace stat::prob
