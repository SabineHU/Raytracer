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

static shared_object create_rectangle_xz(const Point3& p1, const Point3& p2, shared_texture t) {
    auto obj1 = std::make_shared<Rectangle_xz>(p1, p2);
    obj1->set_texture(t);
    return obj1;
}

static void add_table_leg(Scene& scene, shared_texture t, double x1, double x2, double z1, double z2) {
    scene.add_object(create_rectangle_xy(Point3(x1, -1, z1), Point3(x2, .5, z1), t));
    scene.add_object(create_rectangle_xy(Point3(x1, -1, z2), Point3(x2, .5, z2), t));

    scene.add_object(create_rectangle_yz(Point3(x1, -1, z1), Point3(x1, .5, z2), t));
    scene.add_object(create_rectangle_yz(Point3(x2, -1, z1), Point3(x2, .5, z2), t));
}

static void add_table_plank(Scene& scene, shared_texture t, const Point3& pos,
        double l, double w) {
    double x1 = pos.x - l / 2;
    double z1 = pos.z - w / 2;

    double x_min = x1 - .25;
    double x_max = x1 + l + .25;

    double z_min = z1 - .25;
    double z_max = z1 + w + .25;

    double y_min = .5;
    double y_max = y_min + .15;

    scene.add_object(create_rectangle_xz(Point3(x_min, y_min, z_min), Point3(x_max, y_min, z_max), t));
    scene.add_object(create_rectangle_xz(Point3(x_min, y_max, z_min), Point3(x_max, y_max, z_max), t));

    scene.add_object(create_rectangle_xy(Point3(x_min, y_min, z_min), Point3(x_max, y_max, z_min), t));
    scene.add_object(create_rectangle_xy(Point3(x_min, y_min, z_max), Point3(x_max, y_max, z_max), t));

    scene.add_object(create_rectangle_yz(Point3(x_min, y_min, z_min), Point3(x_min, y_max, z_max), t));
    scene.add_object(create_rectangle_yz(Point3(x_max, y_min, z_min), Point3(x_max, y_max, z_max), t));

}

static void add_table_legs(Scene& scene, shared_texture t, const Point3& pos,
        double l, double w) {
    double x1 = pos.x - l / 2;
    double z1 = pos.z - w / 2;

    double x2 = x1 + .25;
    double z2 = z1 + .25;

    add_table_leg(scene, t, x1      , x2     , z1    , z2);
    add_table_leg(scene, t, x1      , x2     , z1 + w, z2 + w);
    add_table_leg(scene, t, x1 + l  , x2 + l , z1 + w, z2 + w);
    add_table_leg(scene, t, x1 + l  , x2 + l , z1    , z2);

    add_table_plank(scene, t, pos, l, w);
}

static void add_table(Scene& scene, const Point3& pos, double length, double width) {
    auto lambertian_brown = std::make_shared<Lambertian>(Color(.3, .13, .03));
    add_table_legs(scene, lambertian_brown, pos, length, width);
}

Scene init_scene3() {
    Camera cam = init_camera();

    Scene scene(cam, Color(.5, .5, .5));
    init_lights(scene);

    add_plane(scene);

    add_table(scene, Point3(0, 0, 0), 5, 4);

    return scene;
}
