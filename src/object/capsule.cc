#include "capsule.hh"
#include "math.hh"
#include "unique.hh"
#include "vector3_op.hh"

Capsule::Capsule()
    : bottom(Point3(0, 0, 0)), top(Point3(0, 1, 0)), radius(1)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Capsule::Capsule(const Point3& b, const Point3& t, double r)
    : bottom(b), top(t), radius(r)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Capsule::Capsule(const Point3& b, const Point3& t, double r, shared_texture s)
    : Object(s), bottom(b), top(t), radius(r)
{}

Capsule::Capsule(const Point3& b, const Point3& t, double r, const Color& c)
    : Object(std::make_shared<Unique>(c)), bottom(b), top(t), radius(r)
{}

Vect Capsule::get_normal_at(const Vect& point) const {
    Vect ba = bottom - top;
    Vect pa = point - top;
    double h = std::min(std::max(vector::dot(pa, ba) / vector::dot(ba, ba), 0.0), 1.0);
    return (pa + ba * -h) / radius;
}

bool Capsule::find_intersection(const Ray& ray, double& t_min, double& t_max) {
    Vect axis = this->bottom - this->top;
    Vect oc = ray.origin - this->top;
    double dist = axis.square_length();

    // Equation of the axis of the capsule: y = dir * x + offs
    double dir = vector::dot(axis,ray.direction);
    double offs = vector::dot(axis, oc);

    double a = dist - dir * dir;
    double b = dist * vector::dot(oc, ray.direction) - offs * dir;
    double c = dist * oc.square_length() - radius * radius * dist - offs * offs;

    double discriminant = b * b - a * c;
    if (discriminant <= 0) return false;

    double t = (-b - std::sqrt(discriminant)) / a;

    // Tube
    double y = dir * t + offs;
    if (y > 0 && y < dist && t > t_min && t < t_max) {
        t_max = t;
        return true;
    }

    // Top && bottom
    if (y > 0)
        oc = ray.origin - this->bottom;

    b = vector::dot(oc, ray.direction);
    c = oc.square_length() - radius * radius;

    discriminant = b * b - c;

    if (discriminant <= 0) return false;
    t = -b - std::sqrt(discriminant);

    if (t <= t_min || t >= t_max) return false;

    t_max = t;
    return true;
}

int Capsule::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
