#include "measures.hpp"

namespace stat::prob {

template <stat::concepts::Floating T>
T mean(const std::vector<T>& data) {
    if (data.empty())
        throw stat::domain_error("mean: data is empty");
    T sum = std::accumulate(data.begin(), data.end(), T(0));
    return sum / static_cast<T>(data.size());
}

template <stat::concepts::Floating T>
T variance(const std::vector<T>& data, bool sample) {
    if (data.size() < 2)
        throw stat::domain_error("variance: need at least 2 data points");
    T m = mean(data);
    T sum_sq = std::accumulate(data.begin(), data.end(), T(0),
                               [m](T acc, T x) { return acc + (x - m) * (x - m); });
    return sum_sq / static_cast<T>(sample ? data.size() - 1 : data.size());
}

template <stat::concepts::Floating T>
T standard_deviation(const std::vector<T>& data, bool sample) {
    return std::sqrt(variance(data, sample));
}

}