#pragma once

#include <stat/core/concepts.hpp>

namespace stat::prob {

template <typename Prior,
          typename Likelihood,
          typename X,
          typename Y>
class BayesianPosterior {
public:
    BayesianPosterior(const Prior& prior,
                      const Likelihood& likelihood)
        : prior_(prior), likelihood_(likelihood) {}

    auto pdf(const X& x, const Y& y) const {
        return likelihood_.pdf(y, x) * prior_.pdf(x);
    }

private:
    const Prior& prior_;
    const Likelihood& likelihood_;
};

} // namespace stat::prob
