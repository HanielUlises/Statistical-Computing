#pragma once

#include <cmath>
#include <random>
#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

template <stat::concepts::Floating T>
class Poisson {
    public:
        explicit Poisson(T lambda);

        T pmf(unsigned int k) const;
        T log_pmf(unsigned int k) const;

        template <stat::concepts::URBG RNG>
        unsigned int sample(RNG& rng) const;

        T lambda() const noexcept;

    private:
        T lambda_;
};

} // namespace stat::prob

#include "distributions.inl"
