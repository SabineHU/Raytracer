#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "init.hh"
#include "raytracer.hh"

#include "scene1.hh"
#include "scene2.hh"
#include "scene3.hh"
#include "scene4.hh"
#include "scene5.hh"
#include "scene6.hh"

int main() {
    std::srand(std::time(nullptr));

    int samples = 15;
    int depth = 50;
    double accuracy = 0.00000001;

    image::Image img = init_image(20, 1000);

    Scene scene = init_default_scene();

    //Scene scene = init_scene1();
    //Scene scene = init_scene2();
    //Scene scene = init_scene3();
    //Scene scene = init_scene4();
    //Scene scene = init_scene5();
    //Scene scene = init_scene6();

    render(img, scene, accuracy, samples, depth);

    img.save();

    return 0;
}
