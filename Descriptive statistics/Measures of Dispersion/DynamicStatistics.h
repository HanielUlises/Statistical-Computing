#ifndef DYNAMIC_STATISTICS_H
#define DYNAMIC_STATISTICS_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <mutex>

template<typename T>
class DynamicStatistics {
public:
    explicit DynamicStatistics(const std::vector<T>& data);
    
    // Statistical methods
    T mean() const;
    T variance() const;
    T standardDeviation() const;
    T range() const;
    T skewness() const;
    T kurtosis() const;

    // Data manipulation
    void addDataPoint(const T& value);
    void addData(const std::vector<T>& newData);

private:
    mutable std::mutex mutex;
    std::vector<T> data;

    // Helper methods
    T computeMean() const;
    T computeVariance(T m) const;

    mutable bool cachedMeanValid = false;
    mutable T cachedMean = T(0);
};

#include "DynamicStatistics.tpp"
#endif // DYNAMIC_STATISTICS_H
