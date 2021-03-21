#include "scene.hh"
#include "array.hh"
#include "vector3_op.hh"


Scene::Scene(const Camera& cam)
    : camera(cam), ambient_light(0),
    objects(std::vector<shared_object>()),
    lights(std::vector<shared_light>())
{}

void Scene::add_object(shared_object obj) {
    this->objects.push_back(obj);
}

void Scene::add_light(shared_light src) {
    if (src->get_intensity() == 0)
        return;

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
    std::vector<double> intersections = this->get_intersections_distance(ray);
    int index = array::get_min_index(intersections);

    if (index == -1 || intersections[index] < accuracy)
        return false;

    info.distance = intersections[index];

    info.ray_in = ray;
    info.compute_ray_out(intersections[index]);

    info.texture = this->objects[index]->texture;
    info.normal = this->objects[index]->get_normal_at(info.ray_out.origin);
    info.color = this->objects[index]->texture->get_color(info.ray_out, info.normal);

    return true;
}

bool Scene::has_shadow(const Ray& ray, double distance, double accuracy) const {
    std::vector<double> intersections = this->get_intersections_distance(ray);

    for (auto inters: intersections) {
        if (inters > accuracy && inters <= distance)
            return true;
    }
    return false;
}

static Color get_color_shadow(const IntersectionInfo& info, const shared_light light,
        const Vect& light_direction, double cos) {
    Color res = info.color * light->get_light_color() * cos * light->get_intensity();
    double obj_specular = info.texture->specular;

    if (obj_specular > 0 && obj_specular <= 1) {
        Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
        double specular = vector::dot(reflection_ray.direction, light_direction);
        if (specular > 0) {
            // reduce specular to have less luminosity
            //specular = std::pow(specular, 5);
            res += light->get_light_color() * specular * obj_specular;
        }
    }
    return res;
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

std::vector<double> Scene::get_intersections_distance(const Ray& ray) const {
    std::vector<double> intersections = std::vector<double>();
    for (const auto& obj : this->objects)
        intersections.push_back(obj->find_intersection(ray));
    return intersections;
}
