#include "CountPlot.hpp"
#include <iostream>
int main() {
    auto counts = CountPlot::calculate({"CCE", "EEE", "CCE", "CIV", "CCE"});
    for (const auto& item : counts)
        std::cout << item.first << ": " << item.second << "\n";
}