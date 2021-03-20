#include "smooth_triangle.hh"

SmoothTriangle::SmoothTriangle(const Point3& a, const Point3& b,
        const Point3& c)
    : Triangle(a, b, c), normalA(Vect()), normalB(Vect()), normalC(Vect())
{}

SmoothTriangle::SmoothTriangle(const Point3& a, const Point3& b,
        const Point3& c, const Color& col)
    : Triangle(a, b, c, col), normalA(Vect()), normalB(Vect()), normalC(Vect())
{}

SmoothTriangle::SmoothTriangle(const Point3& a, const Point3& b,
        const Point3& c, const Vect& na, const Vect& nb, const Vect& nc)
    : Triangle(a, b, c), normalA(na), normalB(nb), normalC(nc)
{}

Vect SmoothTriangle::get_normal_at(const Vect& point) const {
    if (normalA.is_zero() && normalB.is_zero() && normalC.is_zero())
        return Triangle::get_normal_at(point);

    auto normal = normalA * (1 - barycenter.x - barycenter.y)
        + normalB * barycenter.x
        + normalC * barycenter.y;
    return normal.normalize();
}
