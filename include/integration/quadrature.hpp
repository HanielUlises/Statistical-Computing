#pragma once

#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::analysis::integration {

template <stat::concepts::Floating T>
class SimpsonQuadrature {
public:
    SimpsonQuadrature(T a, T b, std::size_t n);

    template <typename F>
    T integrate(F&& f) const;

private:
    T a_;
    T b_;
    std::size_t n_;
};

} // namespace stat::analysis::integration

#include "quadrature.inl"
