#include "descriptiveStatistics.h"

template<typename T, size_t N>
constexpr StaticStatistics<T, N>::StaticStatistics(const std::array<T, N>& data) : data(data) {}

template<typename T, size_t N>
constexpr T StaticStatistics<T, N>::mean() const {
    T sum = 0;
    for (const auto& val : data) {
        sum += val;
    }
    return sum / N;
}

template<typename T, size_t N>
constexpr T StaticStatistics<T, N>::median() const {
    std::array<T, N> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    if (N % 2 == 0) {
        return (sortedData[N / 2 - 1] + sortedData[N / 2]) / 2;
    } else {
        return sortedData[N / 2];
    }
}
