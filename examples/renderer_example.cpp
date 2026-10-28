#include "Renderer.hpp"
#include "CountPlot.hpp"
#include "ImageExporter.hpp"
#include <iostream>
int main() {
    auto counts = CountPlot::calculate({"CCE", "EEE", "CCE"});
    auto svg = Renderer::renderCountPlot(counts, 800, 500, "Programme Counts");
    ImageExporter::saveSVG(svg, "renderer_example.svg");
    std::cout << "Saved renderer_example.svg\n";
}