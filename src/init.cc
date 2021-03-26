#include "init.hh"

#include "unique.hh"
#include "metal.hh"
#include "checkerboard.hh"
#include "image_texture.hh"

#include "object.hh"
#include "cone.hh"
#include "capped_cone.hh"
#include "cube.hh"
#include "capsule.hh"
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

image::Image init_image(double angle, double zmin) {
    double alpha = math::degree_to_radian(angle);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9

    return image::Image(alpha, beta, zmin);
}

Camera init_camera() {
    /* Camera */
    // used for make check
    //Vect look_from(6, 4, -8);
    Vect look_from(0, 1.5, -4);
    //Vect look_from(0, 0, -4); // Vu horizon
    //Vect look_from(0, 10, -0.0001); // Vu du dessus
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 2.5));
}

void init_objects(Scene& scene) {
    /* Textures */
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto board_black_blue = std::make_shared<CheckerBoard>(black, blue, 0.3);
    auto unique_green = std::make_shared<Unique>(light_green, 0.2);
    auto unique_orange = std::make_shared<Unique>(orange, 0);
    auto unique_red = std::make_shared<Metal>(dark_red);
    auto image_texture = std::make_shared<ImageTexture>("textures/quadrillage.ppm");

    auto metal_random = std::make_shared<Metal>(r_random::random_color());
    auto unique_random = std::make_shared<Unique>(r_random::random_color());

    /* Scene objects */
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, board_black_blue));
    //scene.add_object(std::make_shared<Cube>(Point3(0, -1, 0), 2, unique_orange));

    //scene.add_object(std::make_shared<Cone>(Point3(1.75, -1, 0), 1, 2.5, unique_green));
    //scene.add_object(std::make_shared<CappedCone>(Point3(2, 0, 0), Point3(0, 1, 0), 1, 0.5, unique_green));
    //scene.add_object(std::make_shared<Torus>(Point3(3, 1, 0), board_black_blue));
    //scene.add_object(std::make_shared<Triangle>(Point3(3, 0, 0), Point3(0, 3, 0), Point3(0, 0, 3), purple));
    //scene.add_object(std::make_shared<Sphere>(Point3(2, 0, 0), 1, unique_green));

    //scene.add_object(std::make_shared<Sphere>(Point3(-2, 0, 0), 1, unique_red));
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, board_black_blue));
    //scene.add_object(std::make_shared<Sphere>(Point3(2, 0, 0), 1, unique_orange));

    scene.add_object(std::make_shared<Sphere>(Point3(0, 1.5, 0), .5, metal_random));
    scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, image_texture));

    //scene.add_object(std::make_shared<Capsule>(Point3(-2, 0, -3), Point3(2, 1, 0), 1, unique_orange));
    //scene.add_object(std::make_shared<Ellipsoid>(Point3(-2, 0, -3), Point3(1.5, 0.5, 2), unique_orange));
    //scene.add_object(std::make_shared<Cylinder>(Point3(-2, -1, 0), Point3(2, 1, 0), 1, unique_orange));
    //scene.add_object(std::make_shared<Cylinder>(Point3(2, -1, 0), Point3(2, 1, 0), 1, unique_orange));
    scene.add_object(std::make_shared<Cone>(Point3(2, -1, 0), 1, 2, unique_green));

    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));
}

void init_objects2(Scene& scene) {
    /* Textures */
    auto board_black_blue = std::make_shared<CheckerBoard>(black, blue, 0.3);
    auto unique_green = std::make_shared<Unique>(light_green, 0.05);
    auto unique_red = std::make_shared<Metal>(dark_red);

    /* Scene objects */
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    scene.add_object(std::make_shared<Plane>(Point3(0, 1, 0), -1, board_black_white));

    //scene.add_object(std::make_shared<Sphere>(Point3(0.5, 0, 0), 1, light_blue));
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, orange));
    //scene.add_object(std::make_shared<Cone>(Point3(-7, -1, 1), 1, 2.5, unique_green));
    //scene.add_object(std::make_shared<Sphere>(Point3(-5, 0, 2), 1, board_black_blue));
    //scene.add_object(std::make_shared<Sphere>(Point3(5, 0, 0), 1, unique_green));
    //scene.add_object(std::make_shared<Sphere>(Point3(-2, 0.5, -5), 1, unique_red));

    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0.5, 0), 1, red));
    //scene.add_object(std::make_shared<Sphere>(Point3(3, 0.5, 0), 1, blue));
}

void init_blob(Scene& scene) {
    /* Create blob objects */
    std::vector<shared_object> blob_objects;
    //blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 0.5, 0), 1, red));
    //blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 2, 0), 0.5, blue));
    blob_objects.push_back(std::make_shared<Sphere>(Point3(-3, 0.5, 0), 1, red));
    blob_objects.push_back(std::make_shared<Sphere>(Point3(0, 0.5, 0), 1, green));
    blob_objects.push_back(std::make_shared<Sphere>(Point3(3, 0.5, 0), 1, blue));

    Blob blob(Point3(0, 0, 0), 11, 0.25, 75, blob_objects, true);
    blob.compute();

    /* Add triangles to scene */
    for (auto& triangle: blob.get_triangles()) {
        scene.add_object(std::make_shared<SmoothTriangle>(triangle));
    }
}
