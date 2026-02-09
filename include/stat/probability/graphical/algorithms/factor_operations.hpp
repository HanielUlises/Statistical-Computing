#pragma once

#include <stat/probability/graphical/algorithms/factor.hpp>

namespace stat::prob::graphical {

template <typename Assignment>
Factor<Assignment>
multiply(const Factor<Assignment>& a,
         const Factor<Assignment>& b)
{
    std::vector<std::size_t> vars = a.variables();
    for (auto v : b.variables())
        if (std::find(vars.begin(), vars.end(), v) == vars.end())
            vars.push_back(v);

    Factor<Assignment> result(vars);

    for (const auto& [a1, p1] : a.table()) {
        for (const auto& [a2, p2] : b.table()) {
            if (a1.compatible(a2)) {
                result.set(a1.merge(a2), p1 * p2);
            }
        }
    }

    return result;
}

} // namespace stat::prob::graphical
