#include "init.hh"
#include "unique.hh"
#include "metal.hh"
#include "checkerboard.hh"

#include "sphere.hh"
#include "cone.hh"
#include "plane.hh"
#include "triangle.hh"
#include "light.hh"
#include "color.hh"

Camera init_camera() {
    /* Camera */
    //    point3(-2,2,1), point3(0,0,-1), vec3(0,1,0)
    //Vect look_from(3, 1.5, -4);
    Vect look_from(1.5, 2, -4);
    Vect look_at(0, 0, 0);
    Vect vup(0,1,0);
    return Camera(look_from, look_at, vup);
}

Scene init_scene(Camera& cam) {

    /* Scene */
    Scene scene(cam);
    scene.ambient_light = 0.2;

    /* Lights */
    scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), white, 2.5));

    //scene.add_light(std::make_shared<Light>(Point3(7, 10, -10), green, 1.5));
    //scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), red, 1.5));

    /* Textures */
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto board_black_blue = std::make_shared<CheckerBoard>(black, blue, 0.3);
    auto unique_green = std::make_shared<Unique>(light_green, 0.05);
    auto unique_red = std::make_shared<Metal>(dark_red);

    /* Objects */
    scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, board_black_blue));
    //scene.add_object(std::make_shared<Cone>(Point3(1.75, -1, 0), 1, 2.5, unique_green));
    scene.add_object(std::make_shared<Triangle>(Point3(3, 0, 0), Point3(0, 3, 0), Point3(0, 0, 3), purple));
    scene.add_object(std::make_shared<Sphere>(Point3(1.75, 0.25, 0), 0.5, unique_green));
    scene.add_object(std::make_shared<Sphere>(Point3(-1.75, -0.25, 0), 0.5, unique_red));
    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));

    return scene;
}
