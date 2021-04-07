#include "scene4.hh"

#include "point_light.hh"

#include "sphere.hh"
#include "plane.hh"

#include "lambertian.hh"
#include "perlin_noise.hh"

#include "blob.hh"

#include "random.hh"
#include "color.hh"

static Camera init_camera() {
    //Vect look_from(0, 10, -.00008);
    Vect look_from(0, 2, -8);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

static void add_plane(Scene& scene) {
    auto perlin = std::make_shared<PerlinNoise>(2, NOISE, r_random::random_color() / 2, blue3);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(perlin);
    scene.add_object(plane);
}

Blob init_blob() {
    std::vector<shared_object> blob_objects;
    auto red_sphere = std::make_shared<Sphere>(Point3(-1.5, 0.5, 1.5), 1);
    auto blue_sphere = std::make_shared<Sphere>(Point3(1.5, 0.5, 1.5), 1);
    auto green_sphere = std::make_shared<Sphere>(Point3(1.5, 0.5, -1.5), 1);
    auto yellow_sphere = std::make_shared<Sphere>(Point3(-1.5, 0.5, -1.5), 1);

    red_sphere->set_texture(red);
    blue_sphere->set_texture(blue);
    green_sphere->set_texture(green);
    yellow_sphere->set_texture(yellow);

    blob_objects.push_back(red_sphere);
    blob_objects.push_back(blue_sphere);
    blob_objects.push_back(green_sphere);
    blob_objects.push_back(yellow_sphere);

    Blob blob(Point3(0, 0, 0), 6, .5, 85, blob_objects, true);
    blob.compute();

    return blob;
}

Blob init_blob2() {
    std::vector<shared_object> blob_objects;

    auto red_sphere = std::make_shared<Sphere>(Point3(0, 1, 1.50495) * 2, 1);
    auto purple_sphere = std::make_shared<Sphere>(Point3(1.30332, .5, 0.752475) * 2, 1);
    auto blue_sphere = std::make_shared<Sphere>(Point3(1.30332, 1, -0.752474) * 2, 1);
    auto green_sphere = std::make_shared<Sphere>(Point3(0, .5, -1.50495) * 2, 1);
    auto yellow_sphere = std::make_shared<Sphere>(Point3(-1.30332, 1, -0.752475) * 2, 1);
    auto orange_sphere = std::make_shared<Sphere>(Point3(-1.30332, .5, 0.752475) * 2, 1);

    red_sphere->set_texture(red);
    blue_sphere->set_texture(blue);
    purple_sphere->set_texture(purple);
    green_sphere->set_texture(green);
    yellow_sphere->set_texture(yellow);
    orange_sphere->set_texture(orange);

    blob_objects.push_back(red_sphere);
    blob_objects.push_back(blue_sphere);
    blob_objects.push_back(purple_sphere);
    blob_objects.push_back(green_sphere);
    blob_objects.push_back(yellow_sphere);
    blob_objects.push_back(orange_sphere);

    Blob blob(Point3(0, 0, 0), 8, .5, 90, blob_objects, true);
    blob.compute();

    return blob;
}

Blob init_blob3() {
    std::vector<shared_object> blob_objects;

    auto red_sphere = std::make_shared<Sphere>(Point3(-3, 0.5, 0), 1);
    auto green_sphere = std::make_shared<Sphere>(Point3(0, 0.5, 0), 1);
    auto blue_sphere = std::make_shared<Sphere>(Point3(3, 0.5, 0), 1);

    red_sphere->set_texture(red);
    green_sphere->set_texture(green);
    blue_sphere->set_texture(blue);

    blob_objects.push_back(red_sphere);
    blob_objects.push_back(green_sphere);
    blob_objects.push_back(blue_sphere);

    Blob blob(Point3(0, 0, 0), 11, .25, 75, blob_objects, true);
    blob.compute();

    return blob;
}

Scene init_scene4() {
    Camera cam = init_camera();
    Scene scene(cam, Color(.5, .5, .5));
    scene.set_background_colors(Color(0.03, 0.08, 0.25), Color(0.03, 0.05, 0.14));
    init_lights(scene);

    add_plane(scene);

    //Blob blob = init_blob(); // 4 spheres
    //Blob blob = init_blob2(); // 5 sphers
    Blob blob = init_blob3(); // 3 spheres
    /* Add triangles to scene */
    for (auto& triangle: blob.get_triangles()) {
        scene.add_object(std::make_shared<SmoothTriangle>(triangle));
    }

    return scene;
}
