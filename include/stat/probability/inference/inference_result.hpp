#pragma once

#include <unordered_map>
#include <cstddef>

#include <stat/probability/graphical/assignment.hpp>

namespace stat::probability::inference {

struct InferenceResult {
    using Assignment =
        stat::prob::graphical::assignment<std::size_t>;

    std::unordered_map<Assignment, double> distribution;

    void normalize();
};

} // namespace stat::prob::inference

#include "inference_result.inl"
