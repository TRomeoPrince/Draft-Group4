#include "CountPlot.hpp"

CountPlot::Counts CountPlot::calculate(
    const std::vector<std::string>& categories
) {
    Counts counts;

    for (const auto& category : categories) {
        if (!category.empty()) {
            ++counts[category];
        }
    }

    return counts;
}
