#include <cmath>

#include "checkerboard.hh"
#include "lambertian.hh"

CheckerBoard::CheckerBoard()
    : TextureMaterial(), scale(1)
{
    color1 = std::make_shared<Lambertian>(Color(0, 0, 0));
    color2 = std::make_shared<Lambertian>(Color(1, 1, 1));
}

CheckerBoard::CheckerBoard(const Color& c1, const Color& c2)
    : TextureMaterial(), scale(1)
{
    color1 = std::make_shared<Lambertian>(c1);
    color2 = std::make_shared<Lambertian>(c2);
}
CheckerBoard::CheckerBoard(shared_texture c1, shared_texture c2)
    : TextureMaterial(), color1(c1), color2(c2), scale(1)
{}

CheckerBoard::CheckerBoard(const Color& c1, const Color& c2,
        double kd, double ks)
    : TextureMaterial(kd, ks), scale(1)
{
    color1 = std::make_shared<Lambertian>(c1);
    color2 = std::make_shared<Lambertian>(c2);
}

CheckerBoard::CheckerBoard(shared_texture c1, shared_texture c2,
        double kd, double ks)
    : TextureMaterial(kd, ks), color1(c1), color2(c2), scale(1)
{}

Color CheckerBoard::get_color(const Point3& p, double u, double v) const {
    int square = (int) std::floor(u * scale) + (int) std::floor(v * scale);

    return ((square % 2) == 0) ? color1->get_color(p, u, v) : color2->get_color(p, u, v);
}
