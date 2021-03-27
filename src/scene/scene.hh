#pragma once

#include <vector>

#include "camera.hh"
#include "object.hh"
#include "light.hh"
#include "intersection.hh"

class Scene {
public:
    Scene() = default;
    Scene(const Camera&);
    Scene(const Camera&, const Color&);

    /* Methods */
    void add_object(shared_object);
    void add_light(shared_light);

    void clear_objects();
    void clear_lights();

    bool has_intersection(const Ray&, IntersectionInfo&, double) const;
    bool has_shadow(const Ray&, double, double) const;

    /* Getters */
    std::vector<shared_light> get_lights() const { return lights; }

public:
    /* Attributes */
    Camera camera;
    Color ambient_light;
    std::vector<shared_object> objects;
    std::vector<shared_light> lights;
};
