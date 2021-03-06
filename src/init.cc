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

    /* Lights */
    scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), white));

    /* Textures */

    //auto texture = std::make_shared<Unique>(white);
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);

    /* Objects */
    Color color1(0.5, 1, 0.5, 0.3);
    Color color2(0.5, 0.25, 0.25, 0);
    Color color3(1, 1, 1, 2);
    scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, color1));
    scene.add_object(std::make_shared<Sphere>(Point3(1.75, -0.25, 0), 0.5, color2));
    scene.add_object(std::make_shared<Sphere>(Point3(-1.75, -0.25, 0), 0.5, color2));
    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, color3, board_black_white));

    return scene;
}
