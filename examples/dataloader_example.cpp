#include "DataLoader.hpp"
#include <fstream>
#include <iostream>
int main() {
    std::ofstream("sample_loader.csv") << "name,mark\nA,70\nB,85\n";
    auto rows = DataLoader::loadCSV("sample_loader.csv");
    for (const auto& row : rows) {
        for (const auto& value : row) std::cout << value << " ";
        std::cout << "\n";
    }
}