#pragma once

#include "lambertian.hh"
#include "metal.hh"
#include "checkerboard.hh"
#include "image_texture.hh"
#include "strip.hh"
#include "perlin_noise.hh"

#include "object.hh"
#include "cone.hh"
#include "capped_cone.hh"
#include "cube.hh"
#include "capsule.hh"
#include "CSG.hh"
#include "cylinder.hh"
#include "ellipsoid.hh"
#include "plane.hh"
#include "plane_holed.hh"
#include "smooth_triangle.hh"
#include "sphere.hh"
#include "triangle.hh"
#include "rectangle_xy.hh"
#include "rectangle_xz.hh"
#include "rectangle_yz.hh"

#include "rotate.hh"
#include "translate.hh"

#include "blob.hh"
#include "random.hh"
#include "color.hh"

#include "noise.hh"

#include "scene.hh"

/* Plane */
void add_ground_plane(Scene& scene);
void add_water_plane(Scene& scene);
void add_water_plane2(Scene& scene);
void add_water_plane_reflection(Scene& scene);
void add_plane_black_white(Scene& scene);
void add_holed_plane(Scene& scene);
void add_cloudy_plane(Scene& scene);

/* CSG */
void add_ice_cream(Scene& scene);
void add_CSG_fig_1(Scene& scene);
void add_CSG_fig_2(Scene& scene);

/* Image mapping */
void add_sphere_map(Scene& scene);
void add_flower_cube(Scene& scene);
void add_sheep_cube(Scene& scene);

/* Bump mapping */
void add_sphere_noise_mapping(Scene& scene);
void add_sphere_turb_mapping(Scene& scene);
void add_sphere_marble_mapping(Scene& scene);
void add_sphere_wood_mapping(Scene& scene);

/* Refraction & reflection */
void add_transparent_sphere(Scene& scene);

/* Perlin */
void add_sphere_noise(Scene& scene);
void add_sphere_turb(Scene& scene);
void add_sphere_marble(Scene& scene);
void add_sphere_wood(Scene& scene);
void add_sphere_wood_custom_color(Scene& scene);
void add_sphere_rainbow(Scene& scene);

/* Strip */
void add_strip_sphere_spherical(Scene& scene);
void add_strip_vertical_sphere_planar(Scene& scene);
void add_strip_horizontal_sphere_planar(Scene& scene);

/* Primitives */
void add_capsule(Scene& scene);
void add_cube(Scene& scene);
void add_cylinder(Scene& scene);
void add_capped_cone(Scene& scene);
void add_cone(Scene& scene);
void add_ellipsoid(Scene& scene);

/* Rotation & translation */
void add_rectangle_rotated(Scene& scene);
