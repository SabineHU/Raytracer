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
#include "rectangle_xy.hh"
#include "rectangle_xz.hh"
#include "rectangle_yz.hh"
#include "rotate.hh"
#include "translate.hh"

#include "point_light.hh"

#include "blob.hh"

#include "math.hh"
#include "random.hh"
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
    //Vect look_from(6, 4, -8);
    Vect look_from(0, 2, -8);
    //Vect look_from(2, 2, -10);
    //Vect look_from(0, 15, -0.0001);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(0, 2, -10), light_blue, 1.5));
    //scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 1.75));
}

void init_objects(Scene& scene) {
    auto perlin4 = std::make_shared<PerlinNoise>(2, WOOD);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(perlin4);
    scene.add_object(plane);
}

void init_objects2(Scene& scene) {
    add_plane_black_white(scene);
}

void init_blob(Scene& scene) {
    /* Create blob objects */
    std::vector<shared_object> blob_objects;
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

Scene init_default_scene() {
    Camera cam = init_camera();
    Scene scene(cam, Color(0.5, 0.5, 0.5));
    init_lights(scene);

    /* TP1 */
    init_objects(scene);

    /* TP2 */
    //init_objects2(scene);
    //init_blob(scene);

    //scene.set_fog(50, "square_exp");
    return scene;
}
