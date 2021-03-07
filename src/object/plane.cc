#include "plane.hh"
#include "vector3_op.hh"
#include "unique.hh"

Plane::Plane ()
    : normal(Vect(1, 0, 0)), distance(0)
{
    color = Color(0.5, 0.5, 0.5, 0);
    texture = std::make_shared<Unique>(color);
    specular = 0;
}

Plane::Plane (const Vect& n, double d, const Color& c)
    : normal(n), distance(d), color(c)
{
    texture = std::make_shared<Unique>(c);
    specular = 0;
}

Plane::Plane(const Vect& n, double d, const Color& c, shared_texture t)
    : Object(t, 0), normal(n), distance(d), color(c)
{}

Plane::Plane(const Vect& n, double d, const Color& c, shared_texture t,
        double s)
    : Object(t, s), normal(n), distance(d), color(c)
{}

Color Plane::get_color() const {
    return color;
}

Vect Plane::get_normal_at(const Vect&) const {
    return normal;
}

double Plane::find_intersection(const Ray& ray) const {
    Vect ray_direction = ray.direction;
    double a = vector::dot(ray_direction, normal);
    if (a == 0)
        return -1;

    double b = vector::dot(normal, ray.origin + normal * -distance);
    return -1 * b / a;
}
