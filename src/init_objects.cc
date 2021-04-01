#include "init_objects.hh"

void add_ground_plane(Scene& scene) {
    auto lambertian_ground = std::make_shared<Lambertian>(Color(0.41, 0.25, 0.20), 0.5);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(lambertian_ground);
    //plane->add_bump_mapping(Noise(MARBLE, 10), 10);
    plane->add_bump_mapping(Noise(TURBULENCE, 15), 10);
    plane->add_bump_mapping(Noise(TURBULENCE, 10), 2);
    plane->add_bump_mapping(Noise(MARBLE, 5), 3);
    plane->add_bump_mapping(Noise(TURBULENCE, 20), 7);
    scene.add_object(plane);
}

void add_water_plane(Scene& scene) {
    auto lambertian_water = std::make_shared<Metal>(Color(0.05, 0.41, 0.75), 0.5);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(lambertian_water);
    plane->set_specular(20);
    //plane->add_bump_mapping(Noise(MARBLE, 10), 10);
    plane->add_bump_mapping(Noise(TURBULENCE, 15), 10);
    plane->add_bump_mapping(Noise(TURBULENCE, 10), 2);
    plane->add_bump_mapping(Noise(MARBLE, 5), 3);
    plane->add_bump_mapping(Noise(TURBULENCE, 20), 7);
    scene.add_object(plane);
}

void add_plane_black_white(Scene& scene) {
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(board_black_white);
    scene.add_object(plane);
}

void add_ice_cream(Scene& scene) {
    auto lambertian_orange = std::make_shared<Lambertian>(orange, 0.5);
    auto lambertian_light_blue = std::make_shared<Lambertian>(light_blue, 0.5);
    auto lambertian_light_green = std::make_shared<Lambertian>(light_green, 0.5);
    auto lambertian_yellow = std::make_shared<Lambertian>(yellow, 0.5);

    auto capped_cone = std::make_shared<CappedCone>(Point3(-3, -1, 0), Point3(1, 0, 0), 0.0001, 1);
    capped_cone->set_texture(lambertian_orange);

    auto sphere1 = std::make_shared<Sphere>(Point3(1, 0, 0), 1);
    sphere1->set_texture(lambertian_light_blue);

    auto sphere2 = std::make_shared<Sphere>(Point3(2, .25, 0), 1);
    sphere2->set_texture(lambertian_light_green);

    auto sphere3 = std::make_shared<Sphere>(Point3(3, .5, 0), 1);
    sphere3->set_texture(lambertian_yellow);

    auto CSG_1 = std::make_shared<CSG>(UNION, sphere3, sphere2);
    auto CSG_2 = std::make_shared<CSG>(UNION, sphere1, capped_cone);
    auto CSG_3 = std::make_shared<CSG>(UNION, CSG_2, CSG_1);

    scene.add_object(CSG_3);
}

void add_CSG_fig_1(Scene& scene) {
    auto lambertian_blue = std::make_shared<Lambertian>(blue3, 0.6);
    auto lambertian_red = std::make_shared<Lambertian>(red, 0.6);

    auto sphere1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1.1);
    sphere1->set_texture(lambertian_blue);

    auto sphere2 = std::make_shared<Sphere>(Point3(0, 1, 0), .4);
    sphere2->set_texture(lambertian_red);

    auto cylinder = std::make_shared<Cylinder>(Point3(-1.5, 0, 0), Point3(1.5, 0, 0), .75);
    cylinder->set_texture(lambertian_blue);

    auto cube = std::make_shared<Cube>(Point3(-1, -1, -1), 2);
    cube->set_texture(lambertian_blue);

    auto CSG_1 = std::make_shared<CSG>(UNION, cube, cylinder);
    auto CSG_2 = std::make_shared<CSG>(MINUS, CSG_1, sphere1);
    auto CSG_3 = std::make_shared<CSG>(UNION, CSG_2, sphere2);
    scene.add_object(CSG_3);
}

void add_CSG_fig_2(Scene& scene) {
    auto lambertian_blue = std::make_shared<Lambertian>(blue, 0.6);
    auto lambertian_blue2 = std::make_shared<Lambertian>(red, 0.6);
    auto lambertian_blue3 = std::make_shared<Lambertian>(blue3, 0.6);

    auto cube = std::make_shared<Cube>(Point3(-1, -1, -1), 2);
    cube->set_texture(lambertian_blue);

    auto sphere1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1.25);
    sphere1->set_texture(lambertian_blue3);

    auto cylinder1 = std::make_shared<Cylinder>(Point3(-1.25, 0, 0), Point3(1.25, 0, 0), .25);
    auto cylinder2 = std::make_shared<Cylinder>(Point3(0, 0, -1.25), Point3(0, 0, 1.25), .25);
    auto cylinder3 = std::make_shared<Cylinder>(Point3(0, -1.25, 0), Point3(0, 1.25, 0), .25);
    cylinder1->set_texture(lambertian_blue2);
    cylinder2->set_texture(lambertian_blue2);
    cylinder3->set_texture(lambertian_blue2);

    auto CSG_1 = std::make_shared<CSG>(INTERSECTION, cube, sphere1);
    auto CSG_2 = std::make_shared<CSG>(UNION, cylinder1, cylinder2);
    auto CSG_3 = std::make_shared<CSG>(UNION, CSG_2, cylinder3);

    auto CSG_4 = std::make_shared<CSG>(UNION, CSG_1, CSG_3);

    //scene.add_object(std::make_shared<CSG>(MINUS, sphere1, cylinder2));
    scene.add_object(CSG_4);
}

void add_sphere_map(Scene& scene) {
    auto image_carte_texture = std::make_shared<ImageTexture>("textures/carte.ppm");
    auto sphere_map = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    sphere_map->set_texture(image_carte_texture);
    scene.add_object(sphere_map);
}

