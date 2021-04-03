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

enum Position {
    NONE, TOP, BOTTOM, RIGHT, LEFT, FRONT, BACK
};

shared_object create_sphere(shared_texture t, const Point3& pos, double radius, double specular) {
    auto sphere = std::make_shared<Sphere>(pos, radius);
    sphere->set_texture(t);
    sphere->set_specular(specular);
    return sphere;
}

void sphere_duplication(Scene& scene, Position p, double radius, double specular, const Point3& prev_pos) {
    if (radius < 0.25)
        return;

    double new_rad = radius * 4.0 / 9.0;
    auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.5);
    if (p != BOTTOM) { // Create top sphere
        Point3 new_pos = prev_pos;
        new_pos.y += radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_duplication(scene, TOP, new_rad, specular * 2, new_pos);
    }
    if (p != LEFT) { // Create right sphere
        Point3 new_pos = prev_pos;
        new_pos.x += radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_duplication(scene, RIGHT, new_rad, specular * 2, new_pos);
    }
    if (p != TOP) { // Create bottom sphere
        Point3 new_pos = prev_pos;
        new_pos.y -= radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_duplication(scene, BOTTOM, new_rad, specular * 2, new_pos);
    }
    if (p != RIGHT) { // Create left sphere
        Point3 new_pos = prev_pos;
        new_pos.x -= radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_duplication(scene, LEFT, new_rad, specular * 2, new_pos);
    }
    if (p != BACK) { // Create front sphere
        Point3 new_pos = prev_pos;
        new_pos.z += radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_duplication(scene, FRONT, new_rad, specular * 2, new_pos);
    }
    if (p != FRONT) { // Create back sphere
        Point3 new_pos = prev_pos;
        new_pos.z -= radius + new_rad;
        scene.add_object(create_sphere(metal_random, new_pos, new_rad, specular));
        sphere_duplication(scene, BACK, new_rad, specular * 2, new_pos);
    }
}

void init_landscape_2(Scene& scene) {
    Vect look_from(6, 2, -8);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    scene.set_camera(Camera(look_from, look_at, vup));
    //add_plane_black_white(scene);

    auto pos = Point3(0, -0.5, 0);
    double radius = 2;
    double specular = 5;
    auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.5);
    scene.add_object(create_sphere(metal_random, pos, radius, specular));
    sphere_duplication(scene, NONE, radius, specular, pos);

    //auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.8);
    //auto sphere2 = std::make_shared<Sphere>(Point3(0, 1.5, 0), .5);
    //sphere2->set_texture(metal_random);
    //sphere2->set_specular(25);
    //scene.add_object(sphere2);

    //auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.8);
    //auto sphere2 = std::make_shared<Sphere>(Point3(0, 2, 0), 1);
    //sphere2->set_texture(metal_random);
    //sphere2->set_specular(25);
    //scene.add_object(sphere2);

    //auto metal_random2 = std::make_shared<Metal>(r_random::random_color(), 0.3);
    //auto sphere3 = std::make_shared<Sphere>(Point3(0, -2, 0), 1);
    //sphere3->set_texture(metal_random2);
    //sphere3->set_specular(50);
    //scene.add_object(sphere3);
}
