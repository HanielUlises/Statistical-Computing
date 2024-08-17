#include "dynamic_statistics.h"

#include <algorithm>
#include <numeric>

template<typename T>
DynamicStatistics<T>::DynamicStatistics(const std::vector<T>& _data) : data(_data) {}

template<typename T>
T DynamicStatistics<T>::mean() const {
    T sum = std::accumulate(data.begin(), data.end(), T(0));
    return sum / data.size();
}

template<typename T>
T DynamicStatistics<T>::median() const {
    std::vector<T> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());
    size_t n = sortedData.size();

    if (n % 2 == 0) {
        return (sortedData[n / 2 - 1] + sortedData[n / 2]) / 2.0;
    } else {
        return sortedData[n / 2];
    }
}
