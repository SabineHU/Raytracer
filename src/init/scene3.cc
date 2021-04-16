#include "scene3.hh"

#include "point_light.hh"

#include "sphere.hh"
#include "CSG.hh"
#include "plane.hh"
#include "smooth_triangle.hh"

#include "strip.hh"
#include "noise.hh"
#include "image_texture.hh"
#include "metal.hh"
#include "lambertian.hh"
#include "random.hh"
#include "checkerboard.hh"

#include "color.hh"

static Camera init_camera_1() {
    Vect look_from(0, 3.5, -8);
    Vect look_at(0, 0, 0);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static Camera init_camera_2() {
    Vect look_from(8, 13, 10);
    Vect look_at(0, 0, 5);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static Camera init_camera_3() {
    Vect look_from(0, 13, 0);
    Vect look_at(0, 0, 5);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static Camera init_camera_4() {
    Vect look_from(8, 13, 18);
    Vect look_at(0, 0, 10);
    Vect vup(0, 1, 0);
    return Camera(look_from, look_at, vup);
}

static void init_lights_1(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -15), white, 2.5));
}

static void init_lights_2(Scene& scene) {
    scene.add_light(std::make_shared<PointLight>(Point3(-7, 10, -15), blue, 2.5));
    scene.add_light(std::make_shared<PointLight>(Point3(7, 10, -15), red, 2.5));
}

static void add_plane_stars(Scene& scene) {
    auto image = std::make_shared<ImageTexture>("textures/stars.ppm");
    image->reverse_image();
    auto lambertian_ground = std::make_shared<Lambertian>(Color(0.41, 0.25, 0.20), 0.5);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_width(8);
    plane->set_height(6);
    plane->set_texture(lambertian_ground);
    plane->set_displacement_image(image);
    plane->add_bump_mapping(Noise(TURBULENCE, 15));
    scene.add_object(plane);
}

static void add_plane_bird(Scene& scene) {
    auto image = std::make_shared<ImageTexture>("textures/bird.ppm");
    image->reverse_image();
    auto lambertian_ground = std::make_shared<Lambertian>(Color(0.41, 0.25, 0.20), 0.5);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_width(8);
    plane->set_height(6);
    plane->set_texture(lambertian_ground);
    plane->set_displacement_image(image);
    plane->add_bump_mapping(Noise(TURBULENCE, 15));
    scene.add_object(plane);
}

static void add_plane_sheep(Scene& scene) {
    auto image = std::make_shared<ImageTexture>("textures/disp_sheep.ppm");
    image->reverse_image();
    auto lambertian_ground = std::make_shared<Lambertian>(Color(0.41, 0.25, 0.20), 0.5);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_width(8);
    plane->set_height(6);
    plane->set_texture(lambertian_ground);
    plane->set_displacement_image(image);
    plane->add_bump_mapping(Noise(TURBULENCE, 15));
    scene.add_object(plane);
}

static void add_plane_black_white(Scene& scene) {
    auto board_black_white = std::make_shared<CheckerBoard>(black, white);
    auto plane = std::make_shared<Plane>(Point3(0, 1, 0), -1);
    plane->set_texture(board_black_white);
    scene.add_object(plane);
}

static void add_CSG_union(Scene& scene) {
    auto lambertian1 = std::make_shared<Lambertian>(r_random::random_color(), 1);
    auto lambertian2 = std::make_shared<Lambertian>(r_random::random_color(), 1);
    lambertian1->ks = .3;
    lambertian2->ks = .3;
    auto sphere1 = std::make_shared<Sphere>(Point3(-4.5, 0, -3), 1);
    auto sphere2 = std::make_shared<Sphere>(Point3(-3.5, 0, -2), 1);
    sphere1->set_texture(lambertian1);
    sphere2->set_texture(lambertian2);
    sphere1->set_specular(20);
    sphere2->set_specular(20);

    scene.add_object(std::make_shared<CSG>(UNION, sphere1, sphere2));
}

static void add_CSG_difference(Scene& scene) {
    auto metal_random1 = std::make_shared<Metal>(r_random::random_color());
    auto metal_random2 = std::make_shared<Metal>(r_random::random_color());
    metal_random1->kd = .8;
    metal_random2->kd = .1;
    auto sphere1 = std::make_shared<Sphere>(Point3(-.5, 0, -3), 1);
    auto sphere2 = std::make_shared<Sphere>(Point3(.5, 0, -3), 1);
    sphere1->set_texture(metal_random1);
    sphere2->set_texture(metal_random2);
    sphere1->set_specular(10);
    sphere2->set_specular(10);

    scene.add_object(std::make_shared<CSG>(DIFFERENCE, sphere1, sphere2));
}

