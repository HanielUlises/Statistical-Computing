#include "CSVUtilities.h"
#include "dynamic_statistics.h"
#include <iostream>

int main() {
    try {
        std::string filePath = "path/to/your/data.csv";
        auto data = CSVUtilities::readColumn(filePath, 0);

        DynamicStatistics<double> stats(data);
        std::cout << "Mean: " << stats.mean() << std::endl;
        std::cout << "Median: " << stats.median() << std::endl;

        std::string outputFilePath = "path/to/your/output.csv";
        CSVUtilities::writeColumn(outputFilePath, data, "Processed Data");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
