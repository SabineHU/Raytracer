#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "camera.hh"
#include "light.hh"
#include "image.hh"
#include "scene.hh"
#include "init.hh"
#include "math.hh"

void tp1(double angle, int samples, int depth, double accuracy) {
    double alpha = math::degree_to_radian(angle);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9
    double zmin = 1000;
    image::Image img(alpha, beta, zmin);

    Camera cam = init_camera();
    Scene scene = init_scene(cam);;

    img.render(scene, accuracy, samples, depth);
    img.save();
}

void tp2(double angle, int samples, int depth, double accuracy) {
    double alpha = math::degree_to_radian(angle);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9
    double zmin = 1000;
    image::Image img(alpha, beta, zmin);

    Camera cam = init_camera();
    Scene scene = init_scene2(cam);;

    img.render(scene, accuracy, samples, depth);
    img.save();
}

int main () {

    double angle = 20;
    int samples = 5;
    int depth = 15; //50
    double accuracy = 0.00000001;

    //std::srand(std::time(nullptr));

    //tp1(angle, samples, depth, accuracy);
    tp2(angle, samples, depth, accuracy);
    return 0;
}
