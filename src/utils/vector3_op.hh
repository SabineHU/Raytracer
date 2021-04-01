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

inline double dot_x(const Vect& u, const Vect& v) {
    return u.x * v.x;
}

inline double dot_y(const Vect& u, const Vect& v) {
    return u.y * v.y;
}

inline double dot_z(const Vect& u, const Vect& v) {
    return u.z * v.z;
}

inline double dot_xy(const Vect& u, const Vect& v) {
    return dot_x(u, v) + dot_y(u, v);
}

inline Vect rotate(const Vect& u, double theta) {
    // Matrix 3 * 3
    // [ a b 0 ]
    // [ d e 0 ]
    // [ 0 0 1 ]
    auto a = cos(theta);
    auto b = -sin(theta);
    auto d = sin(theta);
    auto e = cos(theta);
    return Vect(a * u.x + b * u.y, d * u.x + e * u.y, u.z);
}
}
