#pragma once

#include "vector3.hh"

namespace vector {
    inline double dot(const Vect& u, const Vect& v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    inline Vect cross(const Vect& u, const Vect& v) {
        auto x = u.y * v.z - u.z * v.y;
        auto y = u.z * v.x - u.x * v.z;
        auto z = u.x * v.y - u.y * v.x;
        return Vect(x, y, z);
    }
}
