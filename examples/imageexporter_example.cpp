#include "ImageExporter.hpp"
#include <iostream>
int main() {
    const std::string svg = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"100\"><rect width=\"200\" height=\"100\" fill=\"skyblue\"/></svg>";
    ImageExporter::saveSVG(svg, "exporter_example.svg");
    std::cout << "Saved exporter_example.svg\n";
}