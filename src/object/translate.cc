#include "translate.hh"

TranslatedObject::TranslatedObject(shared_object o, const Vect& t)
    : obj(o), trans(t)
{}

Vect TranslatedObject::get_normal_at(const Point3& point, double u, double v) const {
    return this->obj->get_normal_at(point, u, v);
}

bool TranslatedObject::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    auto orig = ray.origin - this->trans;
    if (!this->obj->find_intersection(Ray(orig, ray.direction), t_min, t_max, info))
        return false;

    info.point += this->trans;

    return true;
}

int TranslatedObject::get_isolevel_at(const Point3&) const {
    // TODO: isolevel
    return 100;
}
