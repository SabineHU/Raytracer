#include <iostream>
#include <cmath>

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

Image::Image(double alpha, double beta, double zmin)
{
    width = 2 * zmin * std::tan(beta / 2.0);
    height = 2 * zmin * std::tan(alpha / 2.0);

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

void Image::set_index_x_y(double& x, double& y, double samples, int i, int j, double k) {
    auto ratio = this->get_ratio();

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
    Color final_color = scene.ambient_light != 0 ? info.color * scene.ambient_light : info.color;
    double specular = info.texture->specular;

    if (info.texture->type == DIFFUSE) {
    //    for (const auto& light: scene.get_lights()) {
    //        Vect lightDir = (light->get_light_position() - info.point);
    //        float lightDistance2 = vector::dot(lightDir, lightDir);
    //        lightDir = lightDir.normalize();
    //        bool vis = !scene.has_shadow(Ray(shadowPointOrig, lightDir), lightDistance2, accuracy);

    //        // compute the pattern
    //        float angle = math::degree_to_radian(45);
    //        float s = hitTexCoordinates.x * cos(angle) - hitTexCoordinates.y * sin(angle);
    //        float t = hitTexCoordinates.y * cos(angle) + hitTexCoordinates.x * sin(angle);
    //        float scaleS = 20, scaleT = 20;
    //        float pattern = (modulo(s * scaleS) < 0.5);
    //        final_color += vis * pattern * light->get_intensity() * std::max(0.f, vector::dot(hitNormal, lightDir * -1));
    //    }
    //    return final_color.clamp();
    //}

    //if (info.texture->type == DIFFUSE_GLOSSY) {

        Vect lightAmt, specularColor;
        Vect shadowPointOrig = info.point;

        for (const auto& light: scene.get_lights()) {
            Vect lightDir = (light->get_light_position() - info.point);
            float lightDistance2 = vector::dot(lightDir, lightDir);
            lightDir = lightDir.normalize();
            double LdotN = vector::dot(lightDir, info.normal);
            if (LdotN > 0) {
                // is the point in shadow, and is the nearest occluding object closer to the object than the light itself?

                if (!scene.has_shadow(Ray(shadowPointOrig, lightDir), lightDistance2, accuracy)) {

                    lightAmt += light->get_light_color() * light->get_intensity() * LdotN;
                    Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
                    Vect reflectionDirection = get_reflection_dir(info.ray_out.direction, info.normal);
                    // OBJ SPECULAR NOT TEXTURE SPECULAR

                    auto sp = vector::dot(reflection_ray.direction, lightDir);
                    if (sp > 0 && specular > 0 && specular <= 1) {
                        //Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
                        //double specular = vector::dot(reflection_ray.direction, light_direction);

                        specularColor += powf(sp, specular) * light->get_intensity();
                    }
                }
            }
            //specularColor += powf(std::max(0.0, -vector::dot(reflectionDirection, info.ray_out.direction)), specular) * light->get_intensity();
            // Good value for specular is 50
        }

        final_color = lightAmt * info.color * 1 + specularColor * 1;
    //    //final_color = lightAmt * info.kd + specularColor * info.ks;

    }

    //if (specular > 0 && specular <= 1) {
    //    // reflection from objects with specular intensity
    //    IntersectionInfo reflection_info;
    //    Ray reflection_ray = info.ray_out.get_reflection_ray(info.normal);
    //    if (scene.has_intersection(reflection_ray, reflection_info, accuracy))
    //        final_color += getColorAt(scene, reflection_info, accuracy, depth - 1) * specular;
    //}

    final_color = Vect(0, 0, 0);
    auto light_color = scene.get_color_with_light(info, accuracy);

    return (final_color + light_color).clamp();
}


void Image::render(const Scene& scene, double accuracy, int samples, int depth) {
    for (int i = 0; i < width; ++i) {
        std::cerr << "\rScanlines remaining: " << width - i - 1 << ' ' << std::flush;
        for (int j = 0; j < height; ++j) {

            Color pixel_color(0, 0, 0);
            for (int k = 0; k < samples; ++k) {

                double x, y;
                this->set_index_x_y(x, y, samples, i, j, k);

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
            this->set_pixel_color(i, j, pixel_color);
        }
    }
    std::cerr << "\nDone" << std::endl;
}
}
