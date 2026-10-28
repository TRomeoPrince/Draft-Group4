#include "Annotation.hpp"
#include "CountPlot.hpp"
#include "DataLoader.hpp"
#include "DataProcessor.hpp"
#include "Histogram.hpp"
#include "ImageExporter.hpp"
#include "Renderer.hpp"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    Annotation notes;
    notes.add(20, 30, "Peak");
    assert(notes.getItems().size() == 1);
    assert(notes.getItems()[0].text == "Peak");
    notes.clear();
    assert(notes.getItems().empty());

    auto categories = CountPlot::calculate({"A", "B", "A"});
    assert(categories.at("A") == 2);
    assert(categories.at("B") == 1);

    auto bins = Histogram::build({1, 2, 3, 4}, 2);
    assert(bins.size() == 2);
    assert(bins[0].count == 2);
    assert(bins[1].count == 2);

    assert(DataProcessor::trim("  hi  ") == "hi");
    auto values = DataProcessor::toNumeric({" 1 ", "bad", "2"});
    assert(values.size() == 2);
    assert(values[0] == 1.0);

    const std::string csvPath = "dataviz_test_input.csv";
    {
        std::ofstream file(csvPath);
        assert(file.good());
        file << "name,score\nA,10\nB,20\n";
    }
    auto table = DataLoader::loadCSV(csvPath);
    assert(table.size() == 3);
    assert(table[1][1] == "10");
    std::remove(csvPath.c_str());

    std::string svg = Renderer::renderCountPlot(categories, 500, 350, "Example");
    assert(svg.find("<svg") != std::string::npos);
    assert(svg.find("Example") != std::string::npos);

    const std::string svgPath = "dataviz_test_output.svg";
    ImageExporter::saveSVG(svg, svgPath);
    {
        std::ifstream file(svgPath);
        assert(file.good());
        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
        assert(content.find("<svg") != std::string::npos);
    }
    std::remove(svgPath.c_str());

    std::cout << "Component integration tests passed.\n";
}
