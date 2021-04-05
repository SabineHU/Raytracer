#include "scene1.hh"

#include "point_light.hh"
#include "plane.hh"
#include "perlin_noise.hh"

#include "random.hh"
#include "color.hh"

#include "polygon.hh"
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

Scene init_scene1() {
    Camera cam = init_camera();

    Scene scene(cam, Color(0.5, 0.5, 0.5));
    init_lights(scene);

    add_boat(scene);
    add_water_plane(scene);

    return scene;
}
