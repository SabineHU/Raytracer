#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "init.hh"
#include "raytracer.hh"
#include "scene_parser.hh"

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    Scene scene;
    if (argc == 2) {
        const std::string path = argv[1];
        auto parser = SceneParser(path);
        scene = parser.parse();
    } else
        scene = init_default_scene();

    int samples = 15;
    int depth = 50;
    double accuracy = 0.00000001;
    image::Image img = init_image(20, 1000);

    render(img, scene, accuracy, samples, depth);
    img.save();

    return EXIT_SUCCESS;
}
