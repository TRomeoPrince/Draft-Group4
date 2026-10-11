#ifndef ANNOTATION_HPP
#define ANNOTATION_HPP

#include <string>
#include <vector>

struct AnnotationItem {
    double x;
    double y;
    std::string text;
};

class Annotation {
private:
    std::vector<AnnotationItem> items;

public:
    void add(double x, double y, const std::string& text);
    void clear();
    const std::vector<AnnotationItem>& getItems() const;
};

#endif
