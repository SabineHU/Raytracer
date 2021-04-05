#include "scene5.hh"

#include "perlin_noise.hh"
#include "checkerboard.hh"
#include "strip.hh"
#include "image_texture.hh"
#include "metal.hh"

#include "sphere.hh"
#include "plane.hh"
#include "plane_holed.hh"

#include "point_light.hh"
#include "random.hh"
#include "color.hh"

static Camera init_camera() {
    Vect look_from(0, 3, -10);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

static void add_plane(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, RAINBOW, r_random::random_color(), r_random::random_color());
    perlin->ks = 0.8;
    perlin->ka = 1;
    perlin->set_reflection_type();
    auto plane = std::make_shared<PlaneHoled>(Point3(0, 1, 0), -1, 3, 3);
    plane->set_texture(perlin);
    plane->set_specular(20);
    scene.add_object(plane);

    auto board_black_white = std::make_shared<CheckerBoard>(Color(.2, .2, .2), white);
    board_black_white->ks = 0.8;
    board_black_white->ka = 1;
    auto plane2 = std::make_shared<Plane>(Point3(0, 1.00001, 0), -1);
    plane2->set_texture(board_black_white);
    scene.add_object(plane2);
}

static void add_strip_sphere_spherical(Scene& scene) {
    auto strip = std::make_shared<Strip>(orange, r_random::random_color(), true, 25);
    auto sphere1 = std::make_shared<Sphere>(Point3(-4, -.5, -3), .5);
    sphere1->set_texture(strip);
    sphere1->set_specular(25);
    scene.add_object(sphere1);
}

static void add_strip_vertical_sphere_planar(Scene& scene) {
    auto strip2 = std::make_shared<Strip>(Color(.5, .5, .5), r_random::random_color(), true, 10);
    strip2->set_planar(true);
    auto sphere2 = std::make_shared<Sphere>(Point3(-2, -.6, -4.5), .4);
    sphere2->set_texture(strip2);
    sphere2->set_specular(15);
    scene.add_object(sphere2);
}

static void add_strip_horizontal_sphere_planar(Scene& scene) {
    auto strip2 = std::make_shared<Strip>(white, r_random::random_color(), true, 5);
    strip2->set_planar(true);
    strip2->set_horizontal(false);
    auto sphere2 = std::make_shared<Sphere>(Point3(-4, 1, 10), 2);
    sphere2->set_texture(strip2);
    scene.add_object(sphere2);
}

static void add_checker_sphere(Scene& scene) {
    auto t = std::make_shared<CheckerBoard>(r_random::random_color(), light_blue);
    auto sphere2 = std::make_shared<Sphere>(Point3(2, 0, 3), 1);
    t->set_scale(15);
    sphere2->set_texture(t);
    sphere2->set_specular(15);
    scene.add_object(sphere2);
}

static void add_sphere_map(Scene& scene) {
    auto image_carte_texture = std::make_shared<ImageTexture>("textures/carte.ppm");
    auto sphere_map = std::make_shared<Sphere>(Point3(-2, 0, -.5), 1);
    sphere_map->set_texture(image_carte_texture);
    sphere_map->set_specular(30);
    scene.add_object(sphere_map);
}

static void add_sphere_noise_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(0, -.3, -5.5), .7);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(NOISE, 10));
    scene.add_object(obj1);
}

static void add_sphere_turb_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(-1, -.4, -2.3), .6);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(TURBULENCE, 10));
    scene.add_object(obj1);
}

static void add_sphere_marble_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(-3.9, -.4, -5.2), .6);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(MARBLE, 10));
    scene.add_object(obj1);
}

static void add_sphere_wood_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(4, -.2, -3.7), .8);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(WOOD, 10));
    scene.add_object(obj1);
}

static void add_sphere_noise(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, NOISE, light_red, Color());
    auto p1 = std::make_shared<Sphere>(Point3(-15, 1.5, 14), 2.5);
    p1->set_specular(10);
    p1->set_texture(perlin);
    scene.add_object(p1);
}

