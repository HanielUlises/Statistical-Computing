#ifndef ESTIMATORS_HPP
#define ESTIMATORS_HPP

#include "../../Descriptive statistics/Central Tendency"

template <typename T>
class Estimator{
    public:
        // Mean squared error
        // Y: observed values
        // Ŷ: predicted values
        T MSE(std::vector<T> &Y, std::vector<T> &Y_hat);
};

#endif // ESTIMATORS_HPP