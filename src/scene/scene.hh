#pragma once

#include <vector>

#include "camera.hh"
#include "object.hh"
#include "source.hh"
#include "intersection.hh"

class Scene {
public:
    Scene() = default;
    Scene(const Camera&);

    /* Methods */
    void add_object(shared_object);
    void add_light(shared_light);

    void clear_objects();
    void clear_lights();

    bool has_intersection(const Ray&, IntersectionInfo&, double) const;
    bool has_shadow(const Ray&, double, double) const;
    Color get_color_with_light(const Ray&, const shared_object&, const Color&,
            double) const;

private:
    std::vector<double> get_intersections_distance(const Ray&) const;

public:
    /* Attributes */
    Camera camera;
    double ambient_light;
    std::vector<shared_object> objects;
    std::vector<shared_light> lights;
};
