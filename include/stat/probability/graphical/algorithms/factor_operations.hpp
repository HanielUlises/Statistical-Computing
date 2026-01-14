#pragma once

#include "factor.hpp"

namespace stat::prob::graphical {

template <typename Assignment>
factor<Assignment>
multiply(const factor<Assignment>& f1,
         const factor<Assignment>& f2)
{
    factor<Assignment> result;
    for (auto& [a, v1] : f1.table()) {
        for (auto& [b, v2] : f2.table()) {
            if (a.compatible(b)) {
                result.set(a.merge(b), v1 * v2);
            }
        }
    }
    return result;
}

template <typename Assignment, typename Var>
factor<Assignment>
sum_out(const factor<Assignment>& f,
        const Var& var)
{
    factor<Assignment> result;
    for (auto& [a, v] : f.table()) {
        auto reduced = a.remove(var);
        result.set(reduced, result(reduced) + v);
    }
    return result;
}

} // namespace stat::prob::graphical
