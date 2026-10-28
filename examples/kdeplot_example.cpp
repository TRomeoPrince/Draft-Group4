#include "Annotation.hpp"
#include "ImageExporter.hpp"
#include "KDEPlot.hpp"
#include "Renderer.hpp"

#include <exception>
#include <iostream>
#include <vector>

int main() {
    try {
        std::vector<double> marks{55, 60, 62, 65, 67, 70, 70, 72, 75, 80, 85, 90};
        auto points = KDEPlot::estimate(marks, 100);

        Annotation note;
        note.add(580, 80, "Group 4 KDE Example");

        auto svg = Renderer::renderKDE(points, 800, 500, "Marks KDE Plot", note);
        ImageExporter::saveSVG(svg, "kde_example.svg");

        std::cout << "Generated " << points.size()
                  << " KDE points and saved kde_example.svg\n";
    } catch (const std::exception& error) {
        std::cerr << "KDE example failed: " << error.what() << "\n";
        return 1;
    }
}
