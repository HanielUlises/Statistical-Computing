#include "DynamicStatistics.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<double> data = {1.0, 2.0, 4.0, 5.0, 7.0};
    DynamicStatistics<double> stats(data);

    std::cout << "Variance: " << stats.variance() << std::endl;
    std::cout << "Standard Deviation: " << stats.standardDeviation() << std::endl;
    std::cout << "Range: " << stats.range() << std::endl;

    return 0;
}
