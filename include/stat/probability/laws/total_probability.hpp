#pragma once

namespace stat::prob {

/// Law of Total Probability
///
/// Expresses that a marginal distribution can be obtained
/// by integrating (or summing) over a conditional.
///
///   p(Y) = ∫ p(Y | X) p(X) dX
///
/// This is a structural / axiomatic law, not a numerical routine.
template <typename Marginal,
          typename Conditional,
          typename Prior>
struct total_probability {
    using marginal     = Marginal;
    using conditional  = Conditional;
    using prior        = Prior;
};

} // namespace stat::prob
