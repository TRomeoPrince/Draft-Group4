#include "ImageExporter.hpp"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
int main() {
    const std::string path = "test_exporter.svg";
    const std::string svg = "<svg><text>Hello</text></svg>";
    ImageExporter::saveSVG(svg, path);
    std::ifstream input(path);
    assert(input.good());
    std::string saved((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    assert(saved == svg);
    input.close();
    std::remove(path.c_str());
    std::cout << "ImageExporter tests passed.\n";
}