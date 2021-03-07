#include <iostream>

#include "image.hh"
#include "array.hh"
#include "vector3_op.hh"

namespace image {

Image::Image(int w, int h)
    : width(w), height(h)
{
    pixels = new Point3*[width];
    for (int i = 0; i < width; ++i)
        pixels[i] = new Point3[height];
}

Image::~Image() {
    for (int i = 0; i < width; ++i)
        delete [] pixels[i];
    delete [] pixels;
}

double Image::get_ratio() const {
    return (double) width / (double) height;
}

void Image::save() const {
    std::cout << "P3" << std::endl;
    std::cout << width << ' ' << height << std::endl;
    std::cout << "255" << std::endl;

    for (int j = this->height - 1; j >= 0; --j) {
        for (int i = 0; i < this->width; ++i) {
            std::cout << (int) (pixels[i][j].x * 255) << ' ';
            std::cout << (int) (pixels[i][j].y * 255) << ' ';
            std::cout << (int) (pixels[i][j].z * 255) << std::endl;
        }
    }
}

void Image::set_pixel_color(int i, int j, const Color& color) {
    this->pixels[i][j].x = color.x;
    this->pixels[i][j].y = color.y;
    this->pixels[i][j].z = color.z;

}

static Color getColorAt(const Scene& scene, const Ray& intersection_ray, const shared_object closest_obj, double accuracy) {

    auto x = intersection_ray.origin.x;
    auto y = intersection_ray.origin.y;
    auto z = intersection_ray.origin.z;

    // Color
    Color object_color = closest_obj->texture->get_color(x, y, z);
    Color final_color = closest_obj->texture->get_color(x, y, z) * scene.ambient_light;

    Vect object_normal = closest_obj->get_normal_at(intersection_ray.origin);
    if (closest_obj->specular > 0 && closest_obj->specular <= 1) {
        // reflection from objects with specular intensity
        IntersectionInfo reflection_info;
        Ray reflection_ray = intersection_ray.get_reflection_ray(object_normal);

        if (scene.has_intersection(reflection_ray, reflection_info, accuracy)) {
            Vect reflection_pos = reflection_ray.origin + reflection_ray.direction * reflection_info.distance;
            Ray reflection_ray(reflection_pos, reflection_ray.direction);

            final_color = final_color + getColorAt(scene, reflection_ray, reflection_info.object, accuracy) * closest_obj->specular;
        }
    }

    auto light_color = scene.get_color_with_light(intersection_ray, closest_obj, object_color, accuracy);

    return (final_color + light_color).clamp();
}

void Image::set_index_x_y(double& x, double& y, int samples, int i, int j, int k) {
    auto ratio = this->get_ratio();

    // create the ray from the camera to this pixel
    if (samples == 1) {

        // start with no anti-aliasing
        if (width > height) {
            // the image is wider than it is tall
            x = ((i+0.5)/width)*ratio - (((width-height)/(double)height)/2);
            y = ((height - j) + 0.5)/height;
        }
        else if (height > width) {
            // the imager is taller than it is wide
            x = (i + 0.5)/ width;
            y = (((height - j) + 0.5)/height)/ratio - (((height - width)/(double)width)/2);
        }
        else {
            // the image is square
            x = (i + 0.5)/width;
            y = ((height - j) + 0.5)/height;
        }
    }
    else {
        // anti-aliasing
        if (width > height) {
            // the image is wider than it is tall
            x = ((i + (double)k/((double)samples - 1))/width)*ratio - (((width-height)/(double)height)/2);
            y = ((height - j) + (double)k/((double)samples - 1))/height;
        }
        else if (height > width) {
            // the imager is taller than it is wide
            x = (i + (double)k/((double)samples - 1))/ width;
            y = (((height - j) + (double)k/((double)samples - 1))/height)/ratio - (((height - width)/(double)width)/2);
        }
        else {
            // the image is square
            x = (i + (double)k/((double)samples - 1))/width;
            y = ((height - j) + (double)k/((double)samples - 1))/height;
        }
    }

}

void Image::render(const Scene& scene, double accuracy, int samples) {
    for (int i = 0; i < width; ++i) {
        std::cerr << "\rScanlines remaining: " << width - i - 1 << ' ' << std::flush;
        for (int j = 0; j < height; ++j) {

            Color pixel_color(0, 0, 0);
            for (int k = 0; k < samples; ++k) {

                double x, y;
                this->set_index_x_y(x, y, samples, i, j, k);

                Ray cam_ray = scene.camera.get_ray(x, y);
                IntersectionInfo info;
                if (scene.has_intersection(cam_ray, info, accuracy)) {
                    Vect intersection_pos = cam_ray.origin + cam_ray.direction * info.distance;
                    Ray intersection_ray(intersection_pos, cam_ray.direction);

                    pixel_color = pixel_color + getColorAt(scene, intersection_ray, info.object, accuracy);
                } else {
                    pixel_color = Color(0, 0, 0);
                }

            }

            // average the pixel color
            pixel_color = pixel_color / (double) (samples);
            this->set_pixel_color(i, j, pixel_color);
        }
    }
    std::cerr << "\nDone" << std::endl;
}
}
