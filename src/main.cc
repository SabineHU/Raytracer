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

int main() {
    std::srand(std::time(nullptr));

    int samples = 15;
    int depth = 50;
    double accuracy = 0.00000001;

    image::Image img = init_image(20, 1000);

    Camera cam = init_camera();
    Scene scene(cam, Color(0.5, 0.5, 0.5));
    init_lights(scene);

    /* TP1 */
    init_objects(scene);

    /* TP2 */
    //init_objects2(scene);
    //init_blob(scene);

    //Scene scene = init_scene1();
    //Scene scene = init_scene2();
    //Scene scene = init_scene3();
    //Scene scene = init_scene4();
    //Scene scene = init_scene5();
    render(img, scene, accuracy, samples, depth);

    img.save();

    return 0;
}
