#include "init.hh"
#include "unique.hh"
#include "metal.hh"
#include "checkerboard.hh"

#include "object.hh"
#include "sphere.hh"
#include "cone.hh"
#include "plane.hh"
#include "triangle.hh"
#include "smooth_triangle.hh"

#include "light.hh"
#include "color.hh"

#include "blob.hh"

Camera init_camera() {
    /* Camera */
    Vect look_from(1.5, 3, -8);
    //Vect look_from(3, 1.5, -4);
    //Vect look_from(1.5, 2, -4);
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

    /* Textures */
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto board_black_blue = std::make_shared<CheckerBoard>(black, blue, 0.3);
    auto unique_green = std::make_shared<Unique>(light_green, 0.05);
    auto unique_red = std::make_shared<Metal>(dark_red);

    /* Objects */
    scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, board_black_blue));
    //scene.add_object(std::make_shared<Cone>(Point3(1.75, -1, 0), 1, 2.5, unique_green));
    //scene.add_object(std::make_shared<Triangle>(Point3(3, 0, 0), Point3(0, 3, 0), Point3(0, 0, 3), purple));
    scene.add_object(std::make_shared<Sphere>(Point3(2, 0, 0), 1, unique_green));
    scene.add_object(std::make_shared<Sphere>(Point3(-2, 0, 0), 1, unique_red));

    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));

    return scene;
}

Scene init_scene2(Camera& cam) {
    Scene scene(cam);
    scene.ambient_light = 0.2;

    /* Textures */
    auto board_black_blue = std::make_shared<CheckerBoard>(black, blue, 0.3);
    auto unique_green = std::make_shared<Unique>(light_green, 0.05);
    auto unique_red = std::make_shared<Metal>(dark_red);

    /* Lights */
    scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), white, 2.5));

    /* Scene objects */
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));

    /* Add blob objects */
    std::vector<shared_object> blob_objects;
    blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 0.5, 0), 1, light_blue));
    blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 2, 0), 0.5, light_blue));
    Blob blob(Point3(0, 0, 0), 6, 0.5, 80, blob_objects, true);

    blob.compute();

    for (auto& triangle: blob.get_triangles()) {
        scene.add_object(std::make_shared<SmoothTriangle>(triangle));
    }

    /* Add scene objects */
    //scene.add_object(std::make_shared<Sphere>(Point3(0.5, 0, 0), 1, light_blue));
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, orange));
    scene.add_object(std::make_shared<Cone>(Point3(-7, -1, 1), 1, 2.5, unique_green));
    scene.add_object(std::make_shared<Sphere>(Point3(-5, 0, 2), 1, board_black_blue));
    scene.add_object(std::make_shared<Sphere>(Point3(5, 0, 0), 1, unique_green));
    scene.add_object(std::make_shared<Sphere>(Point3(-2, 0.5, -5), 1, unique_red));

    return scene;
}
