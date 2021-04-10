#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdelete-abstract-non-virtual-dtor"

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

#include "scene_parser.hh"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Missing one argument!\n";

        return EXIT_FAILURE;
    }

    auto path = argv[1];
    SceneParser parser = SceneParser(path);

    auto scene = parser.parse();

    std::srand(std::time(nullptr));

    int samples = 15;
    int depth = 50;
    double accuracy = 0.00000001;

    image::Image img = init_image(20, 1000);

    render(img, scene, accuracy, samples, depth);

    img.save();

    return EXIT_SUCCESS;
}

#pragma GCC diagnostic pop
