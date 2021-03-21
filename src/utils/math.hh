#pragma once

#include <cmath>
#include <limits>

namespace math {

constexpr double pi = 3.14159265358979323846;

constexpr double inf = std::numeric_limits<double>::infinity();

inline double quadratic_equation_root_1(double a, double b, double delta) {
    return (-b - std::sqrt(delta)) / (2 * a);
}

inline double quadratic_equation_root_2(double a, double b, double delta) {
    return (-b + std::sqrt(delta)) / (2 * a);
}

inline double quadratic_equation_min_root(double a, double b, double delta) {
    double x1 = quadratic_equation_root_1(a, b, delta);
    double x2 = quadratic_equation_root_2(a, b, delta);
    return x1 > x2 ? x2 : x1;
}

inline double randian_to_degree(double radian) {
    return radian * 180 / pi;
}

inline double degree_to_radian(double degree) {
    return degree * pi / 180;
}

}
