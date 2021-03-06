#include "unique.hh"

Unique::Unique(const Color& c)
    : color(c)
{}

Color Unique::get_color(double, double, double) const {
    return color;
}
