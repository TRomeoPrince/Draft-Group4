#include "DataProcessor.hpp"
#include <iostream>
int main() {
    DataProcessor::Table raw{{"name", "mark"}, {" A ", " 70 "}, {"B", "85"}, {" ", " "}};
    auto cleaned = DataProcessor::cleanRows(raw);
    auto marks = DataProcessor::toNumeric(DataProcessor::getColumn(cleaned, 1));
    for (double mark : marks) std::cout << "Mark: " << mark << "\n";
}