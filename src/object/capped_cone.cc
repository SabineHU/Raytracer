#include "capped_cone.hh"
#include "unique.hh"
#include "vector3_op.hh"

CappedCone::CappedCone()
    : bottom(Point3(0, 0, 0)), top(Point3(0, 1, 0)),
    radius_bottom(2), radius_top(1), normal(Vect())
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

CappedCone::CappedCone(const Point3& b, const Point3& t, double br, double tr)
    : bottom(b), top(t), radius_bottom(br), radius_top(tr), normal(Vect())
{
    auto color = Color(0.5, 0.5, 0.5);
    texture = std::make_shared<Unique>(color);
}

CappedCone::CappedCone(const Point3& b, const Point3& t, double br, double tr, shared_texture s)
    : Object(s), bottom(b), top(t), radius_bottom(br), radius_top(tr), normal(Vect())
{}

CappedCone::CappedCone(const Point3& b, const Point3& t, double br, double tr, const Color& c)
    : Object(std::make_shared<Unique>(c)), bottom(b), top(t), radius_bottom(br), radius_top(tr), normal(Vect())
{}

Vect CappedCone::get_normal_at(const Vect&) const {
    return normal;
}

static bool intersection_top_bot(const Vect& ot, const Vect& raydir,
        double radius, double off, double dir, double& t_min, double& t_max) {
    auto t = -off / dir;
    auto r = radius * radius * dir * dir;
    if (t > t_min && t < t_max && (ot * dir - raydir * off).square_length() < r) {
        t_max = t;
        return true;
    }
    return false;

}

bool CappedCone::find_intersection(const Ray& ray, double& t_min, double& t_max) {
    Vect axis = this->bottom - this->top;
    Vect ot = ray.origin - this->top;
    Vect ob = ray.origin - this->bottom;

    double dist = axis.square_length();
    double offtop = vector::dot(ot, axis);
    double offbot = vector::dot(ob, axis);
    double dir = vector::dot(ray.direction, axis);
    double t;

    if (offtop < 0) {
        if (intersection_top_bot(ot, ray.direction, radius_top, offtop, dir,
                    t_min, t_max)) {
            this->normal = axis * - 1 / std::sqrt(dist);
            return true;
        }
    } else if (offbot > 0) {
        if (intersection_top_bot(ot, ray.direction, radius_bottom, offbot, dir,
                    t_min, t_max)) {
            this->normal = axis / std::sqrt(dist);
            return true;
        }
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

    t = (-b - std::sqrt(discriminant)) / a;

    double y = dir * t + offtop;
    if (y > 0 && y < dist && t > t_min && t < t_max)
    {
        t_max = t;
        auto n = (ot + ray.direction * t) * dist + axis * r * radius_top;
        this->normal = (n * dist - axis * h * y).normalize();
        return true;
    }

    return false;
}

int CappedCone::get_isolevel_at(const Point3&) const {
    // TODO
    return 100;
}