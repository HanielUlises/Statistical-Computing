#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

class LinearRegression {
public:
    LinearRegression();
    
    // Fit the linear model
    template<typename... Args>
    void fit(const std::vector<double>& y, const std::vector<Args>&... x);
    
    // Predict values
    template<typename... Args>
    std::vector<double> predict(const std::vector<Args>&... x);
    
    // Get model parameters
    double slope() const;
    double intercept() const;

private:
    double slope_;
    double intercept_;
    
    // Combine input features (supports single-variable regression)
    template<typename... Args>
    std::vector<double> combine(const std::vector<Args>&... args);
};

#endif // LINEAR_REGRESSION_H