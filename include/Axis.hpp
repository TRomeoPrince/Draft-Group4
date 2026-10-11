#ifndef AXIS_HPP
#define AXIS_HPP

#include <cstddef>
#include <vector>

class Axis {
private:
    double minValue;
    double maxValue;
    double screenStart;
    double screenEnd;

public:
    Axis(
        double minValue,
        double maxValue,
        double screenStart,
        double screenEnd
    );

    double scale(double value) const;

    std::vector<double> ticks(std::size_t count = 6) const;

    double getMin() const;
    double getMax() const;
    double getScreenStart() const;
    double getScreenEnd() const;

    void setRange(double minValue, double maxValue);
    void setScreenRange(double screenStart, double screenEnd);
};

#endif
