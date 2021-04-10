#pragma once

#include <memory>
#include <optional>
#include <map>

#include <iostream>

#include "ray.hh"
#include "vector3.hh"
#include "intersection.hh"
#include "texture_material.hh"
#include "lambertian.hh"
#include "noise.hh"

class Object {
public:
    Object() : texture(std::make_shared<Lambertian>(Color(.5, .5, .5))),
        displacement(std::nullopt), specular(0), depth(5) {}

    Object(shared_texture t) : texture(t), displacement(std::nullopt), specular(0), depth(5) {}
    Object(shared_texture t, double s) : texture(t), displacement(std::nullopt), specular(s), depth(5) {}

    /* Methods */
    virtual Vect get_normal_at(const Point3& point, double u, double v) const = 0;
    virtual bool find_intersection(const Ray& ray, double& t_min, double& t_max, IntersectionInfo& info) = 0;
    virtual int get_isolevel_at(const Point3&) const = 0;

    virtual Color get_color_at(const Point3& point, double u, double v) const {
        return this->texture->get_color(point, u, v);
    }

    virtual void get_properties(IntersectionInfo& info) const {
        info.color = this->get_color_at(info.point, info.u, info.v);
        info.normal = this->get_normal_at(info.point, info.u, info.v);

        info.specular = this->specular;
        info.texture = this->texture;
        info.ka = this->texture->ka;
        info.kd = this->texture->kd;
        info.ks = this->texture->ks;
        info.kt = this->texture->kt;
        info.attenuation = this->texture->attenuation;
        info.ior = this->ior;
    }

    virtual Vect get_displacement_at(const Point3& point, double u, double v) const {
        if (!this->displacement.has_value()) return Vect();

        auto color = this->displacement.value().first->get_color(point, u, v);
        auto noise = this->displacement.value().second;

        auto x0 = Vect(point.x - e, point.y, point.z);
        auto x1 = Vect(point.x + e, point.y, point.z);
        auto y0 = Vect(point.x, point.y - e, point.z);
        auto y1 = Vect(point.x, point.y + e, point.z);
        auto z0 = Vect(point.x, point.y, point.z - e);
        auto z1 = Vect(point.x, point.y, point.z + e);

        auto x = (noise.compute(x0, depth) - noise.compute(x1, depth)) * color.x;
        auto y = (noise.compute(y0, depth) - noise.compute(y1, depth)) * color.y;
        auto z = (noise.compute(z0, depth) - noise.compute(z1, depth)) * color.z;
        return Vect(x, y, z);
    }

    // TODO, set it as virtual -> CSG
    Vect get_bump_at(const Point3& p) const {
        if (bumps.empty()) return Vect(0, 0, 0);

        auto x0 = Vect(p.x - e, p.y, p.z);
        auto x1 = Vect(p.x + e, p.y, p.z);
        auto y0 = Vect(p.x, p.y - e, p.z);
        auto y1 = Vect(p.x, p.y + e, p.z);
        auto z0 = Vect(p.x, p.y, p.z - e);
        auto z1 = Vect(p.x, p.y, p.z + e);
        double x = 0, y = 0, z = 0;
        for (auto const& [noise, coeff] : bumps) {
            x += (noise.compute(x0, depth)
                - noise.compute(x1, depth)) * coeff;

            y += (noise.compute(y0, depth)
                - noise.compute(y1, depth)) * coeff;

            z += (noise.compute(z0, depth)
                - noise.compute(z1, depth)) * coeff;
        }
        double size = bumps.size();
        return Vect(x / size, y / size, z / size);
    }

    void add_bump_mapping(const Noise n, double coeff = 1) { bumps.insert(std::pair<Noise, double>(n, coeff)); }

    /* Setters */
    void set_specular(double s) { specular = s; }
    void set_texture(shared_texture t) { texture = t; }
    void set_texture(const Color& c) { texture = std::make_shared<Lambertian>(c); }
    void set_depth(int d) { depth = d; }
    void set_displacement_image(shared_texture d) {
        displacement = std::make_pair(d, Noise(NOISE, 10));
    }
    void set_ior(double i) { ior = i; }

    /* Getters */
    virtual shared_texture get_texture() const { return texture; }
    double get_specular() const { return specular; }

protected:
    /* Attributes */
    shared_texture texture;
    std::map<Noise, double> bumps;
    std::optional<std::pair<shared_texture, Noise>> displacement;

    double specular;

    int depth;
    double e = 0.01;
    double ior = 1;
};

using shared_object = std::shared_ptr<Object>;
