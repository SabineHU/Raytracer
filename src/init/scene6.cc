#include "scene6.hh"

#include "plane.hh"
#include "point_light.hh"
#include "perlin_noise.hh"
#include "lambertian.hh"
#include "checkerboard.hh"
#include "metal.hh"
#include "strip.hh"

#include "sphere.hh"
#include "cone.hh"
#include "capped_cone.hh"
#include "ellipsoid.hh"
#include "torus.hh"
#include "cylinder.hh"
#include "cube.hh"
#include "capsule.hh"

#include "random.hh"
#include "color.hh"

static Camera init_camera() {
    Vect look_from(0, 4, -14);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 2));
    //scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), light_red, 2));
}

static void add_plane(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, RAINBOW, r_random::random_color(), r_random::random_color());
    auto lamb = std::make_shared<Lambertian>(Color(.91, .705, .733));
    //auto lamb = std::make_shared<Lambertian>(white);
    auto checkerboard = std::make_shared<CheckerBoard>(lamb, perlin);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(checkerboard);
    scene.add_object(plane);
}

static void add_cone(Scene& scene) {
    auto strip = std::make_shared<Strip>(light_blue, r_random::random_color(), true, 10);
    strip->set_planar(true);
    strip->ks = .5;
    strip->kd = 1;
    auto cone1 = std::make_shared<Cone>(Point3(-5.5, -1, -6.5), 1, 2);
    cone1->set_texture(strip);
    cone1->set_specular(30);
    scene.add_object(cone1);
}

static void add_ellipsoid(Scene& scene) {
    auto metal_random = std::make_shared<Metal>(r_random::random_color());
    auto ellipsoid = std::make_shared<Ellipsoid>(Point3(-4.25, 0, -4), Point3(2, 1, 2));
    ellipsoid->set_texture(metal_random);
    ellipsoid->set_specular(20);
    scene.add_object(ellipsoid);
}

static void add_torus(Scene& scene) {
    auto torus = std::make_shared<Torus>(Point3(2.5, .5, 0));
    torus->set_texture(r_random::random_color());
    scene.add_object(torus);
}

static void add_cylinder(Scene& scene) {
    auto strip = std::make_shared<Strip>(white, r_random::random_color(), true, 10);
    strip->set_planar(true);
    strip->set_horizontal(false);
    auto cylinder = std::make_shared<Cylinder>(Point3(-1, 0, -1), Point3(1, 1, 0), 1);
    cylinder->set_texture(strip);
    scene.add_object(cylinder);
}

static void add_cube(Scene& scene) {
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    board_black_white->set_scale(5);
    auto cube = std::make_shared<Cube>(Point3(4, -1, 3), 2);
    cube->set_texture(board_black_white);
    scene.add_object(cube);
}

static void add_capped_cone(Scene& scene) {
    auto capped_cone = std::make_shared<CappedCone>(Point3(8, 0, 5), Point3(7, 1, 6), 1, .5);
    capped_cone->set_texture(r_random::random_color());
    scene.add_object(capped_cone);
}

static void add_capsule(Scene& scene) {
    auto capsule = std::make_shared<Capsule>(Point3(14, 0, 8), Point3(12, 1, 10), 1);
    capsule->set_texture(r_random::random_color());
    scene.add_object(capsule);
}

static void add_transparent_sphere(Scene& scene) {
    auto metal_random = std::make_shared<Metal>(r_random::random_color());
    metal_random->set_transparent_type();
    metal_random->kd = 0.9;
    metal_random->kt = 0.8;
    auto sphere = std::make_shared<Sphere>(Point3(3, 0, -5), 1);
    sphere->set_texture(metal_random);
    sphere->set_specular(30);
    sphere->set_ior(1.33);
    scene.add_object(sphere);
}

static void add_transparent_sphere2(Scene& scene) {
    auto metal_random = std::make_shared<Metal>(white);
    metal_random->set_transparent_type();
    metal_random->kd = 0.1;
    metal_random->kt = .8;
    auto sphere = std::make_shared<Sphere>(Point3(4, 0, -7.25), 1);
    sphere->set_texture(metal_random);
    sphere->set_specular(30);
    sphere->set_ior(1.33);
    scene.add_object(sphere);
}

static void add_transparent_sphere3(Scene& scene) {
    auto metal_random = std::make_shared<Metal>(r_random::random_color() * 2);
    metal_random->set_transparent_type();
    metal_random->kd = 0.1;
    metal_random->kt = .8;
    auto sphere = std::make_shared<Sphere>(Point3(2.2, -.4, -6.2), .6);
    sphere->set_texture(metal_random);
    sphere->set_specular(30);
    sphere->set_ior(1.33);
    scene.add_object(sphere);
}

Scene init_scene6() {
    Camera cam = init_camera();
    Scene scene(cam, Color(.5, .5, .5));
    //scene.set_fog_properties(20, 1);
    //scene.set_fog_properties(20, 2);
    scene.set_fog_properties(20, 3);
    //scene.set_fog_properties(10, 3);
    init_lights(scene);

    add_plane(scene);

    add_cone(scene);
    add_ellipsoid(scene);
    add_torus(scene);
    add_cylinder(scene);
    add_cube(scene);
    add_capped_cone(scene);
    add_capsule(scene);
    add_transparent_sphere(scene);
    add_transparent_sphere2(scene);
    add_transparent_sphere3(scene);

    return scene;
}
