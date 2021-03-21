#pragma once

#include "scene.hh"
#include "image.hh"

image::Image init_image(double angle, double zmin);
Camera init_camera();

void init_lights(Scene& scene);

void init_objects(Scene& scene);
void init_objects2(Scene& scene);

void init_blob(Scene& scene);
