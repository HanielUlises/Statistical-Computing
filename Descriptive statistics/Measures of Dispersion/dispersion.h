#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath> // Required for calculating the square root

template<typename T>
class DynamicStatistics {
public:
    explicit DynamicStatistics(const std::vector<T>& data) : data(data) {}

    T variance() const {
        T m = mean();
        T sum = std::accumulate(data.begin(), data.end(), T(0), [m](T a, T b) {
            return a + (b - m) * (b - m);
        });
        return sum / data.size();
    }

    T standardDeviation() const {
        return std::sqrt(variance());
    }

    T range() const {
        auto [minIt, maxIt] = std::minmax_element(data.begin(), data.end());
        return *maxIt - *minIt;
    }

private:
    std::vector<T> data;

    T mean() const {
        T sum = std::accumulate(data.begin(), data.end(), T(0));
        return sum / data.size();
    }
};
