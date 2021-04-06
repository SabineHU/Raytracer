#include "scene6.hh"

#include "plane.hh"
#include "point_light.hh"
#include "perlin_noise.hh"
#include "lambertian.hh"
#include "checkerboard.hh"

#include "random.hh"
#include "color.hh"

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
    auto perlin = std::make_shared<PerlinNoise>(2, RAINBOW, r_random::random_color(), r_random::random_color());
    auto lamb = std::make_shared<Lambertian>(white);
    auto checkerboard = std::make_shared<CheckerBoard>(lamb, perlin);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(checkerboard);
    scene.add_object(plane);
}

Scene init_scene6() {
    Camera cam = init_camera();
    Scene scene(cam, Color(.5, .5, .5));
    scene.set_fog_properties(50, 3);
    init_lights(scene);

    add_plane(scene);

    return scene;
}
