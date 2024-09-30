#include "preprocessing.h"
#include <limits>

// Helper function to check if a value is NaN (just for handling missing values)
bool is_nan(double value) {
    return std::isnan(value) || value == std::numeric_limits<double>::infinity();
}

// Removes NaN values from a vector
std::vector<double> remove_nan(const std::vector<double>& data) {
    std::vector<double> clean_data;
    std::copy_if(data.begin(), data.end(), std::back_inserter(clean_data), [](double x) {
        return !is_nan(x);
    });
    return clean_data;
}

// Replaces NaN values with the mean of the vector
std::vector<double> replace_nan_with_mean(const std::vector<double>& data) {
    std::vector<double> clean_data = data;
    std::vector<double> non_nan_data = remove_nan(data);

    double mean = std::accumulate(non_nan_data.begin(), non_nan_data.end(), 0.0) / non_nan_data.size();

    // Replace NaNs
    std::transform(clean_data.begin(), clean_data.end(), clean_data.begin(), [mean](double x) {
        return is_nan(x) ? mean : x;
    });

    return clean_data;
}

// Normalizes the data to a 0-1 range
std::vector<double> normalize_min_max(const std::vector<double>& data) {
    std::vector<double> normalized_data = data;

    // Minimum and maximum values of data
    auto [min_it, max_it] = std::minmax_element(data.begin(), data.end());
    double min_value = *min_it;
    double max_value = *max_it;

    // Normalization
    std::transform(data.begin(), data.end(), normalized_data.begin(), [min_value, max_value](double x) {
        return (x - min_value) / (max_value - min_value + EPSILON);
    });

    return normalized_data;
}

// Scales the data to have mean 0 and standard deviation 1
std::vector<double> standardize(const std::vector<double>& data) {
    std::vector<double> standardized_data = data;
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double variance = std::accumulate(data.begin(), data.end(), 0.0, [mean](double accum, double x) {
        return accum + (x - mean) * (x - mean);
    }) / data.size();
    double std_dev = std::sqrt(variance);

    // Standardization
    std::transform(data.begin(), data.end(), standardized_data.begin(), [mean, std_dev](double x) {
        return (x - mean) / (std_dev + EPSILON);
    });

    return standardized_data;
}
