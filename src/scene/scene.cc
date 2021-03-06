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

std::vector<double> Scene::get_intersections_distance(const Ray& ray) const {
    std::vector<double> intersections;
    for (const auto& obj : this->objects)
        intersections.push_back(obj->find_intersection(ray));
    return intersections;
}
