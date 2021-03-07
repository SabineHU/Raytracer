#include "unique.hh"

Unique::Unique(const Color& c)
    : TextureMaterial(0), color(c)
{}

Unique::Unique(const Color& c, double s)
    : TextureMaterial(s), color(c)
{}

Color Unique::get_color(const Ray&, const Vect&) const {
    return color;
}
