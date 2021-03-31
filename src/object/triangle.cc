#include "triangle.hh"
#include "vector3_op.hh"
#include "lambertian.hh"

Triangle::Triangle()
    : Object()
{
    A = Point3(1, 0, 0);
    B = Point3(0, 1, 0);
    C = Point3(0, 0, 1);
}

Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c)
    : Object(), A(a), B(b), C(c)
{}

Vect Triangle::get_normal_at(const Point3&, double, double) const {
    // Normal is the same at any point of the triangle
    return (vector::cross(C - A, B - A)).normalize();
}

Vect Triangle::get_normal() const {
    return this->get_normal_at(Vect(), 0, 0);
}

double Triangle::get_distance() const {
    return vector::dot(this->get_normal(), A);
}

bool Triangle::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    auto v0v1 = B - A;
    auto v0v2 = C - A;

    auto pvec = vector::cross(ray.direction, v0v2);
    double det = vector::dot(v0v1, pvec);

    // ray and triangle are parallel if det is close to 0
    if (std::fabs(det) < 0.000001) return false;

    double invDet = 1 / det;

    auto tvec = ray.origin - A;
    auto u = vector::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) return false;

    auto qvec = vector::cross(tvec, v0v1);
    auto v = vector::dot(ray.direction, qvec) * invDet;
    if (v < 0 || u + v > 1) return false;

    auto t = vector::dot(v0v2, qvec) * invDet;

    if (t <= 0 || t <= t_min || t >= t_max)
        return false;

    this->barycenter = Vect(u, v, 0);
    t_max = t;
    info.point = ray.origin + ray.direction * t_max;
    return true;
}

int Triangle::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
