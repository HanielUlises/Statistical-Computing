#pragma once

#include <vector>

namespace stat::analysis::integration {

template <typename T>
struct MonteCarlo {
    std::vector<T> samples;

    template <typename F>
    T integrate(F&& f) const {
        T acc{};
        for (const auto& x : samples)
            acc += f(x);
        return acc / samples.size();
    }
};

} // namespace stat::analysis::integration
