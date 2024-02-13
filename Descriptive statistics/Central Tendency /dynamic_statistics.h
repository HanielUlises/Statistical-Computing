#ifndef DYNAMIC_STATISTICS_H
#define DYNAMIC_STATISTICS_H

#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
class DynamicStatistics {
public:
    DynamicStatistics(const std::vector<T>& data) : data(data) {}

    T mean() const {
        T sum = std::accumulate(data.begin(), data.end(), T(0));
        return sum / data.size();
    }

    T median() const {
        std::vector<T> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        size_t n = sortedData.size();

        if (n % 2 == 0) {
            return (sortedData[n / 2 - 1] + sortedData[n / 2]) / 2.0;
        } else {
            return sortedData[n / 2];
        }
    }

private:
    std::vector<T> data;
};

#endif // DYNAMIC_STATISTICS_H
