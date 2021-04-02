#include "rectangle.hh"
#include "vector3_op.hh"

Rectangle::Rectangle()
    : min_point(Vect(0, 0, 0)), max_point(Vect(1, 1, 0)), normal(Vect())
{}

Rectangle::Rectangle(const Vect& u, const Vect& v)
    : min_point(u), max_point(v), normal(Vect())
{}

Vect Rectangle::get_normal_at(const Point3&, double, double) const {
    return normal;
}

bool Rectangle::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    double rectZ = this->min_point.z;

    double t = (rectZ - ray.origin.z) / ray.direction.z;
    Vect hitVector = ray.origin + ray.direction * t;

    bool hit = hitVector.x <= this->max_point.x && hitVector.x >= this->min_point.x &&
        hitVector.y <= this->max_point.y && hitVector.y >= this->min_point.y;

    if (hit && t > t_min && t < t_max) {
        t_max = t;
        info.point = hitVector;
        normal = Vect(0, 0, 1);
        if (vector::dot(ray.direction, normal) > 0)
            normal = normal.negative();
        return true;
    }
    return false;
}

int Rectangle::get_isolevel_at(const Point3&) const {
    // TODO: isolevel
    return 100;
}
