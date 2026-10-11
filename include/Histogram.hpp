#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <cstddef>
#include <vector>

struct HistogramBin {
    double lower;
    double upper;
    std::size_t count;
};

class Histogram {
public:
    static std::vector<HistogramBin> build(
        const std::vector<double>& data,
        std::size_t binCount = 10
    );
};

#endif
