#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

#define EPSILON 1e-9
#define PRINT_VECTOR(v) for(const auto& x : v) std::cout << x << " "; std::cout << std::endl;


// Removes NaN values from a vector
std::vector<double> remove_nan(const std::vector<double>& data);
// Replaces NaN values with the mean of the vector
std::vector<double> replace_nan_with_mean(const std::vector<double>& data);
// Normalizes the data to a 0-1 range
std::vector<double> normalize_min_max(const std::vector<double>& data);
// Scales the data to have mean 0 and standard deviation 1
std::vector<double> standardize(const std::vector<double>& data);

#endif // DATA_PREPROCESSING_HPP
