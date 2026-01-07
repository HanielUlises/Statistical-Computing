#pragma once

namespace stat::prob {

/// Bayes' Rule (structural form)
///
///   p(X | Y) ∝ p(Y | X) p(X)
///
/// Normalization is given by the evidence:
///   p(Y) = ∫ p(Y | X) p(X) dX
///
/// This header expresses the *law*, not the computation.
template <typename Posterior,
          typename Likelihood,
          typename Prior,
          typename Evidence>
struct bayes_rule {
    using posterior  = Posterior;
    using likelihood = Likelihood;
    using prior      = Prior;
    using evidence   = Evidence;
};

} // namespace stat::prob
