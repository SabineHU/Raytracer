#pragma once

#include "ray.hh"
#include "texture_material.hh"

class IntersectionInfo {
public:
    IntersectionInfo() = default;

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

    /* Object operators */
    double t_min;
    double t_max;
};
