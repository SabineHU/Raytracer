#include "capped_cone.hh"
#include "lambertian.hh"
#include "vector3_op.hh"
#include "math.hh"

CappedCone::CappedCone()
    : Object(), bottom(Point3(0, 0, 0)), top(Point3(0, 1, 0)),
    radius_bottom(2), radius_top(1)
{}

CappedCone::CappedCone(const Point3& b, const Point3& t, double br, double tr)
    : Object(), bottom(b), top(t), radius_bottom(br), radius_top(tr)
{}

static void compute_uv(IntersectionInfo& info, double dist) {
    info.u = 0.5 + atan2(info.point.x, info.point.y) / (2 * math::pi);
    info.v = -info.point.z / dist;
}

bool CappedCone::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) const {
    Vect axis = this->bottom - this->top;
    Vect ot = ray.origin - this->top;
    Vect ob = ray.origin - this->bottom;

    double dist = axis.square_length();
    double dir = vector::dot(ray.direction, axis);

    double offbot = vector::dot(ob, axis);
    if (offbot > 0 && (ob * dir - ray.direction * offbot).square_length() < radius_bottom * radius_bottom * dir * dir) {
        t_max = -offbot / dir;
        info.normal = axis / std::sqrt(dist);

        info.point = ray.origin + ray.direction * t_max;
        compute_uv(info, dist);
        this->get_properties(info);
        return true;
    }

    double offtop = vector::dot(ot, axis);
    if (offtop < 0 && (ot * dir - ray.direction * offtop).square_length() < radius_top * radius_top * dir * dir) {
        t_max = -offtop / dir;
        info.normal = axis.negative() / std::sqrt(dist);

        info.point = ray.origin + ray.direction * t_max;
        compute_uv(info, dist);
        this->get_properties(info);
        return true;
    }

    double r = radius_top - radius_bottom;
    double h = dist + r * r;

    double a = dist * dist - dir * dir * h;
    double b = dist * dist * vector::dot(ray.direction, ot)
        + dist * radius_top * (r * dir)
        - offtop * dir * h;
    double c = dist * dist * ot.square_length()
        + dist * radius_top * (r * offtop * 2 - dist * radius_top)
        - offtop * offtop * h;

    double discriminant = b * b - a * c;
    if (discriminant < 0) return false;

    c = (-b - std::sqrt(discriminant)) / a;
    a = dir * c + offtop;
    if (a > 0 && a < dist && c > t_min && c < t_max) {
        t_max = c;
        auto n = (ot + ray.direction * c) * dist + axis * r * radius_top;
        info.normal = (n * dist - axis * h * a);

        info.point = ray.origin + ray.direction * t_max;
        compute_uv(info, dist);
        this->get_properties(info);

        return true;
    }

    return false;
}
