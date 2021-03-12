#include "plane.hh"
#include "vector3_op.hh"
#include "unique.hh"

Plane::Plane()
    : normal(Vect(1, 0, 0)), distance(0)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Plane::Plane(const Vect& n, double d)
    : normal(n), distance(d)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Plane::Plane(const Vect& n, double d, shared_texture t)
    : Object(t), normal(n), distance(d)
{}

Plane::Plane(const Vect& n, double d, const Color& c)
    : Object(std::make_shared<Unique>(c)), normal(n), distance(d)
{}

Vect Plane::get_normal_at(const Vect&) const {
    return normal;
}

double Plane::find_intersection(const Ray& ray) const {
    double a = vector::dot(ray.direction, normal);
    if (a == 0)
        return -1;

    double b = vector::dot(normal, ray.origin + normal * -distance);
    return - b / a;
}

int Plane::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
