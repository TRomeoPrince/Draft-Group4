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

# Full-library demo plus standalone examples for individual modules.
add_executable(dataviz_example examples/example.cpp)
target_link_libraries(dataviz_example PRIVATE dataviz)

add_executable(kdeplot_example examples/kdeplot_example.cpp)
target_link_libraries(kdeplot_example PRIVATE dataviz)

add_executable(axis_example examples/axis_example.cpp)
target_link_libraries(axis_example PRIVATE dataviz)

add_executable(statistics_example examples/statistics_example.cpp)
target_link_libraries(statistics_example PRIVATE dataviz)

enable_testing()

# Each test is independently runnable. Use Debug builds to keep asserts enabled.
function(add_dataviz_test target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE dataviz)
    if(MSVC)
        target_compile_options(${target} PRIVATE /UNDEBUG)
    else()
        target_compile_options(${target} PRIVATE -UNDEBUG)
    endif()
    add_test(NAME ${target} COMMAND ${target})
endfunction()

add_dataviz_test(dataviz_tests tests/test_library.cpp)
add_dataviz_test(test_kdeplot tests/test_kdeplot.cpp)
add_dataviz_test(test_axis tests/test_axis.cpp)
add_dataviz_test(test_statistics tests/test_statistics.cpp)
add_dataviz_test(test_components tests/test_components.cpp)
