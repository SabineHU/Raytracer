#pragma once

#include <memory>

#include "ray.hh"
#include "vector3.hh"
#include "intersection.hh"
#include "texture_material.hh"
#include "lambertian.hh"

class Object {
public:
    Object() = default;
    Object(shared_texture t) : texture(t), specular(0) {}
    Object(shared_texture t, double s) : texture(t), specular(s) {}

    /* Methods */
    virtual Vect get_normal_at(const Point3& point) const = 0;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) = 0;
    virtual int get_isolevel_at(const Point3&) const = 0;

    Color get_color_at(const Point3& point, double u, double v) const {
        return this->texture->get_color(point, u, v);
    }

    /* Setters */
    void set_specular(double s) { specular = s; }
    void set_texture(shared_texture t) { texture = t; }
    void set_color(const Color& c) { texture = std::make_shared<Lambertian>(c); }

    shared_texture get_texture() const { return texture; }

    double specular;
    /* Attributes */
protected:
    shared_texture texture;
};

using shared_object = std::shared_ptr<Object>;
