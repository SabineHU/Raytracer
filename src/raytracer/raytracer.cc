#include <iostream>

#include "raytracer.hh"

static void set_index_x_y(double& x, double& y, double samples, int i, int j, double k,
        double width, double height) {

    double ratio = width / height;
    double dheight = height * 2;
    double dwidth = width * 2;

    double value = 0.5;
    if (samples != 1) {
        // anti aliasing
        value = k / (samples - 1);
    }

    if (width > height) {
        x = (i + value) / width * ratio - (width - height) / dheight;
        y = ((height - j) + value)/height;
    } else if (height > width) {
        x = (i + value)/width;
        y = (height - j + value) / height / ratio - (height - width) / dwidth;
    } else {
        x = (i + value)/width;
        y = ((height - j) + value)/height;
    }
}

static Color getColorAt(const Scene& scene, const IntersectionInfo& info, double accuracy, int depth) {
    if (depth == 0)
        return Color(0, 0, 0);

    // Color
    Color final_color = info.color * scene.ambient_light * info.ka;
    final_color += scene.get_color_with_light(info, accuracy);

    if (info.texture->type & REFLECTION) {
        IntersectionInfo reflection_info;
        Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
        if (scene.has_intersection(reflection_ray, reflection_info, accuracy))
            final_color += getColorAt(scene, reflection_info, accuracy, depth - 1);
    }
    //if (info.texture->type & REFRACTION) {
    //    std::cerr << "Refraction" << std::endl;
    //}

    return final_color.clamp();
}

void render(image::Image& img, const Scene& scene, double accuracy, int samples, int depth) {
    for (int i = 0; i < img.get_width(); ++i) {
        std::cerr << "\rScanlines remaining: " << img.get_width() - i - 1 << ' ' << std::flush;
        for (int j = 0; j < img.get_height(); ++j) {

            Color pixel_color(0, 0, 0);
            for (int k = 0; k < samples; ++k) {

                double x, y;
                set_index_x_y(x, y, samples, i, j, k, img.get_width(), img.get_height());

                IntersectionInfo info;
                Ray cam_ray = scene.camera.get_ray(x, y);

                if (scene.has_intersection(cam_ray, info, accuracy)) {
                    pixel_color += getColorAt(scene, info, accuracy, depth);
                } else {
                    pixel_color += Color(0, 0, 0.3);
                }

            }

            // average the pixel color
            pixel_color = pixel_color / (double) (samples);
            img.set_pixel_color(i, j, pixel_color);
        }
    }
    std::cerr << "\nDone" << std::endl;
}
