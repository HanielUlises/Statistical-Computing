#pragma once

#include <algorithm>
#include <stat/probability/graphical/algorithms/factor_operations.hpp>

namespace stat::prob::inference {

inline ExactInference::ExactInference(std::vector<Factor> factors)
    : factors_(std::move(factors)) {}

inline std::vector<ExactInference::Factor>
ExactInference::apply_evidence(const Assignment& evidence) const {
    std::vector<Factor> updated;

    for (const auto& f : factors_)
        updated.push_back(f.condition(evidence));

    return updated;
}

inline std::vector<ExactInference::Factor>
ExactInference::eliminate_variable(
    std::vector<Factor> factors,
    std::size_t var
) const {
    std::vector<Factor> involved;
    std::vector<Factor> remaining;

    for (auto& f : factors) {
        if (f.depends_on(var))
            involved.push_back(std::move(f));
        else
            remaining.push_back(std::move(f));
    }

    if (involved.empty())
        return remaining;

    Factor product = involved.front();
    for (std::size_t i = 1; i < involved.size(); ++i)
        product = multiply(product, involved[i]);

    remaining.push_back(product.marginalize(var));
    return remaining;
}

inline InferenceResult ExactInference::query(
    const std::vector<std::size_t>& query_vars,
    const Assignment& evidence
) const {
    auto factors = apply_evidence(evidence);

    // Retrieving ALL variables
    std::vector<std::size_t> vars;
    for (const auto& f : factors)
        for (auto v : f.variables())
            vars.push_back(v);

    // Prunning non-query variables
    for (auto v : vars) {
        if (std::find(query_vars.begin(), query_vars.end(), v) == query_vars.end())
            factors = eliminate_variable(std::move(factors), v);
    }

    // Multiply remaining factors
    Factor joint = factors.front();
    for (std::size_t i = 1; i < factors.size(); ++i)
        joint = multiply(joint, factors[i]);

    InferenceResult result;
    for (const auto& [a, p] : joint.table())
        result.distribution[a] = p;

    result.normalize();
    return result;
}

} // namespace stat::prob::inference
