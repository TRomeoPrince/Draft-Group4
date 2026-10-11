cmake_minimum_required(VERSION 3.16)

project(DataVisualizationLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dataviz
    src/DataLoader.cpp
    src/DataProcessor.cpp
    src/Statistics.cpp
    src/CountPlot.cpp
    src/Histogram.cpp
    src/KDEPlot.cpp
    src/Axis.cpp
    src/Annotation.cpp
    src/Renderer.cpp
    src/ImageExporter.cpp
)

target_include_directories(dataviz PUBLIC include)

add_executable(dataviz_example examples/example.cpp)
target_link_libraries(dataviz_example PRIVATE dataviz)

enable_testing()

add_executable(dataviz_tests tests/test_library.cpp)
target_link_libraries(dataviz_tests PRIVATE dataviz)

add_test(NAME dataviz_tests COMMAND dataviz_tests)
