#include "cylinder.hh"
#include "math.hh"
#include "lambertian.hh"
#include "vector3_op.hh"

Cylinder::Cylinder()
    : Object(), bottom(Point3(0, 0, 0)), top(Point3(0, 1, 0)), radius(1)
{}

Cylinder::Cylinder(const Point3& b, const Point3& t, double r)
    : Object(), bottom(b), top(t), radius(r)
{}

static void compute_uv(IntersectionInfo& info, double dist) {
    info.u = 0.5 + atan2(info.point.x, info.point.y) / (2 * math::pi);
    info.v = 0.5 + info.point.z / dist;
}

bool Cylinder::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    // Equation over z-axis is x^2 + y^2 - 1 = 0

    Vect oc = ray.origin - this->top;
    Vect axis = this->bottom - this->top;
    double dist = axis.square_length(); // distance between top and bottom

    // Equation of the axis of the cylinder: y = dir * x + offs
    double dir = vector::dot(axis, ray.direction);
    double offs = vector::dot(axis, oc);

    double a = dist - dir * dir;
    double b = dist * vector::dot(oc, ray.direction) - offs * dir;
    double c = dist * oc.square_length() - radius * radius * dist - offs * offs;

    double discriminant = b * b - a * c;
    if (discriminant <= 0) return false;

    discriminant = std::sqrt(discriminant);
    double roots[2] = { (-b - discriminant) / a, (-b + discriminant) / a };
    double t = roots[0];

    // Tube
    c = dir * t + offs;
    if (c > 0 && c < dist && t > t_min && t < t_max) {
        info.normal = (oc + ray.direction * t - axis * c / dist) / radius;
        t_max = t;
        info.point = ray.origin + ray.direction * t_max;
        compute_uv(info, dist);

        info.t_min = roots[0];
        info.t_max = roots[1];
        this->get_properties(info);

        return true;
    }

    // Bottom
    t = - offs / dir;
    if (std::abs(a * t + b) < discriminant && t > t_min && t < t_max) {
        t_max = t;
        info.normal = axis / -dist;
        info.point = ray.origin + ray.direction * t_max;
        compute_uv(info, dist);

        info.t_min = t;
        info.t_max = t;
        this->get_properties(info);

        return true;
    }

    // Top
    t = (dist - offs) / dir;
    if (std::abs(a * t + b) < discriminant && t > t_min && t < t_max) {
        t_max = t;
        info.normal = axis / dist;
        info.point = ray.origin + ray.direction * t_max;
        compute_uv(info, dist);

        info.t_min = t;
        info.t_max = t;
        this->get_properties(info);

        return true;
    }

    return false;
}
