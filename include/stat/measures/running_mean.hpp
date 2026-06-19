#pragma once

#include <cstddef>

namespace stat {

template<typename T>
class RunningMean {
private:
    std::size_t n_ = 0;
    T mean_ = T{};

public:
    void update(T x) {
        ++n_;
        mean_ += (x - mean_) / static_cast<T>(n_);
    }

    [[nodiscard]]
    T value() const {
        return mean_;
    }

    [[nodiscard]]
    std::size_t count() const {
        return n_;
    }
};

}