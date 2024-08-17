#ifndef DYNAMIC_STATISTICS_H
#define DYNAMIC_STATISTICS_H

#include <vector>
#include <optional>

template<typename T>
class DynamicStatistics {
public:
    DynamicStatistics(const std::vector<T>& data);

    T mean() const;
    T median() const;
    std::optional<T> mode() const;
    T variance() const;
    T standardDeviation() const;
    T range() const;
    T skewness() const;
    T kurtosis() const;
    T percentile(double p) const;
    T interquartileRange() const;
    T covariance(const DynamicStatistics<T>& other) const;
    T correlationCoefficient(const DynamicStatistics<T>& other) const;
    std::vector<T> normalize() const;

    void addDataPoint(const T& value);
    void removeDataPoint(const T& value);
    void clearData();

private:
    std::vector<T> data;

    void validateNonEmpty() const;
    void validateSize(size_t minSize) const;
};

#include "dynamic_statistics.tpp"

#endif // DYNAMIC_STATISTICS_H
