#include "scene.hh"
#include "math.hh"
#include "vector3_op.hh"

Scene::Scene(const Camera& cam)
    : camera(cam), ambient_light(Color(1, 1, 1)),
    objects(std::vector<shared_object>()),
    lights(std::vector<shared_light>()),
    background_color1(Color(1, 1, 1)),
    background_color2(Color(.4, .65, 1))
{}

Scene::Scene(const Camera& cam, const Color& light)
    : camera(cam), ambient_light(light),
    objects(std::vector<shared_object>()),
    lights(std::vector<shared_light>()),
    background_color1(Color(1, 1, 1)),
    background_color2(Color(.4, .65, 1))
{}

void Scene::add_object(shared_object obj) {
    this->objects.push_back(obj);
}

void Scene::add_light(shared_light src) {
    if (src->get_intensity() == 0) return;
    this->lights.push_back(src);
}

void Scene::clear_objects() {
    this->objects.clear();
}
void Scene::clear_lights() {
    this->lights.clear();
}

bool Scene::has_intersection(const Ray& ray, IntersectionInfo& info, double accuracy) const {
    double distance = math::inf;
    shared_object closest_obj = nullptr;
    for (const auto& obj : this->objects) {
        if (obj->find_intersection(ray, accuracy, distance, info))
            closest_obj = obj;
    }

    if (closest_obj == nullptr) return false;

    info.dist = distance;
    info.ray_in = ray;
    info.ray_out = Ray(info.point, ray.direction);

    if (vector::dot(info.normal, ray.direction) < 0)
        info.normal = info.normal.negative();

    return true;
}

bool Scene::has_shadow(const Ray& ray, double distance, double accuracy) const {
    IntersectionInfo info;
    for (const auto& obj : this->objects)
        if (obj->find_intersection(ray, accuracy, distance, info))
            return true;

    return false;
}

Color Scene::get_background_color(const Ray& ray) const {
    if (!this->fog.has_value()) {
        double s = 0.5 * (ray.direction.y + 1.0);
        return background_color1 * (1 - s) + background_color2 * s;
    }

    return Color(1, 1, 1);
}

Color Scene::get_fog_color(const Color& color, double dist) const {
    if (!this->fog.has_value())
        return color;

    double ratio = dist / this->fog.value().first;

    FogType type = this->fog.value().second;
    switch (type) {
    case LINEAR:
        return Color(1, 1, 1) * ratio + color * (1 - ratio);

    case EXP:
        ratio = exp(-ratio);
        return Color(1, 1, 1) * (1 - ratio) + color * ratio;

    default:
        ratio = exp(-ratio * ratio);
        return Color(1, 1, 1) * (1 - ratio) + color * ratio;

    }
}
