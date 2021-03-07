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


int main () {
    /* Image */
    int width = 640;
    int height = 480;
    image::Image img(width, height);

    int samples = 5;
    int depth = 50;
    double accuracy = 0.00000001;
    Scene scene = init_scene();

    img.render(scene, accuracy, samples, depth);
    img.save();
    return 0;
}
