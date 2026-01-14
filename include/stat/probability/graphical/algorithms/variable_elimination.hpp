#pragma once

#include "factor_operations.hpp"

namespace stat::prob::graphical {

template <typename Factor, typename Var>
Factor variable_elimination(
    std::vector<Factor> factors,
    const std::vector<Var>& elimination_order)
{
    for (const auto& var : elimination_order) {
        std::vector<Factor> involving;
        std::vector<Factor> remaining;

        for (auto& f : factors) {
            if (f.depends_on(var))
                involving.push_back(f);
            else
                remaining.push_back(f);
        }

        Factor product = involving.front();
        for (size_t i = 1; i < involving.size(); ++i)
            product = multiply(product, involving[i]);

        Factor summed = sum_out(product, var);
        remaining.push_back(summed);

        factors = std::move(remaining);
    }

    return factors.front();
}

} // namespace stat::prob::graphical
