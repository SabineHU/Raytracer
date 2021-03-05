#include "init.hh"

Scene init_scene() {
    /* Camera */
    Vect look_from(3, 1.5, -4);
    Vect look_at(0, 0, 0);

    /* Scene */
    Scene scene(look_from, look_at);
    scene.ambient_light = 0.2;

    /* Lights */
    Color white(1, 1, 1, 0);
    scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), white));

    /* Objects */
    Color color1(0.5, 1, 0.5, 0.3);
    Color color2(0.5, 0.25, 0.25, 0);
    Color color3(1, 1, 1, 2);
    scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, color1));
    scene.add_object(std::make_shared<Sphere>(Point3(1.74, -0.25, 0), 0.5, color2));
    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, color3));

    return scene;
}