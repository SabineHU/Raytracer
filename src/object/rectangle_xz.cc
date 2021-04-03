#include "rectangle_xz.hh"
#include "vector3_op.hh"

Rectangle_xz::Rectangle_xz()
    : p1(Vect(0, 0, 0)), p2(Vect(1, 1, 0)), normal(Vect())
{}

Rectangle_xz::Rectangle_xz(const Vect& u, const Vect& v)
    : p1(u), p2(v), normal(Vect())
{}

Vect Rectangle_xz::get_normal_at(const Point3&, double, double) const {
    return normal;
}

bool Rectangle_xz::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    double t = (this->p1.y - ray.origin.y) / ray.direction.y;
    if (t <= t_min || t >= t_max) return false;

    Vect p = ray.origin + ray.direction * t;
    bool hit = p.x <= this->p2.x && p.x >= this->p1.x &&
        p.z <= this->p2.z && p.z >= this->p1.z;

    if (hit) {
        t_max = t;
        info.point = p;
        normal = Vect(0, 1, 0);
        if (vector::dot(ray.direction, normal) > 0)
            normal = normal.negative();

        info.u = (p.x - p1.x) / (p2.x - p1.x);
        info.v = (p.z - p1.z) / (p2.z - p1.z);
        return true;
    }
    return false;
}

int Rectangle_xz::get_isolevel_at(const Point3&) const {
    // TODO: isolevel
    return 100;
}