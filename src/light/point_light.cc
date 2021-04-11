#include "point_light.hh"

PointLight::PointLight ()
    : position(Vect(0, 0, 0)), color(Color(1, 1, 1)), intensity(1)
{}

PointLight::PointLight (const Vect& p, const Color& c)
    : position(p), color(c), intensity(1)
{}

PointLight::PointLight (const Vect& p, const Color& c, double i)
    : position(p), color(c), intensity(i)
{}

Vect PointLight::get_light_position() const {
    return this->position;
}

Color PointLight::get_light_color() const {
    return this->color;
}

double PointLight::get_intensity() const {
    return this->intensity;
}
