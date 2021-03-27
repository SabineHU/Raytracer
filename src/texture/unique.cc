#include "unique.hh"

Unique::Unique(const Color& c)
    : TextureMaterial(1, 0), color(c)
{}

Unique::Unique(const Color& c, double kd)
    : TextureMaterial(kd, 0), color(c)
{}

Color Unique::get_color(const Point3&, double, double) const {
    return color;
}
