#include "probability_distributions.h"

NormalDistribution::NormalDistribution(double mean, double stddev) 
    : mean_(mean), stddev_(stddev), dist_(mean_, stddev_) {}

double NormalDistribution::pdf(double x) const {
    return (1.0 / (stddev_ * std::sqrt(2.0 * M_PI))) * std::exp(-0.5 * std::pow((x - mean_) / stddev_, 2));
}

double NormalDistribution::cdf(double x) const {
    return 0.5 * (1 + std::erf((x - mean_) / (stddev_ * std::sqrt(2))));
}

double NormalDistribution::random_sample() const {
    return dist_(gen_);
}

UniformDistribution::UniformDistribution(double lower, double upper) 
    : lower_(lower), upper_(upper), dist_(lower_, upper_) {}

double UniformDistribution::pdf(double x) const {
    return (x >= lower_ && x <= upper_) ? (1.0 / (upper_ - lower_)) : 0.0;
}

double UniformDistribution::cdf(double x) const {
    if (x < lower_) return 0.0;
    if (x > upper_) return 1.0;
    return (x - lower_) / (upper_ - lower_);
}

double UniformDistribution::random_sample() const {
    return dist_(gen_);
}

ExponentialDistribution::ExponentialDistribution(double lambda) 
    : lambda_(lambda), dist_(lambda) {}

double ExponentialDistribution::pdf(double x) const {
    return (x >= 0) ? lambda_ * std::exp(-lambda_ * x) : 0.0;
}

double ExponentialDistribution::cdf(double x) const {
    return (x < 0) ? 0.0 : 1.0 - std::exp(-lambda_ * x);
}

double ExponentialDistribution::random_sample() const {
    return dist_(gen_);
}
