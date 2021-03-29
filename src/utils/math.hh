#pragma once

#include <cmath>
#include <limits>

namespace math {

constexpr double pi = 3.14159265358979323846;

constexpr double inf = std::numeric_limits<double>::infinity();

inline double quadratic_equation_root_1(double a, double b, double delta) {
    return (-b - delta) / (2 * a);
}

inline double quadratic_equation_root_2(double a, double b, double delta) {
    return (-b + delta) / (2 * a);
}

inline double quadratic_equation_min_root(double a, double b, double delta) {
    double sqrt_delta = std::sqrt(delta);
    double x1 = quadratic_equation_root_1(a, b, sqrt_delta);
    double x2 = quadratic_equation_root_2(a, b, sqrt_delta);
    return std::min(x1, x2);
}

inline void quadratic_equation_roots(double a, double b, double delta,
        double roots[2]) {
    double sqrt_delta = std::sqrt(delta);
    roots[0] = quadratic_equation_root_1(a, b, sqrt_delta);
    roots[1] = quadratic_equation_root_2(a, b, sqrt_delta);

    if (roots[1] < roots[0])
        std::swap(roots[0], roots[1]);
}

inline double randian_to_degree(double radian) {
    return radian * 180 / pi;
}

inline double degree_to_radian(double degree) {
    return degree * pi / 180;
}

inline double cube_root(double v) {
    if (v < 0)
        return -std::cbrt(-v);
    return std::cbrt(v);
}

inline int round_multiple(int nb, int multiple) {
    if (multiple == 0) return nb;

    auto m = nb % multiple;
    return m == 0 ? nb : nb - m;
}

}
