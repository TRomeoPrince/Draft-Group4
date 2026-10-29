#include "Annotation.hpp"
#include "DataLoader.hpp"
#include "DataProcessor.hpp"
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
        // KDE uses the same cleaned marks as the histogram, but draws a smooth curve.
        auto rows = DataProcessor::cleanRows(DataLoader::loadCSV("data/input/sample.csv"));
        auto marks = DataProcessor::toNumeric(DataProcessor::getColumn(rows, 2));
        auto points = KDEPlot::estimate(marks, 120);

        Annotation notes;
        notes.add(530, 80, "Mean mark: " + std::to_string(Statistics::mean(marks)));

        auto svg = Renderer::renderKDE(
            points, 800, 500, "Student Marks KDE Plot", notes);
        ImageExporter::saveSVG(svg, "kdeplot_example.svg");

        std::cout << "Created kdeplot_example.svg using "
                  << points.size() << " density points.\n";
    } catch (const std::exception& error) {
        std::cerr << "KDE example failed: " << error.what() << "\n";
        return 1;
    }
}
