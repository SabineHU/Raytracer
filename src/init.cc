#include "init.hh"
#include "unique.hh"
#include "checkerboard.hh"

Scene init_scene() {
    /* Camera */
    Vect look_from(3, 1.5, -4);
    Vect look_at(0, 0, 0);

    /* Scene */
    Scene scene(look_from, look_at);
    scene.ambient_light = 0.2;

    /* Colors */
    Color white(1, 1, 1, 0);
    Color red(1, 0, 0, 0);
    Color green(0, 1, 0, 0);
    Color blue(0, 0, 1, 0);
    Color black(0, 0, 0, 0);

    Color green2(0.5, 1, 0.5, 0);
    Color red2(0.5, 0.25, 0.25, 0);
    Color color3(1, 1, 1, 0);

    /* Lights */
    scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), white, 2.5));

    /* Textures */

    //auto texture = std::make_shared<Unique>(white);
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto board_black_blue = std::make_shared<CheckerBoard>(black, blue);
    auto unique_green = std::make_shared<Unique>(green2);
    auto unique_red = std::make_shared<Unique>(red2);

    /* Objects */
    scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, board_black_blue, 0.3));
    scene.add_object(std::make_shared<Sphere>(Point3(1.75, -0.25, 0), 0.5, unique_green));
    scene.add_object(std::make_shared<Sphere>(Point3(-1.75, -0.25, 0), 0.5, unique_red));
    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));

    return scene;
}
