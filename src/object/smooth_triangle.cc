#include "smooth_triangle.hh"

SmoothTriangle::SmoothTriangle(const Point3& a, const Point3& b,
        const Point3& c)
    : Triangle(a, b, c), normalA(Vect()), normalB(Vect()), normalC(Vect())
{}

SmoothTriangle::SmoothTriangle(const Point3& a, const Point3& b,
        const Point3& c, const Vect& na, const Vect& nb, const Vect& nc)
    : Triangle(a, b, c), normalA(na), normalB(nb), normalC(nc)
{}

Vect SmoothTriangle::get_normal_at(const Point3& point, double u, double v) const {
    if (normalA.is_zero() && normalB.is_zero() && normalC.is_zero())
        return Triangle::get_normal();

    auto normal = normalA * (1 - u - v) + normalB * u + normalC * v;
    return (normal + Object::get_bump_at(point)).normalize();
}