void add_flower_cube(Scene& scene) {
    auto image_flower_texture = std::make_shared<ImageTexture>("textures/flower.ppm");
    auto cube = std::make_shared<Cube>(Point3(-1, -1, -1), 2);
    cube->set_texture(image_flower_texture);
    scene.add_object(cube);
}

void add_sheep_cube(Scene& scene) {
    auto image_sheep_texture = std::make_shared<ImageTexture>("textures/sheep.ppm");
    auto cube = std::make_shared<Cube>(Point3(-1, -1, -1), 2);
    cube->set_texture(image_sheep_texture);
    scene.add_object(cube);
}

void add_sphere_noise_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(NOISE, 10));
    scene.add_object(obj1);
}

void add_sphere_turb_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(TURBULENCE, 10));
    scene.add_object(obj1);
}

void add_sphere_marble_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(MARBLE, 10));
    scene.add_object(obj1);
}

void add_sphere_wood_mapping(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(WOOD, 10));
    scene.add_object(obj1);
}

void add_transparent_sphere(Scene& scene) {
    auto metal_random = std::make_shared<Metal>(r_random::random_color());
    metal_random->set_transparent_type();
    metal_random->kd = 0.1;
    metal_random->kt = 0.25;
    auto sphere = std::make_shared<Sphere>(Point3(-2, 0, 0), 1);
    sphere->set_texture(metal_random);
    sphere->set_specular(30);
    scene.add_object(sphere);
}

void add_sphere_noise(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, NOISE, r_random::random_color(), r_random::random_color());
    auto p1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    p1->set_texture(perlin);
    scene.add_object(p1);
}

void add_sphere_turb(Scene& scene) {
    auto perlin2 = std::make_shared<PerlinNoise>(2, TURBULENCE, r_random::random_color(), r_random::random_color());
    auto p2 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    p2->set_texture(perlin2);
    scene.add_object(p2);
}

void add_sphere_marble(Scene& scene) {
    auto perlin3 = std::make_shared<PerlinNoise>(2, MARBLE, r_random::random_color(), r_random::random_color());
    auto p3 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    p3->set_texture(perlin3);
    scene.add_object(p3);
}

void add_sphere_wood(Scene& scene) {
    auto perlin4 = std::make_shared<PerlinNoise>(2, WOOD);
    auto p4 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    p4->set_texture(perlin4);
    scene.add_object(p4);
}

void add_sphere_wood_custom_color(Scene& scene) {
    auto perlin5 = std::make_shared<PerlinNoise>(2, WOOD, r_random::random_color(), r_random::random_color());
    auto sphere_wood_colored = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    sphere_wood_colored->add_bump_mapping(Noise(WOOD, 10));
    sphere_wood_colored->set_texture(perlin5);
    sphere_wood_colored->set_specular(50);
    scene.add_object(sphere_wood_colored);
}

void add_strip_sphere_spherical(Scene& scene) {
    auto strip = std::make_shared<Strip>(r_random::random_color(), r_random::random_color(), true, 25);
    auto sphere1 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    sphere1->set_texture(strip);
    sphere1->set_specular(25);
    scene.add_object(sphere1);
}

void add_strip_vertical_sphere_planar(Scene& scene) {
    auto strip2 = std::make_shared<Strip>(r_random::random_color(), r_random::random_color(), true, 5);
    strip2->set_planar(true);
    auto sphere2 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    sphere2->set_texture(strip2);
    scene.add_object(sphere2);
}

void add_strip_horizontal_sphere_planar(Scene& scene) {
    auto strip2 = std::make_shared<Strip>(r_random::random_color(), r_random::random_color(), true, 5);
    strip2->set_planar(true);
    strip2->set_horizontal(false);
    auto sphere2 = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    sphere2->set_texture(strip2);
    scene.add_object(sphere2);
}

void add_torus(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto torus = std::make_shared<Torus>(Point3(2.5, .5, 0));
    torus->set_texture(lambertian_random);
    scene.add_object(torus);
}

void add_capsule(Scene& scene) {
    auto metal_random = std::make_shared<Metal>(r_random::random_color(), 0.2);
    auto capsule = std::make_shared<Capsule>(Point3(-1, 0, -1), Point3(1, 1, 1), 1);
    capsule->set_texture(metal_random);
    scene.add_object(capsule);
}

void add_cube(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color(), 0.6);
    auto cube = std::make_shared<Cube>(Point3(-1, -1, -1), 2);
    cube->set_texture(lambertian_random);
    scene.add_object(cube);
}

void add_cylinder(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color(), 0.6);
    auto cylinder = std::make_shared<Cylinder>(Point3(-1, 0, 0), Point3(1, 1, 1), 1);
    cylinder->set_texture(lambertian_random);
    scene.add_object(cylinder);
}

void add_capped_cone(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color(), 0.6);
    auto capped_cone = std::make_shared<CappedCone>(Point3(1, 0, 0), Point3(-1, 1, 1), 1, .5);
    capped_cone->set_texture(lambertian_random);
    scene.add_object(capped_cone);
}

void add_cone(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color(), 0.6);
    auto cone1 = std::make_shared<Cone>(Point3(0, -1, 0), 1, 2);
    cone1->set_texture(lambertian_random);
    cone1->set_specular(30);
    scene.add_object(cone1);
}

void add_ellipsoid(Scene& scene) {
    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color(), 0.6);
    auto ellipsoid = std::make_shared<Ellipsoid>(Point3(0, 0, 0), Point3(1.5, 0.5, 2));
    ellipsoid->set_texture(lambertian_random);
    scene.add_object(ellipsoid);
}
