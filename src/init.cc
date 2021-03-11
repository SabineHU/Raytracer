#include "init.hh"
#include "unique.hh"
#include "metal.hh"
#include "checkerboard.hh"

#include "sphere.hh"
#include "cone.hh"
#include "plane.hh"
#include "triangle.hh"
#include "light.hh"

Scene init_scene() {
    /* Camera */
    Vect look_from(3, 1.5, -4);
    Vect look_at(0, 0, 0);
    Vect vup(0,1,0);
    Camera cam(look_from, look_at, vup);

    //    point3(-2,2,1), point3(0,0,-1), vec3(0,1,0)

    /* Scene */
    Scene scene(cam);
    scene.ambient_light = 0.2;

    /* Colors */
    Color white(1, 1, 1);
    Color red(1, 0, 0);
    Color green(0, 1, 0);
    Color blue(0, 0, 1);
    Color black(0, 0, 0);
    Color purple(0.6, 0, 0.6);

    Color green2(0.5, 1, 0.5);
    Color red2(0.5, 0.25, 0.25);
    Color color3(1, 1, 1);

    /* Lights */
    scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), white, 2.5));

    /* Textures */

    //auto texture = std::make_shared<Unique>(white);
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto board_black_blue = std::make_shared<CheckerBoard>(black, blue, 0.3);
    auto unique_green = std::make_shared<Unique>(green2, 0.05);
    auto unique_red = std::make_shared<Metal>(red2);

    /* Objects */
    scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, board_black_blue));
    //scene.add_object(std::make_shared<Cone>(Point3(1.75, -1, 0), 1, 2.5, unique_green));
    scene.add_object(std::make_shared<Triangle>(Point3(3, 0, 0), Point3(0, 3, 0), Point3(0, 0, 3), purple));
    scene.add_object(std::make_shared<Sphere>(Point3(1.75, 0.25, 0), 0.5, unique_green));
    scene.add_object(std::make_shared<Sphere>(Point3(-1.75, -0.25, 0), 0.5, unique_red));
    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));

    return scene;
}
