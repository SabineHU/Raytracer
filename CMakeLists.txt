# OPTIMISATION FLAGS :
set(OPT_FLAGS, "-Ofast")
# END OPTIMIZATION FLAGS

# SOURCES :
# Put all your sources here EXCEPT YOUR MAIN.CC
set(
    SRC_RAYTRACER
    src/init/init.cc
    src/init/init_objects.cc
    src/init/scene1.cc
    src/init/scene2.cc
    src/init/scene3.cc
    src/init/scene4.cc
    src/init/scene5.cc
    src/init/scene6.cc
    src/blob/blob.cc
    src/image/image.cc
    src/light/point_light.cc
    src/object/cone.cc
    src/object/capped_cone.cc
    src/object/capsule.cc
    src/object/CSG.cc
    src/object/cube.cc
    src/object/cylinder.cc
    src/object/ellipsoid.cc
    src/object/plane.cc
    src/object/plane_holed.cc
    src/object/rectangle_xy.cc
    src/object/rectangle_xz.cc
    src/object/rectangle_yz.cc
    src/object/sphere.cc
    src/object/triangle.cc
    src/object/smooth_triangle.cc
    src/object/rotate.cc
    src/object/translate.cc
    src/object/polygon.cc
    src/raytracer/raytracer.cc
    src/raytracer/ray.cc
    src/scene/camera.cc
    src/scene/scene.cc
    src/scene/scene_parser/scene_parser.cc
    src/texture/checkerboard.cc
    src/texture/image_texture.cc
    src/texture/lambertian.cc
    src/texture/metal.cc
    src/texture/strip.cc
    src/texture/perlin_noise.cc
    src/noise/noise.cc
    src/loader/loader.cc
    src/utils/vector3.cc
)

# Directories containing headers must be specified in the include_directories()
include_directories(
    src
    src/utils
    src/light
    src/object
    src/scene
    src/scene/scene_parser
    src/init
    src/image
    src/texture
    src/blob
    src/noise
    src/loader
    src/raytracer
    src/lib
)
# END SOURCES

# SETUP
cmake_minimum_required(VERSION 3.12)
project(Raytracer)

# BUILD OPTIONS
set(CMAKE_CXX_STANDARD 17)

# Add -Wall -Wextra -pedantic if you want warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-inline -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -pthread")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(raytracer)
target_sources(raytracer PRIVATE "src/main.cc" ${SRC_RAYTRACER})
