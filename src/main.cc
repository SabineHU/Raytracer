#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ray.hh"
#include "camera.hh"
#include "source.hh"
#include "light.hh"
#include "object.hh"
#include "sphere.hh"
#include "image.hh"
#include "plane.hh"
#include "scene.hh"
#include "init.hh"
#include "math.hh"

#include "checkerboard.hh"
#include "blob.hh"
#include "color.hh"

void tp1() {
    //int width = 640;
    //int height = 480;
    //image::Image img(width, height);

    //double alpha = math::degree_to_radian(35);
    double alpha = math::degree_to_radian(20);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9
    double zmin = 1000;
    image::Image img(alpha, beta, zmin);

    int samples = 5;
    int depth = 50;
    double accuracy = 0.00000001;

    Camera cam = init_camera();
    Scene scene = init_scene(cam);;

    img.render(scene, accuracy, samples, depth);
    img.save();
}

void tp2() {
    std::srand(std::time(nullptr));

    double alpha = math::degree_to_radian(20);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9
    double zmin = 1000;
    image::Image img(alpha, beta, zmin);

    int samples = 5;
    int depth = 50;
    double accuracy = 0.00000001;

    Camera cam = init_camera();
    Scene scene(cam);
    //scene.ambient_light = 0.2;

    scene.add_light(std::make_shared<Light>(Point3(-7, 10, -10), white, 1.5));

    /* Init blob objects */
    std::vector<shared_object> blob_objects;
    //blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 0, 0), 0.5, orange));
    blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 0, 0), 1, orange));
    blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 1.5, 0), 0.5, light_blue));

    Blob blob(Point3(-2, -2, -2), 6, 0.5, 50, blob_objects);
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, orange));
    //scene.add_object(std::make_shared<Sphere>(Point3(-2, 0, 0), 1, orange));
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, light_blue));
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 1.5, 0), 0.5, light_blue));

    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    //scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));

    blob.compute();

    for (auto& triangle: blob.get_triangles()) {
        scene.add_object(std::make_shared<Triangle>(triangle));
    }

    img.render(scene, accuracy, samples, depth);
    img.save();
}

int main () {
    //tp1();
    tp2();
    return 0;
}
