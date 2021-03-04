#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>

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

Color getColorAt(const Scene& scene, Vect intersection_position, Vect intersecting_ray_direction, int index_of_winning_object, double accuracy) {

    Color winning_object_color = scene.objects[index_of_winning_object]->getColor();
    Vect winning_object_normal = scene.objects[index_of_winning_object]->getNormalAt(intersection_position);

    if (winning_object_color.s == 2) {
        // checkered/tile floor pattern

        int square = (int) std::floor(intersection_position.x) + (int) std::floor(intersection_position.z);
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
        double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());
        Vect scalar1 = winning_object_normal * dot1;
        Vect add1 = scalar1 + intersecting_ray_direction;
        Vect scalar2 = add1 * 2;
        Vect add2 = intersecting_ray_direction.negative() + scalar2;
        Vect reflection_direction = add2.normalize();

        Ray reflection_ray (intersection_position, reflection_direction);

        // determine what the ray intersects with first
        std::vector<double> reflection_intersections;

        for (const auto& obj: scene.objects) {
            reflection_intersections.push_back(obj->findIntersection(reflection_ray));
        }

        int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);

        if (index_of_winning_object_with_reflection != -1) {
            // reflection ray missed everthing else
            if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
                // determine the position and direction at the point of intersection with the reflection ray
                // the ray only affects the color if it reflected off something

                Vect reflection_intersection_position = intersection_position + reflection_direction * reflection_intersections.at(index_of_winning_object_with_reflection);
                Vect reflection_intersection_ray_direction = reflection_direction;

                Color reflection_intersection_color = getColorAt(scene, reflection_intersection_position, reflection_intersection_ray_direction, index_of_winning_object_with_reflection, accuracy);

                final_color = final_color + (reflection_intersection_color * winning_object_color.s);
            }
        }
    }

    for (const auto& light: scene.lights) {
        Vect light_direction = (light->getLightPosition() - intersection_position).normalize();

        float cosine_angle = winning_object_normal.dotProduct(light_direction);

        if (cosine_angle > 0) {
            // test for shadows
            bool shadowed = false;

            Vect distance_to_light = (light->getLightPosition() - intersection_position).normalize();
            float distance_to_light_magnitude = distance_to_light.magnitude();

            Ray shadow_ray (intersection_position, (light->getLightPosition() - intersection_position).normalize());

            std::vector<double> secondary_intersections;

            for (const auto& obj: scene.objects) {
                secondary_intersections.push_back(obj->findIntersection(shadow_ray));
            }

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
                    double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());
                    Vect scalar1 = winning_object_normal * dot1;
                    Vect add1 = scalar1 + intersecting_ray_direction;
                    Vect scalar2 = add1 * 2;
                    Vect add2 = intersecting_ray_direction.negative() + scalar2;
                    Vect reflection_direction = add2.normalize();

                    double specular = reflection_direction.dotProduct(light_direction);
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

                    std::vector<double> intersections;

                    for (const auto& obj : scene.objects) {
                        intersections.push_back(obj->findIntersection(cam_ray));
                    }

                    int index_of_winning_object = winningObjectIndex(intersections);

                    if (index_of_winning_object == -1) {
                        // set the backgroung black
                        pixel_color = Color(0, 0, 0);
                    }
                    else{
                        // index coresponds to an object in our scene
                        if (intersections.at(index_of_winning_object) > accuracy) {
                            // determine the position and direction vectors at the point of intersection

                            Vect intersection_position = cam_ray.origin + cam_ray.direction * intersections[index_of_winning_object];
                            Vect intersecting_ray_direction = cam_ray.direction;

                            Color intersection_color = getColorAt(scene, intersection_position, intersecting_ray_direction, index_of_winning_object, accuracy);

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
