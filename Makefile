CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 \
         -g3 -O0 -fno-inline -fsanitize=address \
         -I./src/utils \
         -I./src/light \
         -I./src/object \
         -I./src/scene \
         -I./src/image

SRC= src/main.cc \
     src/light/light.cc \
     src/light/ray.cc

OBJ=${SRC:.cc=.o}

all: raytracing

raytracing: ${OBJ}
	${CXX} ${CXXFLAGS} -o raytracing ${OBJ}

clean:
	${RM} ${OBJ} raytracing

.PHONY: clean raytracing
