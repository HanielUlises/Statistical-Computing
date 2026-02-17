#pragma once

#include <vector>
#include <unordered_map>
#include <concepts>
#include <cstddef>

#include <stat/probability/graphical/graph.hpp>
#include <stat/probability/graphical/assignment.hpp>
#include <stat/core/hashing/assignment_hash.hpp>

namespace stat::probability::inference {

using Variable = std::size_t;

// Observed evidence:
//   variable -> value
using Evidence = std::unordered_map<Variable, std::size_t>;

// Represents a query over one or more variables
struct Query {
    std::vector<Variable> variables;
};

// Result of an inference query
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

// Base class for inference engines
class InferenceEngine {
public:
    virtual ~InferenceEngine() = default;

    // Perform inference:
    //   P(Query | Evidence)
    virtual InferenceResult infer(
        const Query& query,
        const Evidence& evidence
    ) const = 0;
};

} // namespace stat::probability::inference
