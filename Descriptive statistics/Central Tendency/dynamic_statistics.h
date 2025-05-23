#ifndef DYNAMIC_STATISTICS_H
#define DYNAMIC_STATISTICS_H

#include <vector>
#include <optional>

template<typename T>
class Central_Tendency {
public:
    Central_Tendency(const std::vector<T>& data);

    T mean() const;
    T median() const;
    std::optional<T> mode() const;
    T variance() const;
    T standard_deviation() const;
    T range() const;
    T skewness() const;
    T kurtosis() const;
    T percentile(double p) const;
    T interquartile_range() const;
    T covariance(const Central_Tendency<T>& other) const;
    T correlation_coefficient(const Central_Tendency<T>& other) const;
    std::vector<T> normalize() const;

    void add_data_point(const T& value);
    void remove_data_point(const T& value);
    void clear_data();

private:
    std::vector<T> data;

    void validate_non_empty() const;
    void validate_size(size_t minSize) const;
};


#endif // DYNAMIC_STATISTICS_H
