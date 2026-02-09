#pragma once

#include <vector>
#include <cstddef>

#include <stat/probability/graphical/algorithms/factor.hpp>
#include <stat/probability/graphical/assignment.hpp>

#include <stat/probability/inference/inference_result.hpp>

namespace stat::prob::inference {

class ExactInference {
public:
    using Assignment =
    stat::prob::graphical::assignment<std::size_t>;

    using Factor =
        stat::prob::graphical::factor<Assignment>;

    explicit ExactInference(std::vector<Factor> factors);

    InferenceResult query(
        const std::vector<std::size_t>& query_vars,
        const Assignment& evidence = {}
    ) const;

private:
    std::vector<Factor> factors_;

    std::vector<Factor>
    apply_evidence(const Assignment& evidence) const;

    std::vector<Factor>
    eliminate_variable(
        std::vector<Factor> factors,
        std::size_t var
    ) const;
};

} // namespace stat::prob::inference

#include "exact_inference.inl"
