#pragma once

#include <memory>
#include <optional>

#include "ray.hh"
#include "vector3.hh"
#include "intersection.hh"
#include "texture_material.hh"
#include "lambertian.hh"
#include "noise.hh"

class Object {
public:
    Object() : texture(std::make_shared<Lambertian>(Color(.5, .5, .5))),
        bump(std::nullopt), specular(0), scale(5), depth(5) {}

    Object(shared_texture t) : texture(t), bump(std::nullopt), specular(0),
        scale(5), depth(5) {}
    Object(shared_texture t, double s) : texture(t), bump(std::nullopt),
        specular(s), scale(5), depth(5) {}

    /* Methods */
    virtual Vect get_normal_at(const Point3& point, double u, double v) const = 0;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) = 0;
    virtual int get_isolevel_at(const Point3&) const = 0;

    virtual Color get_color_at(const Point3& point, double u, double v) const {
        return this->texture->get_color(point, u, v);
    }

    virtual void get_properties(IntersectionInfo& info) const {
        info.specular = this->specular;
        info.texture = this->texture;
        info.ka = this->texture->ka;
        info.kd = this->texture->kd;
        info.ks = this->texture->ks;
        info.kt = this->texture->kt;
    }

    Vect get_bump_at(const Point3& p) const {
        if (bump.has_value()) {
            auto x0 = Vect(p.x - e, p.y, p.z);
            auto x1 = Vect(p.x + e, p.y, p.z);
            auto x = bump.value().compute(x0, scale, depth)
                - bump.value().compute(x1, scale, depth);

            auto y0 = Vect(p.x, p.y - e, p.z);
            auto y1 = Vect(p.x, p.y + e, p.z);
            auto y = bump.value().compute(y0, scale, depth)
                - bump.value().compute(y1, scale, depth);

            auto z0 = Vect(p.x, p.y, p.z - e);
            auto z1 = Vect(p.x, p.y, p.z + e);
            auto z = bump.value().compute(z0, scale, depth)
                - bump.value().compute(z1, scale, depth);

            return Vect(x, y, z);
        }
        return Vect(0, 0, 0);
    }

    /* Setters */
    void set_specular(double s) { specular = s; }
    void set_texture(shared_texture t) { texture = t; }
    void set_texture(const Color& c) { texture = std::make_shared<Lambertian>(c); }
    void set_bump_mapping(const Noise n) { bump = n; }
    void set_scale(double s) { scale = s; }
    void set_depth(int d) { depth = d; }

    /* Getters */
    virtual shared_texture get_texture() const { return texture; }
    double get_specular() const { return specular; }

protected:
    /* Attributes */
    shared_texture texture;
    std::optional<Noise> bump;
    double specular;

    double scale;
    int depth;
    double e = 0.01;
};

using shared_object = std::shared_ptr<Object>;
