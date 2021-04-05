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
#include "rectangle_xy.hh"
#include "rectangle_xz.hh"
#include "rectangle_yz.hh"
#include "rotate.hh"
#include "translate.hh"

#include "point_light.hh"

#include "blob.hh"

#include "math.hh"
#include "random_color.hh"
#include "color.hh"

#include "noise.hh"

#include "init_objects.hh"

#include "vector3_op.hh"

#include "polygon.hh"
#include "loader.hh"

image::Image init_image(double angle, double zmin) {
    double alpha = math::degree_to_radian(angle);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9

    return image::Image(alpha, beta, zmin);
}

Camera init_camera() {
    /* Camera */
    //Vect look_from(6, 4, -8);
    Vect look_from(0, 2, -8);
    //Vect look_from(2, 2, -10);
    //Vect look_from(0, 10, -0.0001); // Vu du dessus
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(0, 2, -10), light_blue, 1.5));
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

void init_objects(Scene& scene) {
    //add_ground_plane(scene);
    //add_water_plane(scene);
    //add_water_plane2(scene);
    //add_water_plane_reflection(scene);
    //add_plane_black_white(scene);
    add_holed_plane(scene);

    //auto mat = parse_materials("objs/boat.mtl");
    //auto p = parse_obj_to_polygon("objs/boat.obj", mat);
    //scene.add_object(std::make_shared<Polygon>(p));

    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(0, .5, -4), .5);
    obj1->set_texture(lambertian_random);
    obj1->add_bump_mapping(Noise(WOOD, 10));
    scene.add_object(obj1);

    //std::vector<shared_object> triangles;
    //triangles.push_back(std::make_shared<Triangle>(Point3(0.95106, 0.30902, 0), Point3(0.30898, 0.42527, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(0.30898, 0.42527, 0), Point3(0, 1, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(0, 1, 0), Point3(-0.30898, 0.42527, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(-0.30989, 0.42527, 0), Point3(-0.95106, 0.30902, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(-0.95106, 0.30902, 0), Point3(-0.49993, -0.16244, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(-0.49993, -0.16244, 0), Point3(-0.58779, -0.80902, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(-0.58779, -0.80902, 0), Point3(0, -0.52566, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(0, -0.52566, 0), Point3(0.58779, -0.80902, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(0.58779, -0.80902, 0), Point3(0.49993, -0.16244, 0), Point3(0, 0, 0)));
    //triangles.push_back(std::make_shared<Triangle>(Point3(0.49993, -0.16244, 0), Point3(0.95106, 0.30902, 0), Point3(0, 0, 0)));

    //for (auto t : triangles) {
    //    auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    //    t->set_texture(lambertian_random);
    //    scene.add_object(t);
    //}

    add_ice_cream(scene);
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

    //auto perlin = std::make_shared<PerlinNoise>(2, RAINBOW, r_random::random_color(), r_random::random_color());
    //auto p1 = std::make_shared<Sphere>(Point3(0, 1, 0), 2);
    //p1->set_texture(perlin);
    //scene.add_object(p1);

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
    //add_capped_cone(scene);
    //add_cone(scene);
    //add_ellipsoid(scene);
    //add_rectangle_rotated(scene);
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

    Blob blob(Point3(0, 0, 0), 11, .5, 75, blob_objects, true);
    blob.compute();

    /* Add triangles to scene */
    for (auto& triangle: blob.get_triangles()) {
        scene.add_object(std::make_shared<SmoothTriangle>(triangle));
    }
}
