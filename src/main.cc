#include <vector>
#include <cmath>
#include <iostream>

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

int main () {
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
    return 0;
}
