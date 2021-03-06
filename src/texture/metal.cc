#include "metal.hh"

Metal::Metal(const Color& c)
    : color(c)
{}

Color Metal::get_color(double, double, double) const {
    return color;
}
