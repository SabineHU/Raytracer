#include <vector>
#include <cmath>
#include <iostream>

#include "ray.hh"
#include "camera.hh"
#include "source.hh"
#include "light.hh"
#include "object.hh"
#include "sphere.hh"
#include "image.hh"
#include "plane.hh"
#include "scene.hh"
#include "init.hh"
#include "vector3_op.hh"

int winningObjectIndex(std::vector<double> object_intersections) {
    int index = -1;
    double min = -1;
    for (size_t i = 0; i < object_intersections.size(); ++i) {
        if (object_intersections[i] < 0)
            continue;
        if (min == -1 || object_intersections[i] < min) {
            index = i;
            min = object_intersections[i];
        }
    }
    return index;
}

Color getColorAt(const Scene& scene, Ray& intersection_ray, const shared_object closest_obj, double accuracy) {

    Color winning_object_color = closest_obj->getColor();
    Vect winning_object_normal = closest_obj->getNormalAt(intersection_ray.origin);

    if (winning_object_color.s == 2) {
        // checkered/tile floor pattern

        int square = (int) std::floor(intersection_ray.origin.x) + (int) std::floor(intersection_ray.origin.z);
        if ((square % 2) == 0) {
            // black tile
            winning_object_color = Color(0, 0, 0, winning_object_color.s);
        }
        else {
            // white tile
            winning_object_color = Color(1, 1, 1, winning_object_color.s);
        }
    }

    Color final_color = winning_object_color * scene.ambient_light;

    if (winning_object_color.s > 0 && winning_object_color.s <= 1) {
        // reflection from objects with specular intensity
        Ray reflection_ray = intersection_ray.get_reflection_ray(winning_object_normal);

        // determine what the ray intersects with first
        std::vector<double> reflection_intersections = scene.get_intersections_distance(reflection_ray);
        int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);

        if (index_of_winning_object_with_reflection != -1) {
            // reflection ray missed everthing else
            if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
                // determine the position and direction at the point of intersection with the reflection ray
                // the ray only affects the color if it reflected off something

                Vect reflection_pos = intersection_ray.origin + reflection_ray.direction * reflection_intersections.at(index_of_winning_object_with_reflection);
                Ray reflection_ray(reflection_pos, reflection_ray.direction);

                Color reflection_intersection_color = getColorAt(scene, reflection_ray, scene.objects[index_of_winning_object_with_reflection], accuracy);

                final_color = final_color + (reflection_intersection_color * winning_object_color.s);
            }
        }
    }

    for (const auto& light: scene.lights) {
        Vect light_direction = (light->getLightPosition() - intersection_ray.origin).normalize();

        float cosine_angle = vector::dot(winning_object_normal, light_direction);

        if (cosine_angle > 0) {
            // test for shadows
            bool shadowed = false;

            Vect distance_to_light = (light->getLightPosition() - intersection_ray.origin).normalize();
            float distance_to_light_magnitude = distance_to_light.magnitude();

            Ray shadow_ray(intersection_ray.origin, (light->getLightPosition() - intersection_ray.origin).normalize());

            std::vector<double> secondary_intersections = scene.get_intersections_distance(shadow_ray);

            for (auto inters: secondary_intersections) {
                if (inters > accuracy && inters <= distance_to_light_magnitude) {
                    shadowed = true;
                    break;
                }
            }

            if (shadowed == false) {
                final_color = final_color + (winning_object_color * light->getLightColor() * cosine_angle);

                if (winning_object_color.s > 0 && winning_object_color.s <= 1) {
                    // special [0-1]
                    Ray reflection_ray = intersection_ray.get_reflection_ray(winning_object_normal);
                    double specular = vector::dot(reflection_ray.direction, light_direction);
                    if (specular > 0) {
                        specular = pow(specular, 10);
                        final_color = final_color + (light->getLightColor() * (specular*winning_object_color.s));
                    }
                }

            }

        }
    }

    return final_color.clamp();
}

int main () {
    int width = 640;
    int height = 480;

    image::Image img(width, height);

    double aspectratio = img.get_ratio();
    double accuracy = 0.00000001;
    int samples = 1;

    Scene scene = init_scene();

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {

            // start with a blank pixel
            Color pixel_color(0, 0, 0);

            for (int aax = 0; aax < samples; aax++) {
                for (int aay = 0; aay < samples; aay++) {

                    std::cerr << "\rScanlines remaining: " << width - i - 1 << ' ' << std::flush;
                    double x, y;

                    // create the ray from the camera to this pixel
                    if (samples == 1) {

                        // start with no anti-aliasing
                        if (width > height) {
                            // the image is wider than it is tall
                            x = ((i+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
                            y = ((height - j) + 0.5)/height;
                        }
                        else if (height > width) {
                            // the imager is taller than it is wide
                            x = (i + 0.5)/ width;
                            y = (((height - j) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
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
                            x = ((i + (double)aax/((double)samples - 1))/width)*aspectratio - (((width-height)/(double)height)/2);
                            y = ((height - j) + (double)aax/((double)samples - 1))/height;
                        }
                        else if (height > width) {
                            // the imager is taller than it is wide
                            x = (i + (double)aax/((double)samples - 1))/ width;
                            y = (((height - j) + (double)aax/((double)samples - 1))/height)/aspectratio - (((height - width)/(double)width)/2);
                        }
                        else {
                            // the image is square
                            x = (i + (double)aax/((double)samples - 1))/width;
                            y = ((height - j) + (double)aax/((double)samples - 1))/height;
                        }
                    }

                    Ray cam_ray = scene.camera.get_ray(x, y);

                    std::vector<double> intersections = scene.get_intersections_distance(cam_ray);
                    int index_of_winning_object = winningObjectIndex(intersections);

                    if (index_of_winning_object == -1) {
                        // set the backgroung black
                        pixel_color = Color(0, 0, 0);
                    }
                    else{
                        // index coresponds to an object in our scene
                        if (intersections.at(index_of_winning_object) > accuracy) {
                            // determine the position and direction vectors at the point of intersection

                            Vect intersection_pos = cam_ray.origin + cam_ray.direction * intersections[index_of_winning_object];
                            Ray intersection_ray(intersection_pos, cam_ray.direction);

                            Color intersection_color = getColorAt(scene, intersection_ray, scene.objects[index_of_winning_object], accuracy);

                            pixel_color = pixel_color + intersection_color;
                        }
                    }
                }
            }

            // average the pixel color
            pixel_color = pixel_color / (double) (samples * samples);
            img.set_pixel_color(i, j, pixel_color);
        }
    }

    img.save();
    return 0;
}
