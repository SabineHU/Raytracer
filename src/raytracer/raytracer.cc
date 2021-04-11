#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <future>
#include <mutex>

#include "options.hh"
#include "raytracer.hh"
#include "vector3_op.hh"
#include "progress_bar.hh"
#include "image_square.hh"

std::mutex mtx;

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

static Color get_color(const Scene& scene, const IntersectionInfo& info, double accuracy, int depth) {
    if (depth == 0)
        return Color(0, 0, 0);

    Color final_color;
    final_color += info.color * scene.ambient_light * info.ka;
    final_color += compute_diffuse_specular(scene, info, accuracy);

    if (info.texture->type & REFRACTION && info.texture->type & REFLECTION) {
        final_color += compute_refraction_reflection(scene, info, accuracy, depth);

    } else if (info.texture->type & REFLECTION) {
        IntersectionInfo reflection_info;
        Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
        if (scene.has_intersection(reflection_ray, reflection_info, accuracy))
            final_color += get_color(scene, reflection_info, accuracy, depth - 1) * info.attenuation;
    }

    return scene.get_fog_color(final_color, info.dist);
}

void render(image::Image& img, const Scene& scene, double accuracy, int samples, int depth) {
    auto progress = ProgressBar(std::cerr, 100, FRACTION);

    for (int i = 0; i < img.get_width(); ++i) {
        progress.write(i, img.get_width() - 1);

        for (int j = 0; j < img.get_height(); ++j) {

            Color pixel_color(0, 0, 0);
            for (int k = 0; k < samples; ++k) {

                double x, y;
                set_index_x_y(x, y, samples, i, j, k, img.get_width(), img.get_height());

                IntersectionInfo info;
                Ray cam_ray = scene.camera.get_ray(x, y);

                if (scene.has_intersection(cam_ray, info, accuracy)) {
                    pixel_color += get_color(scene, info, accuracy, depth);
                } else {
                    pixel_color += scene.get_background_color(cam_ray);
                }

            }

            pixel_color = pixel_color / (double) (samples);
            img.set_pixel_color(i, j, pixel_color);
        }
    }
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

static double fresnel(const Vect& dir, const Vect& normal, const double ior=1.33) {
    double cos1 = std::max(-1.0, std::min(1.0, vector::dot(dir, normal)));

    double n2 = 1; // air
    double n1 = ior;

    if (cos1 > 0) std::swap(n2, n1);

    double sint = n2 / n1 * sqrtf(std::max(0.0, 1 - cos1 * cos1));
    if (sint >= 1) return 1;

    double cos2 = std::max(0.0, 1 - sint * sint);
    if (cos2 == 0) return 1;

    cos1 = std::abs(cos1);
    cos2 = std::sqrt(cos2);

    double Rs = ((n1 * cos1) - (n2 * cos2)) / ((n1 * cos1) + (n2 * cos2));
    double Rp = ((n2 * cos1) - (n1 * cos2)) / ((n2 * cos1) + (n1 * cos2));

    return (Rs * Rs + Rp * Rp) / 2.0;
}

Color compute_refraction_reflection(const Scene& scene, const IntersectionInfo& info, double accuracy, int depth) {
    Color refract, reflect;
    bool outside = vector::dot(info.ray_out.direction, info.normal) < 0;

    double kr = fresnel(info.ray_out.direction, info.normal, info.ior);
    if (kr < 1) {
        Vect refract_dir = info.ray_out.get_refraction_dir(info.normal, info.ior);
        Vect refract_orig = outside ? info.point - info.normal : info.point + info.normal;

        IntersectionInfo refraction_info;
        Ray refraction_ray(refract_orig, refract_dir);
        if (scene.has_intersection(refraction_ray, refraction_info, accuracy))
            refract += get_color(scene, refraction_info, accuracy, depth - 1);
    }

    Vect reflect_dir = info.ray_out.get_reflection_dir(info.normal);
    Vect reflect_orig = outside ? info.point + info.normal : info.point - info.normal;

    IntersectionInfo reflection_info;
    Ray reflection_ray(reflect_orig, reflect_dir);
    if (scene.has_intersection(reflection_ray, reflection_info, accuracy))
        reflect += get_color(scene, reflection_info, accuracy, depth - 1);

    if (info.texture->type & TRANSPARENT)
        return (reflect * kr + refract * (1 - kr) * info.kt) * info.color;

    return reflect * kr + refract * (1 - kr);
}

void render_square(const ImageSquare square, image::Image& img, const Scene& scene, double accuracy, int samples, int depth, int& nb_written_pixels, const ProgressBar& progress) {
    int nb_pixels = img.get_width() * img.get_height();
    for (int i = square.i_min; i < square.i_max; ++i) {
        for (int j = square.j_min; j < square.j_max; ++j) {

            Color pixel_color(0, 0, 0);
            for (int k = 0; k < samples; ++k) {

                double x, y;
                set_index_x_y(x, y, samples, i, j, k, img.get_width(), img.get_height());

                IntersectionInfo info;
                Ray cam_ray = scene.camera.get_ray(x, y);

                if (scene.has_intersection(cam_ray, info, accuracy))
                    pixel_color += get_color(scene, info, accuracy, depth);
                else
                    pixel_color += scene.get_background_color(cam_ray);
            }

            pixel_color = pixel_color / (double) (samples);
            img.set_pixel_color(i, j, pixel_color);

            if (progress.get_type() != NO_PRINT) {
                mtx.lock();
                ++nb_written_pixels;
                progress.write(nb_written_pixels, nb_pixels);
                mtx.unlock();
            }
        }
    }
}


static std::vector<ImageSquare> compute_image_square(const image::Image& img, int cores) {
    std::vector<ImageSquare> squares;

    int square_width = img.get_width() / cores * 2;
    int square_height = img.get_height() / 2;

    if (img.get_width() % square_width != 0)
        square_width += 1;

    for (int i = 0; i < img.get_width(); i += square_width) {
        int i_max = std::min(i + square_width, img.get_width());
        squares.emplace_back(i, 0, i_max, square_height);
        squares.emplace_back(i, square_height, i_max, img.get_height());
    }

    return squares;
}

void render_multithreading(image::Image& img, const Scene& scene, double accuracy, int samples, int depth) {
    int cores = std::thread::hardware_concurrency();
    auto squares = compute_image_square(img, cores);

    int nb_written_pixels = 0;
    auto progress = ProgressBar(std::cerr, 100, FRACTION);

    std::vector<std::future<void>> futures;
    for (int i = 0; i < cores; i++)
        futures.push_back(std::async(std::launch::async, render_square, squares[i], std::ref(img), std::ref(scene), accuracy, samples, depth, std::ref(nb_written_pixels), std::cref(progress)));

    for (auto &f : futures)
        f.get();
}
