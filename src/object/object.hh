#pragma once

#include <memory>

#include "ray.hh"
#include "vector3.hh"
#include "intersection.hh"
#include "texture_material.hh"

class Object {
public:
    Object() = default;
    Object(shared_texture t) : texture(t), ka(0.5), kd(0.5), ks(0.5) {}

    /* Methods */
    virtual Vect get_normal_at(const Vect& point) const = 0;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) = 0;
    //virtual bool find_intersection2(const Ray& ray, double& t_max) = 0;

    virtual int get_isolevel_at(const Point3&) const = 0;

    /* Attributes */
    shared_texture texture;

    double ka;
    double kd;
    double ks;
};


using shared_object = std::shared_ptr<Object>;
