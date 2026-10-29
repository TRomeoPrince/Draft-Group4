#include "Annotation.hpp"
#include "Axis.hpp"
#include "CountPlot.hpp"
#include "DataLoader.hpp"
#include "DataProcessor.hpp"
#include "Histogram.hpp"
#include "ImageExporter.hpp"
#include "KDEPlot.hpp"
#include "Renderer.hpp"
#include "Statistics.hpp"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// This test covers the whole flow instead of testing every small function again.
void checkSavedGraph(const std::string& svg, const std::string& filename,
                     const std::string& expectedElement,
                     const std::string& yLabel) {
    assert(svg.find("<svg") != std::string::npos);
    assert(svg.find(expectedElement) != std::string::npos);
    assert(svg.find(yLabel) != std::string::npos);

    ImageExporter::saveSVG(svg, filename);
    // The exporter routes a plain filename into data/output.
    const std::string savedPath = ImageExporter::outputFile(filename);
    std::ifstream file(savedPath);
    assert(file.good());
    std::string saved((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
    assert(saved == svg);
    file.close();
    std::remove(savedPath.c_str());
}

int main() {
    // Step 1: Load the same sample CSV used by our examples.
    auto rows = DataProcessor::cleanRows(
        DataLoader::loadCSV("data/input/sample.csv"));
    auto marks = DataProcessor::toNumeric(
        DataProcessor::getColumn(rows, 2));
    auto programmes = DataProcessor::getColumn(rows, 1);

    assert(marks.size() == 8);
    assert(programmes.size() == marks.size());
    assert(Statistics::mean(marks) > 0.0);

    // Step 2: The Axis maps our calculated values into drawing positions.
    Axis axis(Statistics::minimum(marks), Statistics::maximum(marks), 0, 500);
    assert(axis.scale(Statistics::minimum(marks)) == 0.0);
    assert(axis.ticks(5).size() == 5);

    // Step 3: Prepare the three plot types and a note for the graphs.
    auto counts = CountPlot::calculate(programmes);
    auto bins = Histogram::build(marks, 5);
    auto points = KDEPlot::estimate(marks, 100);
    assert(!counts.empty() && !bins.empty() && points.size() == 100);

    Annotation notes;
    notes.add(500, 80, "Mean: " + std::to_string(Statistics::mean(marks)));

    // Step 4: Render and verify the complete SVGs and exported files.
    auto countSvg = Renderer::renderCountPlot(
        counts, 800, 500, "Programme Count", notes);
    auto histogramSvg = Renderer::renderHistogram(
        bins, 800, 500, "Marks Histogram", notes);
    auto kdeSvg = Renderer::renderKDE(
        points, 800, 500, "Marks Density", notes);

    checkSavedGraph(countSvg, "integration_count.svg", "<rect", "Frequency");
    checkSavedGraph(histogramSvg, "integration_histogram.svg", "<rect", "Frequency");
    checkSavedGraph(kdeSvg, "integration_kde.svg", "<polyline", "Density");

    assert(countSvg.find("Mean:") != std::string::npos);
    assert(histogramSvg.find("Marks") != std::string::npos);
    assert(kdeSvg.find("Marks") != std::string::npos);

    std::cout << "Complete library integration test passed.\n";
}
