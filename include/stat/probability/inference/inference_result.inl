#pragma once

#include "inference_result.hpp"

#include <numeric>
#include <stdexcept>

namespace stat::probability::inference {

inline void InferenceResult::normalize()
{
    if (distribution.empty()) {
        throw std::logic_error(
            "InferenceResult::normalize(): empty distribution"
        );
    }

    const double total =
        std::accumulate(
            distribution.begin(),
            distribution.end(),
            0.0,
            [](double acc, const auto& kv) {
                return acc + kv.second;
            }
        );

    if (total <= 0.0) {
        throw std::logic_error(
            "InferenceResult::normalize(): total probability mass is zero"
        );
    }

    for (auto& [assignment, prob] : distribution) {
        prob /= total;
    }
}

} // namespace stat::probability::inference
