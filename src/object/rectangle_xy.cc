#include "rectangle_xy.hh"
#include "vector3_op.hh"

Rectangle_xy::Rectangle_xy()
    : p1(Vect(0, 0, 0)), p2(Vect(1, 1, 0)), normal(Vect())
{}

Rectangle_xy::Rectangle_xy(const Vect& u, const Vect& v)
    : p1(u), p2(v), normal(Vect())
{}

Vect Rectangle_xy::get_normal_at(const Point3&, double, double) const {
    return normal;
}

bool Rectangle_xy::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    double t = (this->p1.z - ray.origin.z) / ray.direction.z;
    if (t <= t_min || t >= t_max) return false;

    Vect p = ray.origin + ray.direction * t;
    bool hit = p.x <= this->p2.x && p.x >= this->p1.x &&
        p.y <= this->p2.y && p.y >= this->p1.y;

    if (hit) {
        t_max = t;
        info.point = p;
        normal = Vect(0, 0, 1);
        if (vector::dot(ray.direction, normal) > 0)
            normal = normal.negative();

        info.u = (p.x - p1.x) / (p2.x - p1.x);
        info.v = (p.y - p1.y) / (p2.y - p1.y);

        return true;
    }

    return false;
}

int Rectangle_xy::get_isolevel_at(const Point3&) const {
    // TODO: isolevel
    return 100;
}
