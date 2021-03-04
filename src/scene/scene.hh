#pragma once

#include <vector>

#include "camera.hh"
#include "object.hh"
#include "source.hh"

class Scene {
public:
    Scene() = default;
    Scene(const Vect& look_from, const Vect& look_at);

    void add_object(shared_object& obj);
    void add_light(shared_light& src);

    void clear_objects();
    void clear_lights();

    Camera camera;
    double ambient_light;
    std::vector<shared_object> objects;
    std::vector<shared_light> sources;
};
