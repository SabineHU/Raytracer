#include "scene3.hh"

#include "point_light.hh"
#include "color.hh"

#include "plane.hh"

#include "noise.hh"
#include "image_texture.hh"
#include "lambertian.hh"
#include "random.hh"

static Camera init_camera() {
    //Vect look_from(0, 13, -.000001);
    Vect look_from(0, 0, -10);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

static void add_plane(Scene& scene) {
    auto image = std::make_shared<ImageTexture>("textures/disp_sheep.ppm");
    image->reverse_image();
    auto lambertian_ground = std::make_shared<Lambertian>(Color(0.41, 0.25, 0.20), 0.5);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_width(8);
    plane->set_height(6);
    plane->set_texture(lambertian_ground);
    plane->set_displacement_image(image);
    plane->add_bump_mapping(Noise(TURBULENCE, 15));
    scene.add_object(plane);
}

Scene init_scene3() {
    Camera cam = init_camera();

    Scene scene(cam, Color(.5, .5, .5));
    init_lights(scene);

    add_plane(scene);
    // TODO: scene 3
    // add CSG
    // show clearly specular effect
    // add blob diamond
    // add multiples lights

    return scene;
}
