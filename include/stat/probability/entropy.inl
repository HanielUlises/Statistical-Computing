#include "entropy.hpp"

namespace stat::prob {


template <stat::concepts::Distribution Dist, stat::concepts::Floating T>
T entropy(const Dist& dist, const std::vector<T>& samples) {
    T sum = T(0);
    for (auto x : samples) {
        sum -= dist.log_pdf(x);
    }
    return sum / static_cast<T>(samples.size());
}

template <stat::concepts::Distribution Dist1, stat::concepts::Distribution Dist2, stat::concepts::Floating T>
T kl_divergence(const Dist1& p, const Dist2& q, const std::vector<T>& samples) {
    T sum = T(0);
    for (auto x : samples) {
        sum += p.log_pdf(x) - q.log_pdf(x);
    }
    return sum / static_cast<T>(samples.size());
}

}