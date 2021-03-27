#include <iostream>

#include "raytracer.hh"
#include "vector3_op.hh"

static void set_index_x_y(double& x, double& y, double samples, int i, int j, double k,
        double width, double height) {

    double ratio = width / height;
    double dheight = height * 2;
    double dwidth = width * 2;
    double value = 0.5;

    // anti aliasing
    if (samples != 1)
        value = k / (samples - 1);

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
    final_color += compute_diffuse_specular(scene, info, accuracy);

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

static Color compute_one_light(const IntersectionInfo& info, const shared_light light,
        const Vect& light_direction, double cos) {
    Color light_amt = light->get_light_color() * cos * light->get_intensity();
    Color specular_color;
    if (info.specular > 0) {
        Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
        double specular = vector::dot(reflection_ray.direction, light_direction);
        if (specular > 0)
            specular_color += powf(specular, info.specular) * light->get_intensity();
    }
    return light_amt * info.color * info.kd + specular_color * info.ks;
}

Color compute_diffuse_specular(const Scene& scene, const IntersectionInfo& info, double accuracy) {
    Color res_color;
    for (const auto& light: scene.get_lights()) {
        Vect light_direction = light->get_light_position() - info.ray_out.origin;
        Vect light_direction_n = light_direction.normalize();
        float cosine_angle = vector::dot(info.normal, light_direction_n);

        if (cosine_angle > 0) {
            double distance_to_light_magnitude = light_direction.magnitude();
            Ray shadow_ray(info.ray_out.origin, light_direction_n);

            if (!scene.has_shadow(shadow_ray, distance_to_light_magnitude, accuracy)) {
                res_color += compute_one_light(info, light, light_direction_n, cosine_angle);
            }
        }
    }
    return res_color;
}