static void add_sphere_turb(Scene& scene) {
    auto perlin2 = std::make_shared<PerlinNoise>(2, TURBULENCE, purple, r_random::random_color());
    auto p2 = std::make_shared<Sphere>(Point3(2, .7, 15), 1.7);
    p2->set_texture(perlin2);
    scene.add_object(p2);
}

static void add_sphere_marble(Scene& scene) {
    auto perlin3 = std::make_shared<PerlinNoise>(2, MARBLE, Color(.6, .3, .6), r_random::random_color());
    auto p3 = std::make_shared<Sphere>(Point3(-6.3, .3, 7), 1.3);
    p3->set_texture(perlin3);
    scene.add_object(p3);
}

static void add_sphere_wood(Scene& scene) {
    auto perlin4 = std::make_shared<PerlinNoise>(2, WOOD);
    auto p4 = std::make_shared<Sphere>(Point3(-.3, 0, 4), 1);
    p4->set_texture(perlin4);
    scene.add_object(p4);
}

static void add_sphere_rainbow(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, RAINBOW, Color(0, 0, 0), Color(0, 0, .5));
    auto p1 = std::make_shared<Sphere>(Point3(15, .6, 20), 1.6);
    p1->set_texture(perlin);
    scene.add_object(p1);
}

static void add_sphere_noise_wood_mapping(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(10, NOISE, pink, light_blue);
    auto obj1 = std::make_shared<Sphere>(Point3(-7.47, 0, 1.86), 1);
    obj1->set_texture(perlin);
    obj1->add_bump_mapping(Noise(WOOD, 10));
    scene.add_object(obj1);
}

static void add_sphere_marble_marble_mapping(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(10, MARBLE, r_random::random_color(), blue);
    auto obj1 = std::make_shared<Sphere>(Point3(1.87, -.3, -1.86), .7);
    obj1->set_texture(perlin);
    obj1->add_bump_mapping(Noise(MARBLE, 5));
    scene.add_object(obj1);
}

static void add_sphere_rainbow_turb_mapping(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(10, RAINBOW, Color(0, 1, 0), light_blue);
    auto obj1 = std::make_shared<Sphere>(Point3(-7.47, 0, -1.86), 1);
    obj1->set_texture(perlin);
    obj1->add_bump_mapping(Noise(TURBULENCE, 10));
    scene.add_object(obj1);
}

static void add_sphere_strip_noise_mapping(Scene& scene) {
    auto strip = std::make_shared<Strip>(Color(.5, .15, .15), r_random::random_color(), true, 4);
    strip->set_planar(true);
    auto obj1 = std::make_shared<Sphere>(Point3(6.76, 0, 5.86), 1);
    obj1->set_texture(strip);
    obj1->set_specular(20);
    obj1->add_bump_mapping(Noise(NOISE, 10));
    scene.add_object(obj1);
}

static void add_sphere_wood_turb(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(10.47, .45, 3.87), 1.45);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(WOOD, 10));
    obj1->add_bump_mapping(Noise(TURBULENCE, 10), 2);
    scene.add_object(obj1);
}

Scene init_scene5() {
    Camera cam = init_camera();
    Scene scene(cam, Color(.5, .5, .5));
    init_lights(scene);

    add_plane(scene);
    add_strip_sphere_spherical(scene);
    add_strip_vertical_sphere_planar(scene);
    add_strip_horizontal_sphere_planar(scene);
    add_checker_sphere(scene);
    add_sphere_map(scene);
    add_sphere_noise_mapping(scene);
    add_sphere_turb_mapping(scene);
    add_sphere_marble_mapping(scene);
    add_sphere_wood_mapping(scene);
    add_sphere_noise(scene);
    add_sphere_turb(scene);
    add_sphere_marble(scene);
    add_sphere_wood(scene);
    add_sphere_rainbow(scene);
    add_sphere_noise_wood_mapping(scene);
    add_sphere_marble_marble_mapping(scene);
    add_sphere_rainbow_turb_mapping(scene);
    add_sphere_strip_noise_mapping(scene);
    add_sphere_wood_turb(scene);

    return scene;
}
