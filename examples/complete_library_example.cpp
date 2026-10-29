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

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main() {
    try {
        // This final example brings all our modules together using one CSV file.
        auto rows = DataProcessor::cleanRows(DataLoader::loadCSV("data/input/sample.csv"));
        auto marks = DataProcessor::toNumeric(DataProcessor::getColumn(rows, 2));
        auto programmes = DataProcessor::getColumn(rows, 1);

        // Statistics helps us understand the marks before drawing them.
        double average = Statistics::mean(marks);
        Axis marksAxis(Statistics::minimum(marks), Statistics::maximum(marks), 0, 500);
        std::cout << "Mean: " << average
                  << ", mapped position: " << marksAxis.scale(average) << "\n";

        auto counts = CountPlot::calculate(programmes);
        auto bins = Histogram::build(marks, 5);
        auto density = KDEPlot::estimate(marks, 120);

        // All three charts use the same Renderer, Axis logic and SVG exporter.
        Annotation notes;
        notes.add(540, 80, "Mean mark: " + std::to_string(average));

        ImageExporter::saveSVG(
            Renderer::renderCountPlot(counts, 800, 500, "Student Programmes"),
            "complete_countplot.svg");
        ImageExporter::saveSVG(
            Renderer::renderHistogram(bins, 800, 500, "Student Marks", notes),
            "complete_histogram.svg");
        ImageExporter::saveSVG(
            Renderer::renderKDE(density, 800, 500, "Student Marks Density", notes),
            "complete_kdeplot.svg");

        std::cout << "Created three complete SVG graphs.\n";
    } catch (const std::exception& error) {
        std::cerr << "Full library example failed: " << error.what() << "\n";
        return 1;
    }
}
