#pragma once

#include "image.hh"
#include "scene.hh"

void render(image::Image& img, const Scene& scene, double accuracy, int samples, int depth);

Color compute_diffuse_specular(const Scene& scene, const IntersectionInfo& info, double accuracy);
