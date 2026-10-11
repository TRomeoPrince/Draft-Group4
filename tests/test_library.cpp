#include "Axis.hpp"
#include "CountPlot.hpp"
#include "DataProcessor.hpp"
#include "Histogram.hpp"
#include "KDEPlot.hpp"
#include "Renderer.hpp"
#include "Statistics.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace {
bool approximatelyEqual(double a, double b, double tolerance = 1e-9) {
    return std::fabs(a - b) <= tolerance;
}
}

int main() {
    {
        std::vector<double> values{1, 2, 3, 4, 5};
        assert(Statistics::count(values) == 5);
        assert(approximatelyEqual(Statistics::mean(values), 3.0));
        assert(approximatelyEqual(Statistics::minimum(values), 1.0));
        assert(approximatelyEqual(Statistics::maximum(values), 5.0));
        assert(approximatelyEqual(Statistics::median(values), 3.0));
    }

    {
        std::vector<std::string> categories{
            "Uganda", "Kenya", "Uganda", "Rwanda", "Uganda", "Kenya"
        };

        auto counts = CountPlot::calculate(categories);

        assert(counts["Uganda"] == 3);
        assert(counts["Kenya"] == 2);
        assert(counts["Rwanda"] == 1);
    }

    {
        std::vector<double> values{1, 2, 3, 4};
        auto bins = Histogram::build(values, 2);

        assert(bins.size() == 2);
        assert(bins[0].count == 2);
        assert(bins[1].count == 2);
    }

    {
        Axis axis(0, 100, 0, 500);
        assert(approximatelyEqual(axis.scale(50), 250.0));

        auto ticks = axis.ticks(3);
        assert(ticks.size() == 3);
        assert(approximatelyEqual(ticks[0], 0.0));
        assert(approximatelyEqual(ticks[1], 50.0));
        assert(approximatelyEqual(ticks[2], 100.0));
    }

    {
        std::vector<std::string> raw{" 10 ", "20", "bad", "30"};
        auto numeric = DataProcessor::toNumeric(raw);

        assert(numeric.size() == 3);
        assert(approximatelyEqual(numeric[0], 10.0));
        assert(approximatelyEqual(numeric[2], 30.0));
    }

    {
        std::vector<double> values{1, 2, 2, 3, 4, 5};
        auto points = KDEPlot::estimate(values, 25);

        assert(points.size() == 25);

        for (const auto& point : points) {
            assert(point.density >= 0.0);
        }
    }

    {
        CountPlot::Counts counts{{"A", 2}, {"B", 4}};
        std::string svg = Renderer::renderCountPlot(counts, 500, 350, "Test");

        assert(svg.find("<svg") != std::string::npos);
        assert(svg.find("<rect") != std::string::npos);
        assert(svg.find("Test") != std::string::npos);
    }

    std::cout << "All tests passed.\n";
    return 0;
}
