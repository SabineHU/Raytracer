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

image::Image init_image(double angle, double zmin) {
    double alpha = math::degree_to_radian(angle);
    double beta = alpha * 16.0 / 9.0; // Get ratio 16:9

    return image::Image(alpha, beta, zmin);
}

Camera init_camera() {
    /* Camera */
    //Vect look_from(6, 4, -8);
    //Vect look_from(0, 1.5, -8);
    Vect look_from(0, 1.5, -9); // Vu horizon
    //Vect look_from(0, 2, -5);
    //Vect look_from(0, 10, -0.0001); // Vu du dessus
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

void init_lights(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -10), white, 2.5));
}

void init_objects(Scene& scene) {
    /* Black and white plane */
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(board_black_white);
    scene.add_object(plane);

    /* Torus */
    //auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    //auto torus = std::make_shared<Torus>(Point3(2.5, .5, 0));
    //torus->set_texture(lambertian_random);
    //scene.add_object(torus);

    //auto lambertian_green = std::make_shared<Lambertian>(light_green, 0.6);
    //auto sphere1 = std::make_shared<Sphere>(Point3(-4, 0, 2), 1);
    //sphere1->set_texture(lambertian_green);
    //scene.add_object(sphere1);

    //auto metal_orange = std::make_shared<Metal>(orange, 0.2);
    //auto capsule = std::make_shared<Capsule>(Point3(-2, 0, -3), Point3(2, 1, 0), 1);
    //capsule->set_texture(metal_orange);
    //scene.add_object(capsule);

    //auto lambertian_orange = std::make_shared<Lambertian>(orange, 0.5);
    //auto cube = std::make_shared<Cube>(Point3(0, -1, 0), 2);
    //cube->set_texture(lambertian_orange);
    //scene.add_object(cube);

    //auto ellipsoid = std::make_shared<Ellipsoid>(Point3(-2, 0, -3), Point3(1.5, 0.5, 2));
    //ellipsoid->set_texture(lambertian_orange);
    //scene.add_object(ellipsoid);

    //auto cylinder = std::make_shared<Cylinder>(Point3(-2, -1, 0), Point3(-2, 1, 0), 1);
    //cylinder->set_texture(lambertian_orange);
    //scene.add_object(cylinder);

    //auto cone1 = std::make_shared<Cone>(Point3(-2, -1, 0), 1, 2);
    //cone1->set_texture(lambertian_orange);
    //cone1->set_specular(30);
    //scene.add_object(cone1);

    //auto lambertian_red = std::make_shared<Metal>(dark_red);
    //lambertian_red->set_transparent_type();
    //lambertian_red->kd = 0.1;
    //lambertian_red->kt = 0.25;
    //auto sphere_red = std::make_shared<Sphere>(Point3(-2, 0, 0), 1);
    //sphere_red->set_texture(lambertian_red);
    //sphere_red->set_specular(30);
    //scene.add_object(sphere_red);

    //auto image_carte_texture = std::make_shared<ImageTexture>("textures/carte.ppm");
    //auto sphere_map = std::make_shared<Sphere>(Point3(0, 0, 0), 1);
    //sphere_map->set_texture(image_carte_texture);
    //scene.add_object(sphere_map);

    //auto image_texture = std::make_shared<ImageTexture>("textures/quadrillage.ppm");
    //auto capped_cone = std::make_shared<CappedCone>(Point3(2, -1, 0), Point3(2, 1, 0), 1, 0.5);
    //capped_cone->set_texture(image_texture);
    //scene.add_object(capped_cone);

    //auto strip = std::make_shared<Strip>(orange, light_blue, true, 25);
    //auto sphere1 = std::make_shared<Sphere>(Point3(0, 1.5, 0), .5);
    //sphere1->set_texture(strip);
    //sphere1->set_specular(25);
    //scene.add_object(sphere1);

    //auto strip2 = std::make_shared<Strip>(red, white, true, 5);
    //strip2->set_planar(true);
    //auto sphere2 = std::make_shared<Sphere>(Point3(-2, 0, 0), 1);
    //sphere2->set_texture(strip2);
    //scene.add_object(sphere2);

    auto metal_random = std::make_shared<Metal>(r_random::random_color());
    auto metal_random2 = std::make_shared<Metal>(r_random::random_color());
    auto obj1 = std::make_shared<Sphere>(Point3(2, 0, 0), 1);
    obj1->set_texture(metal_random);

    auto obj2 = std::make_shared<Sphere>(Point3(2.5, 1, 0), 1);
    //auto obj2 = std::make_shared<Cone>(Point3(2, 0, 0), 0.75, 2.5);
    obj2->set_texture(metal_random2);
    auto CSG_union = std::make_shared<CSG>(UNION, obj1, obj2);
    scene.add_object(CSG_union);
    //scene.add_object(obj1);
    //scene.add_object(obj2);

    //auto lambertian_random = std::make_shared<Lambertian>(r_random::random_color());
    //scene.add_object(std::make_shared<Sphere>(Point3(2, 0, 0), 1, lambertian_random));

    //auto perlin = std::make_shared<PerlinNoise>(2, NOISE, red, yellow);
    //auto p1 = std::make_shared<Sphere>(Point3(0, 1, 1), 2);
    //p1->set_texture(perlin);
    //scene.add_object(p1);

    //auto perlin2 = std::make_shared<PerlinNoise>(2, TURBULENCE, purple, black);
    //auto p2 = std::make_shared<Sphere>(Point3(-4, 1, 0), 2);
    //p2->set_texture(perlin2);
    //scene.add_object(p2);

    //auto perlin3 = std::make_shared<PerlinNoise>(2, MARBLE, dark_blue, light_blue);
    //auto p3 = std::make_shared<Sphere>(Point3(-5, 1, -4), 2);
    //p3->set_texture(perlin3);
    //scene.add_object(p3);

    //auto perlin4 = std::make_shared<PerlinNoise>(2, WOOD);
    //auto p4 = std::make_shared<Sphere>(Point3(4, 1, 1), 2);
    //p4->set_texture(perlin4);
    //scene.add_object(p4);

    //auto perlin5 = std::make_shared<PerlinNoise>(2, WOOD, light_pink, light_red);
    //auto sphere_wood_colored = std::make_shared<Sphere>(Point3(0, 0, -3), 1);
    //sphere_wood_colored->set_texture(perlin5);
    //sphere_wood_colored->set_specular(50);
    //scene.add_object(sphere_wood_colored);

}

