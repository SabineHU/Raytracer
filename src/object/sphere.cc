#include <cmath>

#include "sphere.hh"
#include "math.hh"
#include "vector3_op.hh"
#include "lambertian.hh"

Sphere::Sphere()
    : Object(), center(Vect(0, 0, 0)), radius(1)
{}

Sphere::Sphere(const Vect& cent, double rad)
    : Object(), center(cent), radius(rad)
{}

Vect Sphere::get_normal_at(const Point3& point, double, double) const {
    return ((point - center) + Object::get_bump_at(point)).normalize();
}

bool Sphere::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    auto oc = ray.origin - this->center;

    //double a = 1; // normalized
    double b = 2 * vector::dot(oc, ray.direction);
    double c = vector::dot(oc, oc) - this->radius * this->radius;

    double discriminant = b * b - 4 * c;

    if (discriminant <= 0) return false;

    double roots[2] = { -1 };
    math::quadratic_equation_roots(1, b, discriminant, roots);

    double x = roots[0];
    if (x <= t_min || x >= t_max) return false;

    t_max = x;
    info.point = ray.origin + ray.direction * t_max;

    info.u = 0.5 + atan2(info.point.z - center.z, info.point.x - center.x) / (2 * math::pi);
    info.v = 0.5 - asin(info.point.y) / math::pi;

    info.normal = this->get_normal_at(info.point, info.u, info.v);

    info.t_min = roots[0];
    info.t_max = roots[1];

    return true;
}

int Sphere::get_isolevel_at(const Point3& point) const {
    double distance = (point - this->center).square_length();
    if (distance > 4 * radius * radius)
        return 100;

    for (int i = 199; i > 100; i-=1) {
        if (distance > (radius * i / 100) * (radius * i / 100))
            return i - 100;
    }
    return 0;
}
