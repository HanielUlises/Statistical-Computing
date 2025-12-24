#pragma once

#include <stat/probability/conditional/evidence.hpp>
#include <stat/core/concepts.hpp>

namespace stat::prob {

template <
    typename Posterior,
    typename Integrator,
    typename X,
    typename Y
>
class PosteriorMeasure {
public:
    using value_type = decltype(
        std::declval<Posterior>().pdf(
            std::declval<X>(),
            std::declval<Y>()
        )
    );

    PosteriorMeasure(const Posterior& posterior,
                     const Integrator& integrator,
                     const Y& y)
        : posterior_(posterior),
          integrator_(integrator),
          y_(y),
          evidence_(evidence<Posterior, Integrator, X, Y>(
              posterior_, integrator_, y_
          ))
    {}

    /// Proper posterior density p(x | y)
    value_type pdf(const X& x) const {
        return posterior_.pdf(x, y_) / evidence_;
    }

    /// Access normalization constant
    value_type normalization() const {
        return evidence_;
    }

private:
    const Posterior&  posterior_;
    const Integrator& integrator_;
    Y                 y_;
    value_type        evidence_;
};

} // namespace stat::prob
