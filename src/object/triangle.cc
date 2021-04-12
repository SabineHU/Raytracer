#include <cmath>

#include "triangle.hh"
#include "vector3_op.hh"
#include "lambertian.hh"

Triangle::Triangle()
    : Object()
{
    A = Point3(1, 0, 0);
    B = Point3(0, 1, 0);
    C = Point3(0, 0, 1);
    normal = vector::cross(C - A, B - A);
}

Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c)
    : Object(), A(a), B(b), C(c)
{
    this->normal = vector::cross(C - A, B - A).normalize();
}

Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c, const Vect& n)
    : Object(), A(a), B(b), C(c), normal(n)
{}

Vect Triangle::get_normal() const {
    return this->normal;
}

bool Triangle::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    auto cross_dir = vector::cross(ray.direction, C - A);
    double det = vector::dot(B - A, cross_dir);

    if (std::fabs(det) < 0.000001) return false;

    auto orig = ray.origin - A;
    double u = vector::dot(orig, cross_dir) / det;
    if (u < 0 || u > 1) return false;

    auto cross_orig = vector::cross(orig, B - A);
    double v = vector::dot(ray.direction, cross_orig) / det;
    if (v < 0 || u + v > 1) return false;

    double t = vector::dot(C - A, cross_orig) / det;
    if (t <= 0 || t <= t_min || t >= t_max) return false;

    t_max = t;

    info.point = ray.origin + ray.direction * t_max;
    info.u = u;
    info.v = v;
    info.normal = this->get_normal();
    this->get_properties(info);

    return true;
}
