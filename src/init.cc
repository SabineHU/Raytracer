#include "init.hh"

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
#include "smooth_triangle.hh"
#include "sphere.hh"
#include "triangle.hh"
#include "torus.hh"

#include "point_light.hh"

#include "blob.hh"

#include "math.hh"
#include "random_color.hh"
#include "color.hh"

#include "noise.hh"

#include "init_objects.hh"

image::Image init_image(double angle, double zmin) {
    double alpha = math::degree_to_radian(angle);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9

    return image::Image(alpha, beta, zmin);
}

Camera init_camera() {
    /* Camera */
    //Vect look_from(6, 4, -8);
    Vect look_from(0, 2, -6);
    //Vect look_from(2, 2, -10);
    //Vect look_from(0, 10, -0.0001); // Vu du dessus
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 2.5));
}

void init_objects(Scene& scene) {
    add_plane_black_white(scene);

    //add_ice_cream(scene);
    //add_CSG_fig_1(scene);
    //add_CSG_fig_2(scene);

    //add_sphere_map(scene);
    //add_flower_cube(scene);
    //add_sheep_cube(scene);

    //add_sphere_noise_mapping(scene);
    //add_sphere_turb_mapping(scene);
    //add_sphere_marble_mapping(scene);
    //add_sphere_wood_mapping(scene);

    //add_transparent_sphere(scene);

    //add_sphere_noise(scene);
    //add_sphere_turb(scene);
    //add_sphere_marble(scene);
    //add_sphere_wood(scene);
    //add_sphere_wood_custom_color(scene);

    //add_strip_sphere_spherical(scene);
    //add_strip_vertical_sphere_planar(scene);
    //add_strip_horizontal_sphere_planar(scene);

    //add_torus(scene);
    //add_capsule(scene);
    //add_cube(scene);
    //add_cylinder(scene);
    add_capped_cone(scene);
    //add_cone(scene);
    //add_ellipsoid(scene);
}

void init_objects2(Scene& scene) {
    add_plane_black_white(scene);
}

void init_blob(Scene& scene) {
    /* Create blob objects */
    std::vector<shared_object> blob_objects;
    //blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 0.5, 0), 1, red));
    //blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 2, 0), 0.5, blue));
    auto red_sphere = std::make_shared<Sphere>(Point3(-3, 0.5, 0), 1);
    auto green_sphere = std::make_shared<Sphere>(Point3(0, 0.5, 0), 1);
    auto blue_sphere = std::make_shared<Sphere>(Point3(3, 0.5, 0), 1);

    red_sphere->set_texture(red);
    green_sphere->set_texture(green);
    blue_sphere->set_texture(blue);

    blob_objects.push_back(red_sphere);
    blob_objects.push_back(green_sphere);
    blob_objects.push_back(blue_sphere);

    Blob blob(Point3(0, 0, 0), 11, 1, 75, blob_objects, true);
    blob.compute();

    /* Add triangles to scene */
    for (auto& triangle: blob.get_triangles()) {
        scene.add_object(std::make_shared<SmoothTriangle>(triangle));
    }
}
