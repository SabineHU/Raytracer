#include "unique.hh"

Unique::Unique(const Color& c)
    : color(c)
{}

Color Unique::get_color(const Ray&) const {
    return color;
}
