#ifndef IMAGEEXPORTER_HPP
#define IMAGEEXPORTER_HPP

#include <string>

// The Renderer prepares SVG text and this module saves it.
// I keep file writing separate from the drawing calculations.
class ImageExporter {
public:
    // The rest of the library will use this public interface.
    static void saveSVG(const std::string& svg, const std::string& filePath);
};

#endif
