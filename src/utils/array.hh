#pragma once

#include <vector>

namespace array {

inline int get_min_index(std::vector<double> object_intersections) {
    int index = -1;
    double min = -1;
    for (size_t i = 0; i < object_intersections.size(); ++i) {
        if (object_intersections[i] < 0)
            continue;
        if (min == -1 || object_intersections[i] < min) {
            index = i;
            min = object_intersections[i];
        }
    }
    return index;
}

}
