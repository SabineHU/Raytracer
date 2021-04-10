#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "init.hh"
#include "raytracer.hh"
#include "scene_parser.hh"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Missing one argument!\n";

        return EXIT_FAILURE;
    }

    std::srand(std::time(nullptr));

    auto path = argv[1];
    auto parser = SceneParser(path);
    auto scene = parser.parse();

    int samples = 15;
    int depth = 50;
    double accuracy = 0.00000001;

    image::Image img = init_image(20, 1000);

    render(img, scene, accuracy, samples, depth);

    img.save();

    return EXIT_SUCCESS;
}
