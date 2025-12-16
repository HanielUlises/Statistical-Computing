#include "slr.h"
#include <numeric>
#include <cassert>

LinearRegression::LinearRegression() : slope_(0), intercept_(0) {}

template<typename... Args>
void LinearRegression::fit(const std::vector<double>& y, const std::vector<Args>&... x) {
    const auto& x1 = combine(x...);
    assert(x1.size() == y.size() && "Input sizes must match!");
    
    size_t n = y.size();
    double x_sum = std::accumulate(x1.begin(), x1.end(), 0.0);
    double y_sum = std::accumulate(y.begin(), y.end(), 0.0);
    double xy_sum = std::inner_product(x1.begin(), x1.end(), y.begin(), 0.0);
    double x2_sum = std::inner_product(x1.begin(), x1.end(), x1.begin(), 0.0);

    slope_ = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
    intercept_ = (y_sum - slope_ * x_sum) / n;
}

template<typename... Args>
std::vector<double> LinearRegression::predict(const std::vector<Args>&... x) {
    const auto& x1 = combine(x...);
    std::vector<double> predictions;
    predictions.reserve(x1.size());
    for (const auto& xi : x1) {
        predictions.push_back(intercept_ + slope_ * xi);
    }
    return predictions;
}

template<typename... Args>
std::vector<double> LinearRegression::combine(const std::vector<Args>&... args) {
    static_assert(sizeof...(args) == 1, "Only single-variable regression is supported.");
    return (args + ...);
}

double LinearRegression::slope() const {
    return slope_;
}

double LinearRegression::intercept() const {
    return intercept_;
}

template void LinearRegression::fit(const std::vector<double>&, const std::vector<double>&);
template std::vector<double> LinearRegression::predict(const std::vector<double>&);
template std::vector<double> LinearRegression::combine(const std::vector<double>&);