#include "lambertian.hh"

Lambertian::Lambertian(const Color& c)
    : TextureMaterial(1, 0), color(c)
{}

Lambertian::Lambertian(const Color& c, double kd)
    : TextureMaterial(kd, 0), color(c)
{}

Color Lambertian::get_color(const Point3&, double, double) const {
    return color;
}
