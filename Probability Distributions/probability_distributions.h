#ifndef PROBABILITY_DISTRIBUTIONS_HPP
#define PROBABILITY_DISTRIBUTIONS_HPP

#include <vector>
#include <random>
#include <cmath>

// Normal Distribution
class NormalDistribution {
public:
    NormalDistribution(double mean, double stddev);
    double pdf(double x) const; // Probability Density Function
    double cdf(double x) const; // Cumulative Distribution Function
    double random_sample() const; // Generate a random sample

private:
    double mean_;
    double stddev_;
    mutable std::mt19937 gen_;
    mutable std::normal_distribution<double> dist_;
};

// Uniform Distribution
class UniformDistribution {
public:
    UniformDistribution(double lower, double upper);
    double pdf(double x) const; // Probability Density Function
    double cdf(double x) const; // Cumulative Distribution Function
    double random_sample() const; // Generate a random sample

private:
    double lower_;
    double upper_;
    mutable std::mt19937 gen_;
    mutable std::uniform_real_distribution<double> dist_;
};

// Exponential Distribution
class ExponentialDistribution {
public:
    ExponentialDistribution(double lambda);
    double pdf(double x) const; // Probability Density Function
    double cdf(double x) const; // Cumulative Distribution Function
    double random_sample() const; // Generate a random sample

private:
    double lambda_;
    mutable std::mt19937 gen_;
    mutable std::exponential_distribution<double> dist_;
};

#endif // PROBABILITY_DISTRIBUTIONS_HPP