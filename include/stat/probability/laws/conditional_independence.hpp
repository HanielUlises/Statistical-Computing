#pragma once

namespace stat::prob {

/// Marker type representing conditional independence:
///
///   X ⫫ Y | Z
///
///
/// Intended uses:
/// - Bayesian networks
/// - Graphical models
/// - Compile-time reasoning
template <typename X, typename Y, typename Z>
struct conditional_independence {
    using first  = X;
    using second = Y;
    using given  = Z;
};

template <typename X, typename Y, typename Z>
using X_independent_of_Y_given_Z =
    conditional_independence<X, Y, Z>;

} // namespace stat::prob
