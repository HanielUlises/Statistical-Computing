#pragma once

#include <cmath>

#include "quadrature.hpp"

namespace stat::analysis::integration {

template <stat::concepts::Floating T>
SimpsonQuadrature<T>::SimpsonQuadrature(T a, T b, std::size_t n)
    : a_(a), b_(b), n_(n)
{
    if (n_ == 0 || n_ % 2 != 0)
        throw stat::core::error(
            "SimpsonQuadrature: n must be a positive even number");
}

template <stat::concepts::Floating T>
template <typename F>
T SimpsonQuadrature<T>::integrate(F&& f) const
{
    const T h = (b_ - a_) / static_cast<T>(n_);
    T sum = f(a_) + f(b_);

    for (std::size_t i = 1; i < n_; ++i) {
        T x = a_ + h * static_cast<T>(i);
        sum += (i % 2 == 0 ? T{2} : T{4}) * f(x);
    }

    return sum * h / T{3};
}

} // namespace stat::analysis::integration
