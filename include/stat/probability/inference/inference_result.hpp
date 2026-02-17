#pragma once

#include <vector>
#include <unordered_map>
#include <cstddef>

#include <stat/probability/graphical/assignment.hpp>
#include <stat/core/hashing/assignment_hash.hpp>

namespace stat::prob::inference {

using Variable = std::size_t;

using Evidence = std::unordered_map<Variable, std::size_t>;

struct Query {
    std::vector<Variable> variables;
};

struct InferenceResult {

    using Assignment =
        stat::prob::graphical::assignment<std::size_t>;

    using Hasher =
        stat::core::hashing::assignment_hash<std::size_t>;

    std::unordered_map<
        Assignment,
        double,
        Hasher
    > distribution;

    void normalize();
};

class InferenceEngine {
public:
    virtual ~InferenceEngine() = default;

    virtual InferenceResult infer(
        const Query& query,
        const Evidence& evidence
    ) const = 0;
};

} // namespace stat::prob::inference

#include "inference_result.inl"