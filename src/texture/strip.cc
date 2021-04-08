#include <cmath>

#include "strip.hh"
#include "lambertian.hh"

Strip::Strip()
    : TextureMaterial(), horizontal(true), scale(15), planar(false)
{
    color1 = std::make_shared<Lambertian>(Color(0, 0, 0));
    color2 = std::make_shared<Lambertian>(Color(1, 1, 1));
}

Strip::Strip(const Color& c1, const Color& c2)
    : TextureMaterial(), horizontal(true), scale(15), planar(false)
{
    color1 = std::make_shared<Lambertian>(c1);
    color2 = std::make_shared<Lambertian>(c2);
}

Strip::Strip(shared_texture c1, shared_texture c2)
    : TextureMaterial(), color1(c1), color2(c2), horizontal(true), scale(15),
    planar(false)
{}

Strip::Strip(const Color& c1, const Color& c2, bool h, double s)
    : TextureMaterial(), horizontal(h), scale(s), planar(false)
{
    color1 = std::make_shared<Lambertian>(c1);
    color2 = std::make_shared<Lambertian>(c2);
}

Strip::Strip(shared_texture c1, shared_texture c2, bool h, double s)
    : TextureMaterial(), color1(c1), color2(c2), horizontal(h), scale(s),
    planar(false)
{}

Color Strip::get_color(const Point3& p, double u, double v) const {
    double value;
    if (!planar) {
        value = horizontal ? u : v;
    } else {
        value = horizontal ? p.y : p.x;
    }

    return ((int) std::floor(value * scale)) % 2 == 0 ? color1->get_color(p, u, v) : color2->get_color(p, u, v);
}
