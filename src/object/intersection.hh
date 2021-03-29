#pragma once

#include "ray.hh"
#include "texture_material.hh"

class IntersectionInfo {
public:
    IntersectionInfo() = default;

    IntersectionInfo(const Ray& in) {
        point = Point3();
        ray_in = in;
        ray_out = Ray();
        normal = Vect();
        color = Color();
        texture = nullptr;
        barycenter = Point3();
        ka = 1;
        kd = 1;
        ks = 1;
        u = 0;
        v = 0;
        specular = 0;
    }

    /* Intersection point */
    Point3 point;

    /* Rays */
    Ray ray_in;
    Ray ray_out;

    /* Object */
    Vect normal;
    Color color;
    shared_texture texture;

    /* Triangle */
    Point3 barycenter;

    /* Textures coordinates */
    double u, v;

    /* Properties */
    double ka;
    double kd;
    double ks;
    double kt;
    double specular;

    /* Object operators */
    double t_min;
    double t_max;
};
