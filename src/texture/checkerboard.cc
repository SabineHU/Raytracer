#include <cmath>

#include "checkerboard.hh"

CheckerBoard::CheckerBoard()
    : TextureMaterial(0), color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

CheckerBoard::CheckerBoard(const Color& c1, const Color& c2)
    : TextureMaterial(0), color1(c1), color2(c2)
{}

CheckerBoard::CheckerBoard(const Color& c1, const Color& c2, double s)
    : TextureMaterial(s), color1(c1), color2(c2)
{}

Color CheckerBoard::get_color(const Point3& p, double, double) const {
    auto x = p.x;
    auto z = p.z;

    int square = (int) std::floor(x) + (int) std::floor(z);
    return ((square % 2) == 0) ? color1 : color2;
}
