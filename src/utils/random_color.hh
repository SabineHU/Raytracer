#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "vector3.hh"

namespace r_random {

inline int random_int(int min, int max) {
    return min + std::rand() % (max - min);
}

inline double random_0_1() {
    return (double) std::rand() / RAND_MAX;
}

inline Color random_color() {
    return Color(random_0_1(), random_0_1(), random_0_1()) / 2;
    //return Color(random_0_1(), random_0_1(), random_0_1());
}

}
