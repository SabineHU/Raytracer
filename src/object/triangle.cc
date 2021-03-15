#include "triangle.hh"
#include "vector3_op.hh"
#include "unique.hh"

Triangle::Triangle()
{
    A = Point3(1, 0, 0);
    B = Point3(0, 1, 0);
    C = Point3(0, 0, 1);
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c)
    : A(a), B(b), C(c)
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c,
        shared_texture t)
    : Object(t), A(a), B(b), C(c)
{}

Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c,
        const Color& col)
    : Object(std::make_shared<Unique>(col)), A(a), B(b), C(c)
{}

Vect Triangle::get_normal_at(const Vect&) const {
    // Normal is the same at any point of the triangle
    return (vector::cross(C - A, B - A)).normalize();
}

Vect Triangle::get_normal() const {
    return this->get_normal_at(Vect(0, 0, 0));
}

double Triangle::get_distance() const {
    return vector::dot(this->get_normal(), A);
}

double Triangle::find_intersection(const Ray& ray) const {

    auto v0v1 = B - A;
    auto v0v2 = C - A;

    auto pvec = vector::cross(ray.direction, v0v2);
    double det = vector::dot(v0v1, pvec);

    // ray and triangle are parallel if det is close to 0
    if (std::fabs(det) < 0.000001) return -1;

    double invDet = 1 / det;

    auto tvec = ray.origin - A;
    auto u = vector::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) return -1;

    auto qvec = vector::cross(tvec, v0v1);
    auto v = vector::dot(ray.direction, qvec) * invDet;
    if (v < 0 || u + v > 1) return -1;

    auto t = vector::dot(v0v2, qvec) * invDet;

    return (t > 0) ? t : -1;

    //const Vect normal = this->get_normal_at(ray.origin);
    //double a = vector::dot(ray.direction, normal);
    //if (a == 0)
    //    return -1;

    //double b = vector::dot(normal, ray.origin + normal * -this->get_distance());
    //double distance = - b / a;

    //Point3 P = ray.direction * distance + ray.origin;

    //if (vector::dot(vector::cross(C - A, P - A), normal) >= 0
    //    && vector::dot(vector::cross(B - C, P - C), normal) >= 0
    //    && vector::dot(vector::cross(A - B, P - B), normal) >= 0)
    //    return distance - 0.000001;
    //return -1;
}

int Triangle::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}
