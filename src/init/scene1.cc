#include "scene1.hh"

#include "point_light.hh"
#include "plane.hh"
#include "perlin_noise.hh"

#include "random.hh"
#include "color.hh"

#include "polygon.hh"
#include "sphere.hh"
#include "capsule.hh"
#include "cube.hh"
#include "rotate.hh"
#include "ellipsoid.hh"
#include "CSG.hh"

#include "metal.hh"
#include "lambertian.hh"

#include "loader.hh"

static Camera init_camera() {
    Vect look_from(0, 2, -8);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(0, 2, -10), light_blue, 1.5));
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

static void add_boat(Scene& scene) {
    auto mat = parse_materials("objs/boat.mtl");
    auto p = parse_obj_to_polygon("objs/boat.obj", mat);
    scene.add_object(std::make_shared<Polygon>(p));
}

static void add_water_plane(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, CLOUD, r_random::random_color(), r_random::random_color());
    perlin->kd = 0.25;
    perlin->kt = 0.5;
    perlin->ks = 0.7;
    perlin->set_reflection_type();
    auto p1= std::make_shared<Plane>(Point3(0, 1, 0), -1);
    p1->set_texture(perlin);
    p1->add_bump_mapping(Noise(TURBULENCE, 10), 2);
    p1->add_bump_mapping(Noise(TURBULENCE, 20), 3);
    p1->set_specular(40);
    scene.add_object(p1);
}

static void add_sphere(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, MARBLE, r_random::random_color() / 2, r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(3, -1, -4), 1);
    obj1->set_texture(perlin);
    obj1->add_bump_mapping(Noise(WOOD, 10));
    scene.add_object(obj1);
}

static void add_sphere2(Scene& scene) {
    auto t = std::make_shared<Metal>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(-5, -.5, 8), 1);
    obj1->set_texture(t);
    scene.add_object(obj1);
}

static void add_capsule(Scene& scene) {
    auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.5);
    auto capsule = std::make_shared<Capsule>(Point3(-6.5, -.75, 2), Point3(-4.5, -.75, 4), .75);
    capsule->set_texture(metal_random);
    capsule->add_bump_mapping(Noise(TURBULENCE, 10));
    scene.add_object(capsule);
}

static void add_ellipsoid(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(light_orange, 0.6);
    auto ellipsoid = std::make_shared<Ellipsoid>(Point3(-17, -1.25, 25), Point3(10, 1, 6));
    ellipsoid->set_texture(lambertian_random);
    scene.add_object(ellipsoid);
}

static void add_CSG_spheres(Scene& scene) {
    auto perlin2 = std::make_shared<PerlinNoise>(2, TURBULENCE, r_random::random_color(), r_random::random_color());
    perlin2->ka = 1;
    perlin2->ks = 0.7;

    auto sphere1 = std::make_shared<Sphere>(Point3(-3, -.8, -3.25), .75);
    sphere1->set_texture(perlin2);
    sphere1->set_specular(60);

    auto sphere2 = std::make_shared<Sphere>(Point3(-4, -.8, -3), .75);
    sphere2->set_texture(perlin2);
    sphere2->set_specular(60);

    auto res = std::make_shared<CSG>(UNION, sphere1, sphere2);
    scene.add_object(res);
}

static void add_rotated_cube(Scene& scene) {
    auto perlin4 = std::make_shared<PerlinNoise>(2, WOOD, Color(.314, .161, 0), Color(.392, .239, .004));
    auto cube = std::make_shared<Cube>(Point3(-1, -2, -1), 2);
    cube->set_texture(perlin4);

    auto rotated1 = std::make_shared<RotatedObject>(cube, 45, AXIS_Y);
    auto rotated2 = std::make_shared<RotatedObject>(rotated1, 20, AXIS_Z);
    scene.add_object(rotated2);
}

Scene init_scene1() {
    Camera cam = init_camera();

    Scene scene(cam, Color(0.5, 0.5, 0.5));
    init_lights(scene);

    add_water_plane(scene);

    add_boat(scene);
    //add_rotated_cube(scene); // To add
    add_sphere(scene); // Bottom right
    add_sphere2(scene);
    add_capsule(scene);
    add_ellipsoid(scene);
    //add_CSG_spheres(scene); // To add

    return scene;
}
