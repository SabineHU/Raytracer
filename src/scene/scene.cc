#include "scene.hh"


Scene::Scene(const Vect& look_from, const Vect& look_at)
    : ambient_light(0), objects(std::vector<shared_object>()),
    sources(std::vector<shared_light>())
{
    Vect Y(0,1,0);

    Vect camdir = (look_at - look_from).normalize();
    Vect camright = Y.crossProduct(camdir).normalize();
    Vect camdown = camright.crossProduct(camdir);
    camera = Camera(look_from, camdir, camright, camdown);

}

void Scene::add_object(shared_object& obj) {
    this->objects.push_back(obj);
}

void Scene::add_light(shared_light& src) {
    this->sources.push_back(src);
}

void Scene::clear_objects() {
    this->objects.clear();
}
void Scene::clear_lights() {
    this->sources.clear();
}
