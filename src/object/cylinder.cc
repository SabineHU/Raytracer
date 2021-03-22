#include "cylinder.hh"
#include "math.hh"
#include "unique.hh"
#include "vector3_op.hh"

Cylinder::Cylinder()
    : bottom(Point3(0, 0, 0)), top(Point3(0, 1, 0)), radius(1)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cylinder::Cylinder(const Point3& b, const Point3& t, double r)
    : bottom(b), top(t), radius(r)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Cylinder::Cylinder(const Point3& b, const Point3& t, double r, shared_texture s)
    : Object(s), bottom(b), top(t), radius(r)
{}

Cylinder::Cylinder(const Point3& b, const Point3& t, double r, const Color& c)
    : Object(std::make_shared<Unique>(c)), bottom(b), top(t), radius(r)
{}

Vect Cylinder::get_normal_at(const Vect&) const {
    return normal;
}

bool Cylinder::find_intersection(const Ray& ray, double& t_min, double& t_max) {
    Vect axis = this->bottom - this->top;
    Vect oc = ray.origin - top;
    double dist = axis.square_length(); // distance between top and bottom

    // Equation of the axis of the cylinder: y = dir * x + offs
    double dir = vector::dot(axis, ray.direction);
    double offs = vector::dot(axis, oc);

    double a = dist - dir * dir;
    double b = dist * vector::dot(oc, ray.direction) - offs * dir;
    double c = dist * oc.square_length() - radius * radius * dist - offs * offs;

    double discriminant = b * b - a * c;
    if (discriminant <= 0) return false;

    discriminant = std::sqrt(discriminant);
    double t = (-b - discriminant) / a;

    // Tube
    double y = dir * t + offs;
    if (y > 0 && y < dist && t > t_min && t < t_max) {
        normal = (oc + ray.direction * t - axis * y / dist) / radius;
        t_max = t;
        return true;
    }

    // Bottom
    t = - offs / dir;
    if (std::abs(a * t + b) < discriminant && t > t_min && t < t_max) {
        t_max = t;
        normal = axis / -dist;
        return true;
    }

    // Top
    t = (dist - offs) / dir;
    if (std::abs(a * t + b) < discriminant && t > t_min && t < t_max) {
        t_max = t;
        normal = axis / dist;
        return true;
    }
    return false;
}

int Cylinder::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