static void add_CSG_intersection(Scene& scene) {
    auto lambertian1 = std::make_shared<Lambertian>(r_random::random_color());
    auto lambertian2 = std::make_shared<Lambertian>(r_random::random_color());
    lambertian1->set_transparent_type();
    lambertian1->kd = 0.1;
    lambertian1->kt = 0.5;
    lambertian2->set_transparent_type();
    lambertian2->kd = 0.1;
    lambertian2->kt = 0.5;

    auto sphere1 = std::make_shared<Sphere>(Point3(4.5, 0, -3), 1);
    auto sphere2 = std::make_shared<Sphere>(Point3(3.5, 0, -2), 1);
    sphere1->set_texture(lambertian1);
    sphere1->set_ior(2.417);
    sphere2->set_texture(lambertian2);
    sphere2->set_ior(2.417);

    scene.add_object(std::make_shared<CSG>(INTERSECTION, sphere1, sphere2));
}

static void add_CSG_intersection2(Scene& scene) {
    auto sphere1 = std::make_shared<Sphere>(Point3(3, 0, 1), 1);
    auto sphere2 = std::make_shared<Sphere>(Point3(3.5, .3, 1), 1);

    sphere1->set_texture(blue3);
    sphere2->set_texture(light_orange);

    scene.add_object(std::make_shared<CSG>(INTERSECTION, sphere1, sphere2));
}

static void add_CSG_minus(Scene& scene) {
    auto strip = std::make_shared<Strip>(white, r_random::random_color(), true, 5);
    strip->set_planar(true);
    strip->set_horizontal(false);

    auto sphere1 = std::make_shared<Sphere>(Point3(6.5, 0, 1), 1);
    auto sphere2 = std::make_shared<Sphere>(Point3(6.5, 1, 1), 1);

    sphere1->set_texture(strip);
    sphere2->set_texture(light_orange);
    sphere1->set_specular(10);

    scene.add_object(std::make_shared<CSG>(MINUS, sphere1, sphere2));
}

static void add_CSG_minus2(Scene& scene) {
    auto strip = std::make_shared<Strip>(white, r_random::random_color(), true, 5);
    strip->set_planar(true);

    auto sphere1 = std::make_shared<Sphere>(Point3(0, 0, 1), 1);
    auto sphere2 = std::make_shared<Sphere>(Point3(.5, 1, 1), 1);

    sphere1->set_texture(strip);
    sphere2->set_texture(light_orange);
    sphere1->set_specular(10);

    scene.add_object(std::make_shared<CSG>(MINUS, sphere1, sphere2));
}

static shared_object create_sphere(const Point3& p, double r, double spec, shared_texture t) {
    auto sphere = std::make_shared<Sphere>(p, r);
    sphere->set_texture(t);
    sphere->set_specular(spec);
    return sphere;
}

static void add_spheres(Scene& scene) {
    auto metal1  = std::make_shared<Metal>(Color( .5,     0,   0), .5, .07);
    auto metal2  = std::make_shared<Metal>(Color( .5, .1235,   0), .5, .14);
    auto metal3  = std::make_shared<Metal>(Color( .5,   .25,   0), .5, .21);
    auto metal4  = std::make_shared<Metal>(Color( .5,    .5,   0), .5, .28);
    auto metal5  = std::make_shared<Metal>(Color(.25,    .5,   0), .5, .34);
    auto metal6  = std::make_shared<Metal>(Color(  0,    .5,   0), .5, .40);
    auto metal7  = std::make_shared<Metal>(Color(  0,    .5, .25), .5, .45);
    auto metal8  = std::make_shared<Metal>(Color(  0,    .5,  .5), .5, .50);
    auto metal9  = std::make_shared<Metal>(Color(  0,   .25,  .5), .5, .55);
    auto metal10 = std::make_shared<Metal>(Color(  0, .1235,  .5), .5, .60);
    auto metal11 = std::make_shared<Metal>(Color(  0,     0,  .5), .5, .66);
    auto metal12 = std::make_shared<Metal>(Color(.25,     0,  .5), .5, .72);
    auto metal13 = std::make_shared<Metal>(Color( .5,     0,  .5), .5, .79);
    auto metal14 = std::make_shared<Metal>(Color( .5,     0, .25), .5, .86);
    auto metal15 = std::make_shared<Metal>(Color( .5,     0,   0), .5, .93);

    scene.add_object(create_sphere(Point3(-14, 0, 8), 1, 10, metal1));
    scene.add_object(create_sphere(Point3(-12, 0, 8), 1, 10, metal2));
    scene.add_object(create_sphere(Point3(-10, 0, 8), 1, 10, metal3));
    scene.add_object(create_sphere(Point3( -8, 0, 8), 1, 10, metal4));
    scene.add_object(create_sphere(Point3( -6, 0, 8), 1, 10, metal5));
    scene.add_object(create_sphere(Point3( -4, 0, 8), 1, 10, metal6));
    scene.add_object(create_sphere(Point3( -2, 0, 8), 1, 10, metal7));
    scene.add_object(create_sphere(Point3(  0, 0, 8), 1, 10, metal8));
    scene.add_object(create_sphere(Point3(  2, 0, 8), 1, 10, metal9));
    scene.add_object(create_sphere(Point3(  4, 0, 8), 1, 10, metal10));
    scene.add_object(create_sphere(Point3(  6, 0, 8), 1, 10, metal11));
    scene.add_object(create_sphere(Point3(  8, 0, 8), 1, 10, metal12));
    scene.add_object(create_sphere(Point3( 10, 0, 8), 1, 10, metal13));
    scene.add_object(create_sphere(Point3( 12, 0, 8), 1, 10, metal14));
    scene.add_object(create_sphere(Point3( 14, 0, 8), 1, 10, metal15));
}

