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


## Individual module examples and tests

The original `examples/example.cpp` demonstrates the complete library. The following
standalone examples make it easier to learn and present individual modules:

- `examples/axis_example.cpp`: numerical axis scaling and ticks.
- `examples/statistics_example.cpp`: descriptive statistics.
- `examples/kdeplot_example.cpp`: KDE estimation, SVG rendering, and export to `kde_example.svg`.

After building, run the desired executable from the build folder, or use its
generator-specific path (for example `build/Debug/kdeplot_example.exe` on Windows).

CTest now runs five separately reported test executables:

| Test | What it covers |
| --- | --- |
| `dataviz_tests` | Existing cross-module behavior and rendering checks |
| `test_kdeplot` | KDE point count, finite nonnegative densities, ordering, bandwidth, invalid inputs |
| `test_axis` | Scaling, tick spacing, range updates, and invalid inputs |
| `test_statistics` | Descriptive calculations, sample values, and empty input |
| `test_components` | Annotation, count plot, histogram, data processing/loading, renderer, SVG export |

Run everything with:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

The `.github/workflows/ci.yml` workflow also builds and runs the test suite
on GitHub for pushes and pull requests.

**Note:** These files demonstrate the current implementations; the standalone
modules still require further integration and additional edge-case tests before
this reference library should be considered production-ready.
