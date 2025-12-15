#include "likelihood.hpp"

namespace stat::prob {

template <stat::concepts::Distribution Dist, stat::concepts::Floating T>
T likelihood(const Dist& dist, const std::vector<T>& data) {
    T result = T(1);
    for (auto x : data) {
        result *= dist.pdf(x);
    }
    return result;
}

template <stat::concepts::Distribution Dist, stat::concepts::Floating T>
T log_likelihood(const Dist& dist, const std::vector<T>& data) {
    T sum = T(0);
    for (auto x : data) {
        sum += dist.log_pdf(x);
    }
    return sum;
}

}