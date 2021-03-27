#include "metal.hh"

Metal::Metal(const Color& c)
    : TextureMaterial(1, 1), color(c)
{}

Metal::Metal(const Color& c, double ks)
    : TextureMaterial(1, ks), color(c)
{}

Color Metal::get_color(const Point3&, double, double) const {
    return color;
}
