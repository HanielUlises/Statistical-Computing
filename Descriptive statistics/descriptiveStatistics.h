#ifndef STATIC_STATISTICS_H
#define STATIC_STATISTICS_H

#include <array>
#include <algorithm>

template<typename T, size_t N>
class StaticStatistics {
public:
    constexpr StaticStatistics(const std::array<T, N>& data);

    constexpr T mean() const;
    constexpr T median() const;

private:
    const std::array<T, N> data;
};

#include "StaticStatistics.cpp"

#endif // STATIC_STATISTICS_H
