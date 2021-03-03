#pragma once

#include <cmath>

namespace math {

double quadratic_equation_root_1(double a, double b, double delta) {
    return (-b - std::sqrt(delta)) / (2 * a);

}

double quadratic_equation_root_2(double a, double b, double delta) {
    return (-b + std::sqrt(delta)) / (2 * a);
}

}
