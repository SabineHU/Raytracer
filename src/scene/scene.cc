#include "scene.hh"
#include "array.hh"
#include "vector3_op.hh"
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

static Color get_color_shadow(const IntersectionInfo& info, const shared_light light,
        const Vect& light_direction, double cos) {
    Color light_amt = light->get_light_color() * cos * light->get_intensity();
    Color specular_color;
    if (info.specular > 0) {
        Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
        double specular = vector::dot(reflection_ray.direction, light_direction);
        if (specular > 0) {
            specular_color += powf(specular, info.specular) * light->get_intensity();
        }
    }
    return light_amt * info.color * info.kd + specular_color * info.ks;
}

Color Scene::get_color_with_light(const IntersectionInfo& info, double accuracy) const {
    Color res_color;
    for (const auto& light: this->lights) {
        Vect light_direction = light->get_light_position() - info.ray_out.origin;
        Vect light_direction_n = light_direction.normalize();
        float cosine_angle = vector::dot(info.normal, light_direction_n);

        if (cosine_angle > 0) {
            // test for shadows
            double distance_to_light_magnitude = light_direction.magnitude();
            Ray shadow_ray(info.ray_out.origin, light_direction_n);

            if (!this->has_shadow(shadow_ray, distance_to_light_magnitude, accuracy)) {
                res_color += get_color_shadow(info, light, light_direction_n, cosine_angle);
            }
        }
    }
    return res_color;
}
