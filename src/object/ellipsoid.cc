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

Vect Ellipsoid::get_normal_at(const Point3& point, double, double) const {
    return ((point - center) / radius + Object::get_bump_at(point)).normalize();
}

bool Ellipsoid::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    auto oc = ray.origin - this->center;

    Vect ocn = oc / this->radius;
    Vect rdn = ray.direction / this->radius;

    double a = rdn.square_length();
    double b = vector::dot(ocn, rdn);
    double c = ocn.square_length() - 1;

    double discriminant = b * b - a * c;
    if (discriminant < 0) return false;

    double t = (-b - std::sqrt(discriminant)) / a;
    if (t <= t_min || t >= t_max) return false;

    t_max = t;
    info.point = ray.origin + ray.direction * t_max;

    return true;
}

int Ellipsoid::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
