#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "vector3.hh"

namespace r_random {

inline int random_int(int min, int max) {
    return min + std::rand() % (max - min);
}

inline double random_double() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + random_double() * (max - min);
}

inline double random_0_1() {
    return (double) std::rand() / RAND_MAX;
}

inline Color random_color() {
    return Color(random_0_1(), random_0_1(), random_0_1()) / 2;
}

inline Color random_pastel_color() {
    double x = random_double(0, .5);
    double y = random_double(0, .5);
    double z = random_double(0, .5);

    return Color(.5 + x, .5 + y, .5 + z);
}

inline Vect random_vector() {
    return Vect(random_double(), random_double(), random_double());
}

inline Vect random_vector(double a, double b) {
    return Vect(random_double(a, b), random_double(a, b), random_double(a, b));
}

inline void shuffle(int* p, int n) {
    for (int i = n-1; i > 0; --i) {
        int target = random_int(0, i);
        std::swap(p[i], p[target]);
    }
}

}
