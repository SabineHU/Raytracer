#pragma once

#include "vector3.hh"

namespace hash {

inline size_t get_value_hash(double value) {
    size_t hash = std::hash<double>{}(value);
    hash += hash << 10;
    hash ^= hash >> 6;
    return hash;
}

inline size_t get_point_hash(const Point3& p) {
    // jenkins one at a time hash
    size_t hash = 0;

    hash += get_value_hash(p.x);
    hash += get_value_hash(p.y);
    hash += get_value_hash(p.z);

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

}
