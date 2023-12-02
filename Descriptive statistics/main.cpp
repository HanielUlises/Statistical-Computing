#include <iostream>
#include "descriptiveStatistics.h"

int main() {
    constexpr std::array<double, 5> data = {1, 2, 3, 4, 5};
    constexpr StaticStatistics<double, data.size()> stats(data);

    std::cout << "Mean: " << stats.mean() << std::endl;
    std::cout << "Median: " << stats.median() << std::endl;

    return 0;
}
