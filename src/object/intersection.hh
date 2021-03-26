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
    Point3 uv;

    /* Properties */
    double ka;
    double kd;
    double ks;
};
