#ifndef DYNAMIC_STATISTICS_H
#define DYNAMIC_STATISTICS_H

#include <vector>

template<typename T>
class DynamicStatistics {
public:
    DynamicStatistics(const std::vector<T>& data);

    T mean() const;
    T median() const;

private:
    std::vector<T> data;
};

#include "dynamic_statistics.tpp"

#endif // DYNAMIC_STATISTICS_H
