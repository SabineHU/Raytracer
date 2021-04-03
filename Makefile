CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 \
         -g3 -O3 -fno-inline \
         -I./src \
         -I./src/utils \
         -I./src/light \
         -I./src/object \
         -I./src/scene \
         -I./src/image \
         -I./src/texture \
         -I./src/blob \
         -I./src/raytracer

SRC= src/main.cc \
     src/init.cc \
     src/init_objects.cc \
     \
     src/blob/blob.cc \
     \
     src/image/image.cc \
     \
     src/light/point_light.cc \
     \
     src/object/cone.cc \
     src/object/capped_cone.cc \
     src/object/capsule.cc \
     src/object/CSG.cc \
     src/object/cube.cc \
     src/object/cylinder.cc \
     src/object/ellipsoid.cc \
     src/object/plane.cc \
     src/object/rectangle.cc \
     src/object/sphere.cc \
     src/object/triangle.cc \
     src/object/torus.cc \
     src/object/smooth_triangle.cc \
     src/object/rotate.cc \
     \
     src/raytracer/raytracer.cc \
     src/raytracer/ray.cc \
     \
     src/scene/camera.cc \
     src/scene/scene.cc \
     \
     src/texture/checkerboard.cc \
     src/texture/image_texture.cc \
     src/texture/lambertian.cc \
     src/texture/metal.cc \
     src/texture/strip.cc \
     src/texture/noise.cc \
     src/texture/perlin_noise.cc \
     \
     src/utils/vector3.cc

OBJ=${SRC:.cc=.o}

all: raytracing

raytracing: ${OBJ}
	${CXX} ${CXXFLAGS} -o raytracing ${OBJ}

clean:
	${RM} ${OBJ} raytracing

.PHONY: clean raytracing
