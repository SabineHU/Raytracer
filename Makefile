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
         -I./src/blob

SRC= src/main.cc \
     src/init.cc \
     src/light/light.cc \
     src/light/ray.cc \
     src/object/cone.cc \
     src/object/plane.cc \
     src/object/sphere.cc \
     src/object/triangle.cc \
     src/object/smooth_triangle.cc \
     src/scene/camera.cc \
     src/scene/scene.cc \
     src/image/image.cc \
     src/utils/vector3.cc \
     src/texture/metal.cc \
     src/texture/unique.cc \
     src/texture/checkerboard.cc \
     src/blob/blob.cc

OBJ=${SRC:.cc=.o}

all: raytracing

raytracing: ${OBJ}
	${CXX} ${CXXFLAGS} -o raytracing ${OBJ}

clean:
	${RM} ${OBJ} raytracing

check:
	make clean && make -j
	time ./raytracing > test.ppm
	diff original.ppm test.ppm

.PHONY: clean raytracing
