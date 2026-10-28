#include "Statistics.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<double> marks{55, 60, 62, 65, 70, 75, 80, 90};
    std::cout << "Count: " << Statistics::count(marks) << "\n";
    std::cout << "Mean: " << Statistics::mean(marks) << "\n";
    std::cout << "Median: " << Statistics::median(marks) << "\n";
    std::cout << "Standard deviation: "
              << Statistics::standardDeviation(marks) << "\n";
}
