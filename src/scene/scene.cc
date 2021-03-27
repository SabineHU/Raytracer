#include "scene.hh"
#include "math.hh"

Scene::Scene(const Camera& cam)
    : camera(cam), ambient_light(Color(1, 1, 1)),
    objects(std::vector<shared_object>()),
    lights(std::vector<shared_light>())
{}

Scene::Scene(const Camera& cam, const Color& light)
    : camera(cam), ambient_light(light),
    objects(std::vector<shared_object>()),
    lights(std::vector<shared_light>())
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

bool Scene::has_intersection(const Ray& ray, IntersectionInfo& info,
        double accuracy) const {

    double distance = math::inf;
    shared_object closest_obj = nullptr;
    for (const auto& obj : this->objects) {
        if (obj->find_intersection(ray, accuracy, distance, info))
            closest_obj = obj;
    }

    if (closest_obj == nullptr) return false;

    info.ray_in = ray;

    info.point = ray.origin + ray.direction * distance;
    info.normal = closest_obj->get_normal_at(info.point);

    info.ray_out = Ray(info.point, ray.direction);
    info.texture = closest_obj->texture;
    info.color = closest_obj->texture->get_color(info.point, info.u, info.v);

    info.ka = closest_obj->texture->ka;
    info.kd = closest_obj->texture->kd;
    info.ks = closest_obj->texture->ks;

    info.specular = closest_obj->specular;

    return true;
}

bool Scene::has_shadow(const Ray& ray, double distance, double accuracy) const {
    IntersectionInfo info;
    for (const auto& obj : this->objects)
        if (obj->find_intersection(ray, accuracy, distance, info))
            return true;
    return false;
}
