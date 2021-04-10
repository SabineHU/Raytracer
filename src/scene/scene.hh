#pragma once

#include <vector>
#include <string>

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
    Color get_fog_color(const Color&, double) const;

    /* Getters */
    std::vector<shared_light> get_lights() const { return lights; }
    Color get_background_color(const Ray& ray) const;

    /* Setters */
    void set_camera(const Camera& c) { camera = c; }
    void set_background_colors(const Color& c1, const Color& c2) {
        background_color1 = c1;
        background_color2 = c2;
    }
    void set_fog(double d, std::string type = "exp") { fog = std::make_pair(d, type); }
    void set_objects(std::vector<shared_object> objs) {
        this->objects = objs;
    }
    void set_lights(std::vector<shared_light> l) {
        this->lights = l;
    }
    void set_ambient_light(Color color) {
        this->ambient_light = color;
    }

public:
    /* Attributes */
    Camera camera;
    Color ambient_light;
    std::vector<shared_object> objects;
    std::vector<shared_light> lights;

    Color background_color1;
    Color background_color2;

    std::optional<std::pair<double, std::string>> fog;
};
