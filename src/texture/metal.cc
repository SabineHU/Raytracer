#include "metal.hh"

Metal::Metal(const Color& c)
    : TextureMaterial(1, 1), color(c)
{
    set_reflection_type();
}

Metal::Metal(const Color& c, double ks)
    : TextureMaterial(1, ks), color(c)
{
    set_reflection_type();
}

Color Metal::get_color(const Point3&, double, double) const {
    return color;
}
