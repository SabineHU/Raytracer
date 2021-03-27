#include <cmath>

#include "checkerboard.hh"

CheckerBoard::CheckerBoard()
    : TextureMaterial(), color1(Color(0, 0, 0)), color2(Color(1, 1, 1))
{}

CheckerBoard::CheckerBoard(const Color& c1, const Color& c2)
    : TextureMaterial(), color1(c1), color2(c2)
{}

CheckerBoard::CheckerBoard(const Color& c1, const Color& c2,
        double kd, double ks)
    : TextureMaterial(kd, ks), color1(c1), color2(c2)
{}

Color CheckerBoard::get_color(const Point3&, double u, double v) const {
    int square = (int) std::floor(u) + (int) std::floor(v);
    return ((square % 2) == 0) ? color1 : color2;
}
