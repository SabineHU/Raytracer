#include "translate.hh"

TranslatedObject::TranslatedObject(shared_object o, const Vect& t)
    : obj(o), trans(t)
{}

bool TranslatedObject::find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) {
    auto orig = ray.origin - this->trans;
    if (!this->obj->find_intersection(Ray(orig, ray.direction), t_min, t_max, info))
        return false;

    info.point += this->trans;

    return true;
}
