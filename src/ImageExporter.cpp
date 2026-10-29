#include "ImageExporter.hpp"

#include <fstream>
#include <stdexcept>

// Writing the SVG to a file is the final step after rendering.
void ImageExporter::saveSVG(
    const std::string& svg,
    const std::string& filePath
) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not create output file: " + filePath);
    }

    file << svg;

    if (!file.good()) {
        throw std::runtime_error("Failed while writing output file: " + filePath);
    }
}
