#include "Annotation.hpp"
#include <iostream>
int main() {
    Annotation annotations;
    annotations.add(100, 60, "Highest mark");
    annotations.add(200, 90, "Average");
    for (const auto& note : annotations.getItems())
        std::cout << note.text << " at (" << note.x << ", " << note.y << ")\n";
}