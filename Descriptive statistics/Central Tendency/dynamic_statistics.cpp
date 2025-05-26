#include "dynamic_statistics.h"

#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <stdexcept>

template<typename T>
Central_Tendency<T>::Central_Tendency(const std::vector<T>& _data) : data(_data) {}

template<typename T>
void Central_Tendency<T>::validateNonEmpty() const {
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty.");
    }
}

template<typename T>
void Central_Tendency<T>::validateSize(size_t minSize) const {
    if (data.size() < minSize) {
        throw std::runtime_error("Dataset must contain at least " + std::to_string(minSize) + " elements.");
    }
}

template<typename T>
T Central_Tendency<T>::mean() const {
    validateNonEmpty();
    T sum = std::accumulate(data.begin(), data.end(), T(0));
    return sum / data.size();
}

template<typename T>
T Central_Tendency<T>::median() const {
    validateNonEmpty();
    std::vector<T> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());
    size_t n = sortedData.size();

    if (n % 2 == 0) {
        return (sortedData[n / 2 - 1] + sortedData[n / 2]) / T(2);
    } else {
        return sortedData[n / 2];
    }
}

template<typename T>
std::optional<T> Central_Tendency<T>::mode() const {
    validateNonEmpty();

    std::map<T, int> frequencyMap;
    for (const T& value : data) {
        frequencyMap[value]++;
    }

    int maxFrequency = 0;
    std::optional<T> modeValue;
    for (const auto& [key, frequency] : frequencyMap) {
        if (frequency > maxFrequency) {
            maxFrequency = frequency;
            modeValue = key;
        }
    }

    if (maxFrequency == 1) {
        return std::nullopt; // No mode
    }

    return modeValue;
}

template<typename T>
T Central_Tendency<T>::variance() const {
    validateSize(2);

    T meanValue = mean();
    T sumSquaredDiff = std::accumulate(data.begin(), data.end(), T(0), [meanValue](T acc, T value) {
        T diff = value - meanValue;
        return acc + diff * diff;
    });

    return sumSquaredDiff / (data.size() - 1);
}

template<typename T>
T Central_Tendency<T>::standard_deviation() const {
    return std::sqrt(variance());
}

template<typename T>
T Central_Tendency<T>::range() const {
    validateNonEmpty();

    auto [minIt, maxIt] = std::minmax_element(data.begin(), data.end());
    return *maxIt - *minIt;
}

template<typename T>
T Central_Tendency<T>::skewness() const {
    validateSize(3);

    T meanValue = mean();
    T stdDev = standard_deviation();

    T skewSum = std::accumulate(data.begin(), data.end(), T(0), [meanValue, stdDev](T acc, T value) {
        return acc + std::pow((value - meanValue) / stdDev, 3);
    });

    return (skewSum * data.size()) / ((data.size() - 1) * (data.size() - 2));
}

template<typename T>
T Central_Tendency<T>::kurtosis() const {
    validateSize(4);

    T meanValue = mean();
    T stdDev = standardDeviation();

    T kurtSum = std::accumulate(data.begin(), data.end(), T(0), [meanValue, stdDev](T acc, T value) {
        return acc + std::pow((value - meanValue) / stdDev, 4);
    });

    return (kurtSum * data.size() * (data.size() + 1)) /
           ((data.size() - 1) * (data.size() - 2) * (data.size() - 3)) - (3 * (data.size() - 1) * (data.size() - 1)) /
           ((data.size() - 2) * (data.size() - 3));
}

template<typename T>
T Central_Tendency<T>::percentile(double p) const {
    validateNonEmpty();

    if (p < 0.0 || p > 100.0) {
        throw std::out_of_range("Percentile must be between 0 and 100.");
    }

    std::vector<T> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    size_t index = static_cast<size_t>(std::ceil(p / 100.0 * sortedData.size())) - 1;
    return sortedData[index];
}

template<typename T>
T Central_Tendency<T>::interquartile_range() const {
    return percentile(75) - percentile(25);
}

template<typename T>
T Central_Tendency<T>::covariance(const Central_Tendency<T>& other) const {
    validateSize(2);

    if (data.size() != other.data.size()) {
        throw std::runtime_error("Datasets must have the same size for covariance calculation.");
    }

    T mean1 = mean();
    T mean2 = other.mean();

    T covarSum = T(0);
    for (size_t i = 0; i < data.size(); ++i) {
        covarSum += (data[i] - mean1) * (other.data[i] - mean2);
    }

    return covarSum / (data.size() - 1);
}

template<typename T>
T Central_Tendency<T>::correlation_coefficient(const Central_Tendency<T>& other) const {
    T cov = covariance(other);
    T stdDev1 = standardDeviation();
    T stdDev2 = other.standardDeviation();

    return cov / (stdDev1 * stdDev2);
}

template<typename T>
std::vector<T> Central_Tendency<T>::normalize() const {
    validateNonEmpty();

    T meanValue = mean();
    T stdDev = standardDeviation();

    std::vector<T> normalizedData;
    normalizedData.reserve(data.size());

    std::transform(data.begin(), data.end(), std::back_inserter(normalizedData), [meanValue, stdDev](T value) {
        return (value - meanValue) / stdDev;
    });

    return normalizedData;
}

template<typename T>
void Central_Tendency<T>::add_data_point(const T& value) {
    data.push_back(value);
}

template<typename T>
void Central_Tendency<T>::remove_data_point(const T& value) {
    auto it = std::find(data.begin(), data.end(), value);
    if (it != data.end()) {
        data.erase(it);
    }
}

template<typename T>
void Central_Tendency<T>::clear_data() {
    data.clear();
}
