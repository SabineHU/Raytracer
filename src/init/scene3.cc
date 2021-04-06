#include "scene3.hh"

#include "point_light.hh"
#include "color.hh"

#include "CSG.hh"
#include "plane.hh"
#include "cube.hh"
#include "cylinder.hh"
#include "rectangle_xy.hh"
#include "rectangle_xz.hh"
#include "rectangle_yz.hh"
#include "rotate.hh"

#include "checkerboard.hh"
#include "lambertian.hh"
#include "random.hh"

static Camera init_camera() {
    Vect look_from(0, 10, -.000001);
    //Vect look_from(0, 0, -10);
    //Vect look_from(0, 2, -6);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

static void add_plane(Scene& scene) {
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(board_black_white);
    scene.add_object(plane);
}

Scene init_scene3() {
    Camera cam = init_camera();

    Scene scene(cam, Color(.5, .5, .5));
    init_lights(scene);

    add_plane(scene);

    return scene;
}
