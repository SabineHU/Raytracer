#pragma once

#include "object.hh"

class TranslatedObject : public Object {
public:
    TranslatedObject() = delete;
    TranslatedObject(shared_object o, const Vect& t);

    /* Methods */
    virtual Vect get_normal_at(const Point3& point, double u, double v) const override;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) override;

private:
    shared_object obj;
    Vect trans;
};
