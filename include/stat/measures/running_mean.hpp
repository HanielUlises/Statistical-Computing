#pragma once

#include <cstddef>

namespace stat {

template<typename T>
class RunningVariance {
private:
    std::size_t n_ = 0;
    T mean_ = T{};
    T m2_ = T{};

public:

    void update(T x) {

        ++n_;

        const T delta = x - mean_;
        mean_ += delta / static_cast<T>(n_);

        const T delta2 = x - mean_;
        m2_ += delta * delta2;
    }

    [[nodiscard]]
    std::size_t count() const {
        return n_;
    }

    [[nodiscard]]
    T mean() const {
        return mean_;
    }

    [[nodiscard]]
    T variance() const {

        if(n_ < 2)
            return T{};

        return m2_ / static_cast<T>(n_ - 1);
    }

    [[nodiscard]]
    T population_variance() const {

        if(n_ == 0)
            return T{};

        return m2_ / static_cast<T>(n_);
    }

    [[nodiscard]]
    T standard_deviation() const {
        return std::sqrt(variance());
    }
};

}