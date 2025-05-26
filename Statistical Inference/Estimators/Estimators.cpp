#include "Estimators.hpp"

template <typename T>
T Estimators<T>::mse(std::vector<T> &Y, std::vector<T> &Y_hat){
     if (Y.size() != Y_hat.size()) {
        throw std::invalid_argument("The observed values and predicted values must be the same length.");
    }
    decltype(Y.size()) n = Y.size();
    T sum_of_squared_error = {};

    for(int i = 0; i < n; i++)
        sum_of_squared_error += std::pow((Y[i] - Y_hat[i]),2);

    return 1/n * sum_of_squared_error;
}