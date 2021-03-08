#pragma once

#include <cmath>

namespace math {

constexpr double pi = 3.14159265358979323846;

inline double quadratic_equation_root_1(double a, double b, double delta) {
    return (-b - std::sqrt(delta)) / (2 * a);

}

inline double quadratic_equation_root_2(double a, double b, double delta) {
    return (-b + std::sqrt(delta)) / (2 * a);
}

inline double randian_to_degree(double radian) {
    return radian * 180 / pi;
}

inline double degree_to_radian(double degree) {
    return degree * pi / 180;
}

}
