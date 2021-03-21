#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "init.hh"

int main () {
    int samples = 5;
    int depth = 50;
    double accuracy = 0.00000001;

    image::Image img = init_image(20, 1000);
    Camera cam = init_camera();

    Scene scene(cam, 0.2);
    init_lights(scene);

    /* TP1 */
    init_objects(scene);

    /* TP2 */
    //init_objects2(scene);
    //init_blob(scene);

    img.render(scene, accuracy, samples, depth);
    img.save();

    return 0;
}
