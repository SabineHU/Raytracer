#include "init_landscape.hh"

void init_landscape_1(Scene& scene) {
    //add_water_plane_reflection(scene);
    add_plane_black_white(scene);

    auto lambertian_random = std::make_shared<Lambertian>(orange, 0.6);
    auto ellipsoid = std::make_shared<Ellipsoid>(Point3(0, -1.5, 3), Point3(6, 1, 5));
    ellipsoid->set_texture(lambertian_random);
    ellipsoid->add_bump_mapping(Noise(NOISE, 25));
    scene.add_object(ellipsoid);
}
