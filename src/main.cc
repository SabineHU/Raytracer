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


#define AADEPTH 1

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

Color getColorAt(Vect intersection_position, Vect intersecting_ray_direction, std::vector<Object*> scene_objects, int index_of_winning_object, std::vector<Source*> light_sources, double accuracy, double ambientlight) {

    Color winning_object_color = scene_objects[index_of_winning_object]->getColor();
    Vect winning_object_normal = scene_objects[index_of_winning_object]->getNormalAt(intersection_position);

    if (winning_object_color.s == 2) {
        // checkered/tile floor pattern

        int square = (int)std::floor(intersection_position.x) + (int)std::floor(intersection_position.z);
        if ((square % 2) == 0) {
            // black tile
            winning_object_color = Color(0, 0, 0, winning_object_color.s);
        }
        else {
            // white tile
            winning_object_color = Color(1, 1, 1, winning_object_color.s);
        }
    }

    Color final_color = winning_object_color * ambientlight;

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

        for (const auto& obj: scene_objects) {
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

                Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientlight);

                final_color = final_color + (reflection_intersection_color * winning_object_color.s);
            }
        }
    }

    for (const auto& light: light_sources) {
        Vect light_direction = (light->getLightPosition() - intersection_position).normalize();

        float cosine_angle = winning_object_normal.dotProduct(light_direction);

        if (cosine_angle > 0) {
            // test for shadows
            bool shadowed = false;

            Vect distance_to_light = (light->getLightPosition() - intersection_position).normalize();
            float distance_to_light_magnitude = distance_to_light.magnitude();

            Ray shadow_ray (intersection_position, (light->getLightPosition() - intersection_position).normalize());

            std::vector<double> secondary_intersections;

            for (const auto& obj: scene_objects) {
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
    double ambientlight = 0.2;
    double accuracy = 0.00000001;

    Vect O(0,0,0);
    Vect X(1,0,0);
    Vect Y(0,1,0);
    Vect Z(0,0,1);

    Vect look_from(3, 1.5, -4);
    Vect look_at(0, 0, 0);
    Scene scene(look_from, look_at);

    Vect light_position (-7,10,-10);
    Light scene_light (light_position, Color(1, 1, 1, 0));
    std::vector<Source*> light_sources;
    light_sources.push_back(dynamic_cast<Source*>(&scene_light));

    // scene objects
    Sphere scene_sphere (Point3(0, 0, 0), 1, Color(0.5, 1, 0.5, 0.3));
    Sphere scene_sphere2 (Point3(1.74, -0.25, 0), 0.5, Color(0.5, 0.25, 0.25, 0));
    Plane scene_plane (Point3(0, 1, 0), -1, Color(1, 1, 1, 2));
    std::vector<Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
    scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere2));
    scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

    double xamnt, yamnt;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            // start with a blank pixel
            Color pixel_color(0, 0, 0);

            for (int aax = 0; aax < AADEPTH; aax++) {
                for (int aay = 0; aay < AADEPTH; aay++) {

                    std::cerr << "\rScanlines remaining: " << width - x - 1 << ' ' << std::flush;

                    // create the ray from the camera to this pixel
                    if (AADEPTH == 1) {

                        // start with no anti-aliasing
                        if (width > height) {
                            // the image is wider than it is tall
                            xamnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
                            yamnt = ((height - y) + 0.5)/height;
                        }
                        else if (height > width) {
                            // the imager is taller than it is wide
                            xamnt = (x + 0.5)/ width;
                            yamnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
                        }
                        else {
                            // the image is square
                            xamnt = (x + 0.5)/width;
                            yamnt = ((height - y) + 0.5)/height;
                        }
                    }
                    else {
                        // anti-aliasing
                        if (width > height) {
                            // the image is wider than it is tall
                            xamnt = ((x + (double)aax/((double)AADEPTH - 1))/width)*aspectratio - (((width-height)/(double)height)/2);
                            yamnt = ((height - y) + (double)aax/((double)AADEPTH - 1))/height;
                        }
                        else if (height > width) {
                            // the imager is taller than it is wide
                            xamnt = (x + (double)aax/((double)AADEPTH - 1))/ width;
                            yamnt = (((height - y) + (double)aax/((double)AADEPTH - 1))/height)/aspectratio - (((height - width)/(double)width)/2);
                        }
                        else {
                            // the image is square
                            xamnt = (x + (double)aax/((double)AADEPTH - 1))/width;
                            yamnt = ((height - y) + (double)aax/((double)AADEPTH - 1))/height;
                        }
                    }

                    Vect cam_ray_origin = scene.camera.getCameraPosition();
                    Vect cam_ray_direction = (scene.camera.camdir + scene.camera.camright * (xamnt - 0.5) + scene.camera.camdown * (yamnt - 0.5)).normalize();

                    Ray cam_ray(cam_ray_origin, cam_ray_direction);

                    std::vector<double> intersections;

                    for (const auto& obj : scene_objects) {
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

                            Vect intersection_position = cam_ray_origin + (cam_ray_direction * intersections[index_of_winning_object]);
                            Vect intersecting_ray_direction = cam_ray_direction;

                            Color intersection_color = getColorAt(intersection_position, intersecting_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientlight);

                            pixel_color = pixel_color + intersection_color;
                        }
                    }
                }
            }

            // average the pixel color
            pixel_color = pixel_color / (double) (AADEPTH * AADEPTH);

            img.pixels[x][y].x = pixel_color.x;
            img.pixels[x][y].y = pixel_color.y;
            img.pixels[x][y].z = pixel_color.z;
        }
    }

    img.save();
    return 0;
}
