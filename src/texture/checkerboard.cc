#include <cmath>

#include "checkerboard.hh"

CheckerBoard::CheckerBoard()
    : color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

CheckerBoard::CheckerBoard(const Color& c1, const Color& c2)
    : color1(c1), color2(c2)
{}

Color CheckerBoard::get_color(double x, double, double z) const {
    int square = (int) std::floor(x) + (int) std::floor(z);

    return ((square % 2) == 0) ? color1 : color2;
}
