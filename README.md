# Draft Group 4 — C++ Data Visualization Library

This repository is a complete reference implementation for Group 4's C++ Object-Oriented Programming project.

The library demonstrates the full flow:

```
CSV / raw data
      |
      v
DataLoader
      |
      v
DataProcessor
      |
      v
Statistics
      |
      +----------------+----------------+
      |                |                |
      v                v                v
  CountPlot        Histogram         KDEPlot
      |                |                |
      +----------------+----------------+
                       |
                       v
                 Axis scaling
                       |
                       v
                  Annotation
                       |
                       v
                    Renderer
                       |
                       v
                 ImageExporter
                       |
                       v
                   SVG image
```

## Project structure

```
Draft-Group4/
├── include/
│   ├── DataLoader.hpp
│   ├── DataProcessor.hpp
│   ├── Statistics.hpp
│   ├── CountPlot.hpp
│   ├── Histogram.hpp
│   ├── KDEPlot.hpp
│   ├── Axis.hpp
│   ├── Annotation.hpp
│   ├── Renderer.hpp
│   └── ImageExporter.hpp
├── src/
│   ├── DataLoader.cpp
│   ├── DataProcessor.cpp
│   ├── Statistics.cpp
│   ├── CountPlot.cpp
│   ├── Histogram.cpp
│   ├── KDEPlot.cpp
│   ├── Axis.cpp
│   ├── Annotation.cpp
│   ├── Renderer.cpp
│   └── ImageExporter.cpp
├── tests/
│   └── test_library.cpp
├── examples/
│   └── example.cpp
├── data/
│   ├── input/
│   │   └── sample.csv
│   └── output/
│       └── README.md
├── CMakeLists.txt
└── .gitignore
```

## What each module does

- **DataLoader** — reads CSV data into C++.
- **DataProcessor** — trims, cleans, extracts columns and converts text values to numbers.
- **Statistics** — calculates count, mean, minimum, maximum, median, variance and standard deviation.
- **CountPlot** — counts how many times each category appears.
- **Histogram** — groups numerical values into bins and counts values in each bin.
- **KDEPlot** — estimates a smooth probability-density curve.
- **Axis** — maps real data values to positions on a drawing area and can generate tick values.
- **Annotation** — stores labels or notes to place on a graph.
- **Renderer** — turns calculated plot data into SVG graphics.
- **ImageExporter** — saves the rendered SVG text to an image file.

## Shared-code idea

The files are separate, but they are connected.

For example:

- Renderer uses Axis for coordinate scaling.
- Renderer consumes output from CountPlot, Histogram and KDEPlot.
- Histogram and KDEPlot use numerical data prepared by DataProcessor.
- ImageExporter saves what Renderer produces.

This avoids rewriting the same logic in several modules.

## Build

Requirements:

- C++17-compatible compiler
- CMake 3.16 or newer

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

## Run the example

```bash
./build/dataviz_example
```

On Windows with some CMake generators, the executable may be inside:

```
build/Debug/dataviz_example.exe
```

The example writes SVG plot files into the current working directory.

## Run tests

```bash
ctest --test-dir build --output-on-failure
```

## Notes

This is deliberately written using only the C++ standard library. SVG is used for image output so the project can demonstrate rendering and image export without requiring a large external graphics dependency.

Weekly reports are intentionally not included in this draft reference repository.
