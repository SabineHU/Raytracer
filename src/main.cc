#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "init.hh"
#include "options.hh"
#include "raytracer.hh"
#include "scene_parser.hh"

#include "scene1.hh"
#include "scene2.hh"
#include "scene3.hh"
#include "scene4.hh"
#include "scene5.hh"
#include "scene6.hh"

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    Scene scene;
    if (argc == 2) {
        const std::string path = argv[1];
        auto parser = SceneParser(path);
        scene = parser.parse();
    } else
        scene = init_scene1();
        //scene = init_scene2();
        //scene = init_scene3();
        //scene = init_scene4();
        //scene = init_scene5();
        //scene = init_scene6();
        //scene = init_default_scene();

    image::Image img = init_image(20, 1000);

    if (MULTITHREADING)
        render_multithreading(img, scene, ACCURACY, SAMPLES, DEPTH);
    else
        render(img, scene, ACCURACY, SAMPLES, DEPTH);

    img.save();
    return EXIT_SUCCESS;
}
