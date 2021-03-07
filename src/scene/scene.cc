#include "scene.hh"
#include "array.hh"
#include "vector3_op.hh"

Scene::Scene(const Vect& look_from, const Vect& look_at)
    : ambient_light(0), objects(std::vector<shared_object>()),
    lights(std::vector<shared_light>())
{
    Vect Y(0,1,0);

    Vect camdir = (look_at - look_from).normalize();
    Vect camright = vector::cross(Y, camdir).normalize();
    Vect camdown = vector::cross(camright, camdir);
    camera = Camera(look_from, camdir, camright, camdown);

}

void Scene::add_object(shared_object obj) {
    this->objects.push_back(obj);
}

void Scene::add_light(shared_light src) {
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

    info.object = this->objects[index];
    info.normal = this->objects[index]->get_normal_at(ray.origin);
    info.color = this->objects[index]->get_color();
    info.distance = intersections[index];
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

Color Scene::get_color_with_light(const Ray& ray, const shared_object& obj,
        const Color& color, double accuracy) const {
    Color res_color(0, 0, 0);

    auto normal = obj->get_normal_at(ray.origin);

    for (const auto& light: this->lights) {

        Vect light_direction = (light->get_light_position() - ray.origin).normalize();
        float cosine_angle = vector::dot(normal, light_direction);

        if (cosine_angle > 0) {
            // test for shadows

            Vect distance_to_light = (light->get_light_position() - ray.origin).normalize();
            float distance_to_light_magnitude = distance_to_light.magnitude();

            Ray shadow_ray(ray.origin, (light->get_light_position() - ray.origin).normalize());

            if (!this->has_shadow(shadow_ray, distance_to_light_magnitude, accuracy)) {
                res_color = res_color + (color * light->get_light_color() * cosine_angle);

                if (obj->specular > 0 && obj->specular <= 1) {
                    // special [0-1]
                    Ray reflection_ray = ray.get_reflection_ray(normal);
                    double specular = vector::dot(reflection_ray.direction, light_direction);
                    if (specular > 0) {
                        // reduce specular to have less luminosity
                        // specular = std::pow(specular, 5);
                        res_color = res_color + light->get_light_color() * specular * obj->specular * light->get_intensity();
                    }
                }

            }
        }
    }
    return res_color;
}

std::vector<double> Scene::get_intersections_distance(const Ray& ray) const {
    std::vector<double> intersections;
    for (const auto& obj : this->objects)
        intersections.push_back(obj->find_intersection(ray));
    return intersections;
}
