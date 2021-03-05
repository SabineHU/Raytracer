#include "plane.hh"

Plane::Plane ()
    : normal(Vect(1, 0, 0)), distance(0), color(Color(0.5, 0.5, 0.5))
{}

Plane::Plane (Vect n, double d, Color c)
    : normal(n), distance(d), color(c)
{}

Color Plane::getColor() const {
    return color;
}

Vect Plane::getNormalAt(Vect) const {
    return normal;
}

double Plane::findIntersection(Ray ray) const {
    Vect ray_direction = ray.direction;

    double a = ray_direction.dotProduct(normal);
    if (a == 0)
        return -1;

    auto n = normal;
    double b = n.dotProduct(ray.origin + normal * -distance);
    return -1 * b / a;
}
