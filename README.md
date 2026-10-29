# Group 4 — C++ Data Visualization Library (Draft)

This is a working reference for the group's Object-Oriented Programming project.
It is designed to show how reusable C++ modules work together to produce SVG graphs.

## Project plan

The project is divided into ten modules:

- **DataLoader** reads CSV files.
- **DataProcessor** cleans the data and converts text to numbers.
- **Statistics** calculates mean, median, minimum, maximum, variance and standard deviation.
- **CountPlot** counts category frequencies.
- **Histogram** groups numerical values into bins.
- **KDEPlot** estimates a smooth density curve.
- **Axis** scales data values to drawing positions and generates ticks.
- **Annotation** stores extra text labels for the graphs.
- **Renderer** combines plot data, scales, axes, labels and annotations into SVG.
- **ImageExporter** writes the SVG image to disk.

The plotting modules reuse the Renderer and Axis logic. We do not draw a new
axis or write a new SVG exporter in every example.

## Folder structure

```text
include/       Ten public C++ headers
src/           Ten matching C++ implementation files
data/input/    sample.csv
data/output/   Default destination for generated SVG images
examples/      Three complete plot demonstrations plus one all-in-one demo
tests/         Ten individual module tests plus one integration test
CMakeLists.txt  Build setup and CTest registration
```

### Examples — finished graphs

- `histogram_example.cpp`: CSV → cleaning → binning → title, axes, annotation → SVG.
- `kdeplot_example.cpp`: CSV → cleaning → KDE density → title, axes, annotation → SVG.
- `countplot_example.cpp`: CSV → cleaning → category counts → title, axes, annotation → SVG.
- `complete_library_example.cpp`: runs the complete flow and creates all three plots.

Each example calls the library modules it needs. The Renderer handles the
drawing, including axes and scales, while ImageExporter saves the finished image.
They are demonstrations for users of the library, not unit tests.

### Tests — prove the code works

There is one individual test per module:
`test_dataloader`, `test_dataprocessor`, `test_statistics`,
`test_histogram`, `test_kdeplot`, `test_countplot`, `test_axis`,
`test_annotation`, `test_renderer`, and `test_imageexporter`.

`test_integration` loads the sample CSV, prepares the data, calculates all
three plots, renders the SVGs and checks that they can be saved correctly.

These are the two levels of testing: **individual** and **whole-library**.

## Build and run

Requirements: a C++17 compiler and CMake 3.16 or newer.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

For Linux and single-config CMake builds, open the build folder and run:

```bash
cd build
./histogram_example
./kdeplot_example
./countplot_example
./complete_library_example
```

On Windows with a multi-configuration generator, executables may be inside
`build/Debug/`. Launch them with the working directory set to `build/`,
where CMake has copied `data/input/sample.csv`.

By default, every graph example saves its SVG inside the repository's
`data/output/` directory, even when the program runs from `build/` or
`build/Debug/`. The directory is created automatically if needed.

Examples of generated filenames:

```text
data/output/
├── histogram_example.svg
├── kdeplot_example.svg
├── countplot_example.svg
├── complete_histogram.svg
├── complete_kdeplot.svg
└── complete_countplot.svg
```

`ImageExporter::saveSVG(svg, "mygraph.svg")` uses this same default folder.
If a caller explicitly supplies a directory or absolute path, that location
is honored instead. `ImageExporter::outputFile("mygraph.svg")` returns the
actual destination and is useful when displaying or opening a saved file.

The files are created on the computer that runs the program; running GitHub
Actions does not automatically commit these images into the repository.

## OOP design notes

Classes such as Axis and Annotation use private data and public methods
(encapsulation). Many other modules expose static functions for reusable tasks.
The current code does **not** demonstrate class inheritance or virtual-method
polymorphism; do not claim those concepts are implemented until they are added.

The comments in each header and source file explain the working ideas and
calculations in straightforward language, so every group member can discuss
and verify their module. AI assistance should be acknowledged accurately in
the individual or group report where applicable.

This draft is a reference copy; it does not automatically change the group's
official repository.
