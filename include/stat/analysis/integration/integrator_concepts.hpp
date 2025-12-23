#pragma once

#include <concepts>

namespace stat::analysis::integration {

template <typename I, typename F>
concept Integrator =
    requires(I integ, F f) {
        { integ.integrate(f) };
    };

} // namespace stat::analysis::integration
