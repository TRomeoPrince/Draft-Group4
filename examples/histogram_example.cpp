#include "Histogram.hpp"
#include <iostream>
int main() {
    auto bins = Histogram::build({55, 60, 65, 65, 70, 75, 80, 90}, 4);
    for (const auto& bin : bins)
        std::cout << bin.lower << "-" << bin.upper << ": " << bin.count << "\n";
}