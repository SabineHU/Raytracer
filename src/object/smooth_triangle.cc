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

Vect SmoothTriangle::get_normal_at(const Vect& point,
        const Point3& center) const {
    auto n = Triangle::get_normal_at(point, center);
    if (normalA.is_zero() && normalB.is_zero() && normalC.is_zero())
        return Triangle::get_normal_at(point, center);

    auto dist_a = (A - point).magnitude();
    auto dist_b = (B - point).magnitude();
    auto dist_c = (C - point).magnitude();
    auto dist = dist_a + dist_b + dist_c;

    auto a = this->normalA;
    auto b = this->normalB;
    auto c = this->normalC;


    //return (a + b + c).normalize();

    //hitNormal = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2; 
    auto normal = normalA * (1 - barycenter.x - barycenter.y) 
        + normalB * barycenter.x
        + normalC * barycenter.y;
    return normal.normalize();
}
