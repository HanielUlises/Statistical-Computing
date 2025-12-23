#pragma once

#include <cmath>

#include "adaptive.hpp"

namespace stat::analysis::integration {

template <stat::concepts::Floating T>
AdaptiveSimpson<T>::AdaptiveSimpson(T tol, std::size_t max_depth)
    : tol_(tol), max_depth_(max_depth) {}

template <stat::concepts::Floating T>
template <typename F>
T AdaptiveSimpson<T>::integrate(F&& f) const
{
    T a = T{0};
    T b = T{1};

    T fa = f(a);
    T fb = f(b);
    T m  = (a + b) / T{2};
    T fm = f(m);

    T whole = (b - a) * (fa + T{4} * fm + fb) / T{6};

    return recurse(f, a, b, fa, fb, fm, whole, max_depth_);
}

template <stat::concepts::Floating T>
template <typename F>
T AdaptiveSimpson<T>::recurse(
    F&& f,
    T a,
    T b,
    T fa,
    T fb,
    T fm,
    T whole,
    std::size_t depth) const
{
    T m  = (a + b) / T{2};
    T lm = (a + m) / T{2};
    T rm = (m + b) / T{2};

    T flm = f(lm);
    T frm = f(rm);

    T left  = (m - a) * (fa + T{4} * flm + fm) / T{6};
    T right = (b - m) * (fm + T{4} * frm + fb) / T{6};

    T delta = left + right - whole;

    if (depth == 0 || std::abs(delta) < T{15} * tol_)
        return left + right + delta / T{15};

    return recurse(f, a, m, fa, fm, flm, left, depth - 1) +
           recurse(f, m, b, fm, fb, frm, right, depth - 1);
}

} // namespace stat::analysis::integration
