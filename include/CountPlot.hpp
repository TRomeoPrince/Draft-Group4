#ifndef COUNTPLOT_HPP
#define COUNTPLOT_HPP

#include <cstddef>
#include <map>
#include <string>
#include <vector>

class CountPlot {
public:
    using Counts = std::map<std::string, std::size_t>;

    static Counts calculate(const std::vector<std::string>& categories);
};

#endif
