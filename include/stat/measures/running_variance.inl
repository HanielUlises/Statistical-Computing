#pragma once

#include "running_variance.hpp"

namespace stat {

template<typename T>
void RunningVariance<T>::update(T x) {

    ++n_;

    const T delta = x - mean_;
    mean_ += delta / static_cast<T>(n_);

    const T delta2 = x - mean_;

    m2_ += delta * delta2;
}

}