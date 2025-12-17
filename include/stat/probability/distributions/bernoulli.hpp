#pragma once

#include <random>
#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

template <stat::concepts::Floating T>
class Bernoulli {
    public:
        explicit Bernoulli(T p);

        T pmf(bool x) const;
        T log_pmf(bool x) const;

        template <stat::concepts::URBG RNG>
        bool sample(RNG& rng) const;

        T probability() const noexcept;

    private:
        T p_;
};

} // namespace stat::prob

#include "distributions.inl"
