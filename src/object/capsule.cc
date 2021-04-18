#include "capsule.hh"
#include "math.hh"
#include "lambertian.hh"
#include "vector3_op.hh"

Capsule::Capsule()
    : Object(), bottom(Point3(0, 0, 0)), top(Point3(0, 1, 0)), radius(1)
{}

Capsule::Capsule(const Point3& b, const Point3& t, double r)
    : Object(), bottom(b), top(t), radius(r)
{}

Vect Capsule::get_normal(const Point3& point) const {
    Vect ba = bottom - top;
    Vect pa = point - top;
    double h = std::min(std::max(vector::dot(pa, ba) / vector::dot(ba, ba), 0.0), 1.0);

    return ((pa + ba * -h) / radius);
}

bool Capsule::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    Vect oc = ray.origin - this->top;
    Vect axis = this->bottom - this->top;
    double dist = axis.square_length();
    double radius2 = radius * radius;

    // Equation of the axis of the capsule: y = dir * x + offs
    double dir = vector::dot(axis,ray.direction);
    double offs = vector::dot(axis, oc);

    double a = dist - dir * dir;
    double b = dist * vector::dot(oc, ray.direction) - offs * dir;
    double c = dist * oc.square_length() - radius2 * dist - offs * offs;

    double t = math::get_min_root_quadratic_opti(a, b, c);
    if (t == 0) return false;

    // Tube
    a = dir * t + offs;
    if (c > 0 && c < dist && t > t_min && t < t_max) {
        t_max = t;
        info.point = ray.origin + ray.direction * t_max;
        info.normal = this->get_normal(info.point);
        this->get_properties(info);
        return true;
    }

    // Top && bottom
    if (a > 0) oc = ray.origin - this->bottom;

    b = vector::dot(oc, ray.direction);
    c = oc.square_length() - radius2;

    t = math::get_min_root_quadratic_opti(1, b, c);
    if (t == 0 || t <= t_min || t >= t_max) return false;

    t_max = t;
    info.point = ray.origin + ray.direction * t_max;
    info.normal = this->get_normal(info.point);
    this->get_properties(info);
    return true;
}
