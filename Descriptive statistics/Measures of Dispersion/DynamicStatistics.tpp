#include "DynamicStatistics.h"

template<typename T>
DynamicStatistics<T>::DynamicStatistics(const std::vector<T>& data) : data(data) {
    if (data.empty()) {
        throw std::invalid_argument("Data vector cannot be empty.");
    }
}

template<typename T>
T DynamicStatistics<T>::mean() const {
    std::lock_guard<std::mutex> lock(mutex);
    if (!cachedMeanValid) {
        cachedMean = computeMean();
        cachedMeanValid = true;
    }
    return cachedMean;
}

template<typename T>
T DynamicStatistics<T>::variance() const {
    T m = mean();
    return computeVariance(m);
}

template<typename T>
T DynamicStatistics<T>::standardDeviation() const {
    return std::sqrt(variance());
}

template<typename T>
T DynamicStatistics<T>::range() const {
    std::lock_guard<std::mutex> lock(mutex);
    auto [minIt, maxIt] = std::minmax_element(data.begin(), data.end());
    return *maxIt - *minIt;
}

template<typename T>
T DynamicStatistics<T>::skewness() const {
    T m = mean();
    T var = variance();
    T n = data.size();

    if (var == 0) return 0;

    T skewSum = std::accumulate(data.begin(), data.end(), T(0), [m, var](T acc, T val) {
        return acc + std::pow((val - m) / std::sqrt(var), 3);
    });

    return skewSum / n;
}

template<typename T>
T DynamicStatistics<T>::kurtosis() const {
    T m = mean();
    T var = variance();
    T n = data.size();

    if (var == 0) return 0;

    T kurtSum = std::accumulate(data.begin(), data.end(), T(0), [m, var](T acc, T val) {
        return acc + std::pow((val - m) / std::sqrt(var), 4);
    });

    return kurtSum / n - 3; 
}

template<typename T>
void DynamicStatistics<T>::addDataPoint(const T& value) {
    std::lock_guard<std::mutex> lock(mutex);
    data.push_back(value);
    cachedMeanValid = false;
}

template<typename T>
void DynamicStatistics<T>::addData(const std::vector<T>& newData) {
    std::lock_guard<std::mutex> lock(mutex);
    data.insert(data.end(), newData.begin(), newData.end());
    cachedMeanValid = false;
}

template<typename T>
T DynamicStatistics<T>::computeMean() const {
    return std::accumulate(data.begin(), data.end(), T(0)) / data.size();
}

template<typename T>
T DynamicStatistics<T>::computeVariance(T m) const {
    T sum = std::accumulate(data.begin(), data.end(), T(0), [m](T acc, T val) {
        return acc + (val - m) * (val - m);
    });
    return sum / data.size();
}
