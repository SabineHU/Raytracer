#include "scene2.hh"

#include "point_light.hh"
#include "sphere.hh"
#include "metal.hh"

#include "random.hh"
#include "color.hh"

static Camera init_camera() {
    Vect look_from(6, 2, -8);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(0, 0, -10), light_blue, 1.5));
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

enum Position {
    NONE, TOP, BOTTOM, RIGHT, LEFT, FRONT, BACK
};

static shared_object create_sphere(shared_texture t, const Point3& pos, double radius, double specular) {
    auto sphere = std::make_shared<Sphere>(pos, radius);
    sphere->set_texture(t);
    sphere->set_specular(specular);
    return sphere;
}

static void sphere_fract(Scene& scene, Position p, double radius, double specular, const Point3& prev_pos, int depth) {
    if (depth == 0)
        return;

    double new_rad = radius * 4.0 / 9.0;
    auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.5);
    if (p != BOTTOM) { // Create top sphere
        Point3 new_pos = prev_pos;
        new_pos.y += radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_fract(scene, TOP, new_rad, specular * 2, new_pos, depth - 1);
    }
    if (p != LEFT) { // Create right sphere
        Point3 new_pos = prev_pos;
        new_pos.x += radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_fract(scene, RIGHT, new_rad, specular * 2, new_pos, depth - 1);
    }
    if (p != TOP) { // Create bottom sphere
        Point3 new_pos = prev_pos;
        new_pos.y -= radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_fract(scene, BOTTOM, new_rad, specular * 2, new_pos, depth - 1);
    }
    if (p != RIGHT) { // Create left sphere
        Point3 new_pos = prev_pos;
        new_pos.x -= radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_fract(scene, LEFT, new_rad, specular * 2, new_pos, depth - 1);
    }
    if (p != BACK) { // Create front sphere
        Point3 new_pos = prev_pos;
        new_pos.z += radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_fract(scene, FRONT, new_rad, specular * 2, new_pos, depth - 1);
    }
    if (p != FRONT) { // Create back sphere
        Point3 new_pos = prev_pos;
        new_pos.z -= radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_fract(scene, BACK, new_rad, specular * 2, new_pos, depth - 1);
    }
}

static void add_spheres(Scene& scene) {
    auto pos = Point3(0, -0.5, 0);
    double radius = 2;
    double specular = 5;
    auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.5);
    scene.add_object(create_sphere(metal_random, pos, radius, specular));
    sphere_fract(scene, NONE, radius, specular, pos, 5);
}

Scene init_scene2() {
    Camera cam = init_camera();

    Scene scene(cam, Color(0.5, 0.5, 0.5));
    scene.set_background_colors(Color(0.03, 0.08, 0.25), Color(0.03, 0.05, 0.14));
    init_lights(scene);

    add_spheres(scene);

    return scene;
}
