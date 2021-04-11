#pragma once

#include "ray.hh"
#include "texture_material.hh"

class IntersectionInfo {
public:
    IntersectionInfo() = default;

    IntersectionInfo operator=(const IntersectionInfo& info) {
        dist        = info.dist;
        point       = info.point;
        ray_in      = info.ray_in;
        ray_out     = info.ray_out;
        normal      = info.normal;
        color       = info.color;
        texture     = info.texture;
        u           = info.u;
        v           = info.v;
        ka          = info.ka;
        kd          = info.kd;
        ks          = info.ks;
        kt          = info.kt;
        specular    = info.specular;
        attenuation = info.attenuation;
        ior         = info.ior;
        t_min       = info.t_min;
        t_max       = info.t_max;
        return *this;
    }

    /* Intersection point and distance */
    double dist;
    Point3 point;

    /* Rays */
    Ray ray_in;
    Ray ray_out;

    /* Object */
    Vect normal;
    Color color;
    shared_texture texture;

    /* Textures coordinates */
    double u, v;

    /* Properties */
    double ka;
    double kd;
    double ks;
    double kt;
    double specular;
    double attenuation;
    double ior;

    /* Object operators */
    double t_min;
    double t_max;
};