static void add_spheres2(Scene& scene) {
    auto metal1  = std::make_shared<Metal>(Color(.2549,.6235,.1568));
    auto metal2  = std::make_shared<Metal>(Color(.3176,.6117,.1451));
    auto metal3  = std::make_shared<Metal>(Color(.3725,.6078,.1333));
    auto metal4  = std::make_shared<Metal>(Color(.4353,.5921,.1215));
    auto metal5  = std::make_shared<Metal>(Color(.4901,.5843,.1059));
    auto metal6  = std::make_shared<Metal>(Color(.5490,.5764,.0941));
    auto metal7  = std::make_shared<Metal>(Color(.6117,.5686,.0823));
    auto metal8  = std::make_shared<Metal>(Color(.6705,.5608,.0667));
    auto metal9  = std::make_shared<Metal>(Color(.7255,.5490,.0549));
    auto metal10 = std::make_shared<Metal>(Color(.7882,.5372,.0431));
    auto metal11 = std::make_shared<Metal>(Color(.8431,.5333,.0274));
    auto metal12 = std::make_shared<Metal>(Color(.9059,.5216,.0157));
    auto metal13 = std::make_shared<Metal>(Color(.9608,.5137,.0039));

    scene.add_object(create_sphere(Point3(-24, 0, 22), 2,  8, metal1));
    scene.add_object(create_sphere(Point3(-20, 0, 22), 2,  8, metal2));
    scene.add_object(create_sphere(Point3(-16, 0, 22), 2,  8, metal3));
    scene.add_object(create_sphere(Point3(-12, 0, 22), 2,  8, metal4));
    scene.add_object(create_sphere(Point3( -8, 0, 22), 2, 16, metal5));
    scene.add_object(create_sphere(Point3( -4, 0, 22), 2, 24, metal6));
    scene.add_object(create_sphere(Point3(  0, 0, 22), 2, 32, metal7));
    scene.add_object(create_sphere(Point3(  4, 0, 22), 2, 40, metal8));
    scene.add_object(create_sphere(Point3(  8, 0, 22), 2, 48, metal9));
    scene.add_object(create_sphere(Point3( 12, 0, 22), 2, 56, metal10));
    scene.add_object(create_sphere(Point3( 16, 0, 22), 2, 56, metal11));
    scene.add_object(create_sphere(Point3( 20, 0, 22), 2, 56, metal12));
    scene.add_object(create_sphere(Point3( 24, 0, 22), 2, 56, metal13));
}

static void add_plane(Scene& scene, int nb) {
    if (nb == 1)             add_plane_black_white(scene);
    else if (nb == 2)        add_plane_sheep(scene);
    else if (nb == 3)        add_plane_stars(scene);
    else                     add_plane_bird(scene);
}
static void add_lights(Scene& scene, int nb) {
    if (nb == 1)        init_lights_1(scene);
    else                init_lights_2(scene);
}
static Camera init_camera(int nb) {
    if (nb == 1) return init_camera_1();
    else if (nb == 2) return init_camera_2();
    else if (nb == 3) return init_camera_3();
    return init_camera_4();
}

Scene init_scene3() {
    Camera cam = init_camera(2);

    Scene scene(cam, Color(.5, .5, .5));
    add_lights(scene, 1);
    add_plane(scene, 2);

    add_CSG_union(scene);
    add_CSG_difference(scene);
    add_CSG_intersection(scene);
    add_CSG_intersection2(scene);
    add_CSG_minus(scene);
    add_CSG_minus2(scene);

    add_spheres(scene);
    add_spheres2(scene);

    return scene;
}
