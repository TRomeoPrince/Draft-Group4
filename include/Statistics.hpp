#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <cstddef>
#include <vector>

class Statistics {
public:
    static std::size_t count(const std::vector<double>& data);
    static double mean(const std::vector<double>& data);
    static double minimum(const std::vector<double>& data);
    static double maximum(const std::vector<double>& data);
    static double median(std::vector<double> data);
    static double variance(const std::vector<double>& data);
    static double standardDeviation(const std::vector<double>& data);
};

#endif
