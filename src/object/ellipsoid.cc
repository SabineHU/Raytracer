#include <cmath>

#include "ellipsoid.hh"
#include "vector3_op.hh"
#include "lambertian.hh"

Ellipsoid::Ellipsoid()
    : Object(), center(Vect(0, 0, 0)), radius(Vect(1, 0.5, 1))
{}

Ellipsoid::Ellipsoid(const Vect& cent, const Vect& rad)
    : Object(), center(cent), radius(rad)
{}

Vect Ellipsoid::get_normal(const Point3& point) const {
    return (point - center) / radius;
}

bool Ellipsoid::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    // Equation:
    // x^2 / a^2 + y^2 / b^2 + z^2 / c^2 - 1 = 0

    Vect orig = (ray.origin - this->center) / this->radius;
    Vect dir = ray.direction / this->radius;

    double a = dir.square_length();
    double b = vector::dot(orig, dir);
    double c = orig.square_length() - 1;

    double discriminant = b * b - a * c;
    if (discriminant < 0) return false;

    double t = (-b - std::sqrt(discriminant)) / a;
    if (t <= t_min || t >= t_max) return false;

    t_max = t;
    info.point = ray.origin + ray.direction * t_max;
    info.normal = this->get_normal(info.point);
    this->get_properties(info);

    return true;
}
