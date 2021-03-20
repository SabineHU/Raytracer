#pragma once

#include "object.hh"

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

        //
        object = nullptr;
        distance = 0;
    }

    void compute_ray_out(double distance) {
        this->point = ray_in.origin + ray_in.direction * distance;
        this->ray_out = Ray(this->point, ray_in.direction);
    }

    void change_rays() {
        this->ray_in = this->ray_out;
        this->ray_out = Ray();
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

    // TODO: old to remove
    shared_object object;
    double distance;
};
