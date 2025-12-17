#pragma once

#include <cmath>
#include <random>
#include <stat/core/concepts.hpp>
#include <stat/core/error.hpp>

namespace stat::prob {

template <stat::concepts::Floating T>
class Normal {
    public:
        Normal(T mean, T stddev);

        T pdf(T x) const;
        T log_pdf(T x) const;

        template <stat::concepts::URBG RNG>
        T sample(RNG& rng) const;

        T mean() const noexcept;
        T stddev() const noexcept;

    private:
        T mean_;
        T stddev_;
};

} // namespace stat::prob

#include "distributions.inl"