void init_objects2(Scene& scene) {
    /* Textures */
    auto lambertian_green = std::make_shared<Lambertian>(light_green, 0.05);
    auto metal_green = std::make_shared<Metal>(light_green, 0.05);
    auto lambertian_red = std::make_shared<Metal>(dark_red);
    auto strip2 = std::make_shared<Strip>(red, white, true, 5);
    strip2->set_planar(true);

    /* Black and white plane */
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(board_black_white);
    scene.add_object(plane);

    //scene.add_object(std::make_shared<Sphere>(Point3(0.5, 0, 0), 1, light_blue));
    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0, 0), 1, orange));
    //scene.add_object(std::make_shared<Cone>(Point3(-7, -1, 1), 1, 2.5, lambertian_green));

    //auto sphere1 = std::make_shared<Sphere>(Point3(-5, 0, 2), 1, strip2);
    //sphere1->set_specular(25);
    //scene.add_object(sphere1);

    //auto sphere2 = std::make_shared<Sphere>(Point3(5, 0, 0), 1, metal_green);
    //sphere2->set_specular(40);
    //scene.add_object(sphere2);
    //scene.add_object(std::make_shared<Sphere>(Point3(-2, 0.5, -5), 1, lambertian_red));

    //scene.add_object(std::make_shared<Sphere>(Point3(0, 0.5, 0), 1, red));
    //scene.add_object(std::make_shared<Sphere>(Point3(3, 0.5, 0), 1, blue));
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
