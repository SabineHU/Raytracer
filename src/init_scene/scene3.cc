#include "scene3.hh"

#include "point_light.hh"
#include "color.hh"

#include "plane.hh"
#include "rectangle_xy.hh"
#include "rectangle_xz.hh"
#include "rectangle_yz.hh"
#include "rotate.hh"

#include "checkerboard.hh"
#include "lambertian.hh"
#include "random_color.hh"

static Camera init_camera() {
    Vect look_from(0, 2, -8);
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

static shared_object create_rectangle_xy(const Point3& p1, const Point3& p2, shared_texture t) {
    auto obj1 = std::make_shared<Rectangle_xy>(p1, p2);
    obj1->set_texture(t);
    return obj1;
}

static shared_object create_rectangle_yz(const Point3& p1, const Point3& p2, shared_texture t) {
    auto obj1 = std::make_shared<Rectangle_yz>(p1, p2);
    obj1->set_texture(t);
    return obj1;
}

static void add_table_leg(Scene& scene, shared_texture t, double x1, double x2, double z1, double z2) {
    scene.add_object(create_rectangle_xy(Point3(x1, -1, z1), Point3(x2, .5, z1), t));
    scene.add_object(create_rectangle_xy(Point3(x1, -1, z2), Point3(x2, .5, z2), t));

    scene.add_object(create_rectangle_yz(Point3(x1, -1, z1), Point3(x1, .5, z2), t));
    scene.add_object(create_rectangle_yz(Point3(x2, -1, z1), Point3(x2, .5, z2), t));
}

static void add_table_legs(Scene& scene, shared_texture t) {
    add_table_leg(scene, t, -1.75      , -1.5     , -2.75    , -2.5);
    add_table_leg(scene, t, -1.75      , -1.5     , -2.75 + 3, -2.5 + 3);
    add_table_leg(scene, t, -1.75 + 4  , -1.5 + 4 , -2.75 + 3, -2.5 + 3);
    add_table_leg(scene, t, -1.75 + 4  , -1.5 + 4 , -2.75    , -2.5);

    auto obj = std::make_shared<Rectangle_xz>(Point3(-2, .5, -3), Point3(-1.25 + 4, .5, -2.25 + 3));
    obj->set_texture(t);
    scene.add_object(obj);
}

static void add_table(Scene& scene) {
    auto lambertian_brown = std::make_shared<Lambertian>(Color(.3, .13, .03));
    add_table_legs(scene, lambertian_brown);
}

Scene init_scene3() {
    Camera cam = init_camera();

    Scene scene(cam, Color(.5, .5, .5));
    init_lights(scene);

    add_plane(scene);

    add_table(scene);

    return scene;
}
