#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "loader.hh"

static std::ifstream open_obj_file(const char* filename) {
    // Open file, read only
    std::ifstream ifs(filename, std::ifstream::in);
    if (!ifs.is_open()) {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(1);
    }

    return ifs;
}

Polygon parse_obj_to_polygon(const char* filename) {
    std::ifstream f = open_obj_file(filename);

    std::vector<Vect> vertices;
    std::vector<Vect> normals;
    std::vector<Vect2> textures;
    std::vector<Face> faces;

    std::string code;
    double x, y, z;
    for (std::string line; std::getline(f, line);) {
        if (line[0] == '#') continue;
        std::istringstream iss(line);

        iss >> code;
        if (code == "v") {
            iss >> x >> y >> z;
            vertices.push_back(Vect(x, y, z));
        } else if (code == "vt") {
            iss >> x >> y;
            textures.push_back(Vect2(x, y));
        } else if (code == "vn") {
            iss >> x >> y >> z;
            normals.push_back(Vect(x, y, z));
        } else if (code == "f") {
            char w;
            double x1, y1, z1;
            double x2, y2, z2;

            iss >> x   >> w >> y   >> w >> z;
            iss >> x1  >> w >> y1  >> w >> z1;
            iss >> x2  >> w >> y2  >> w >> z2;

            auto vertice = TriangleMesh(x - 1, x1 - 1, x2 - 1);
            auto texture = TriangleMesh(y - 1, y1 - 1, y2 - 1);
            auto normal  = TriangleMesh(z - 1, z1 - 1, z2 - 1);

            faces.push_back(Face(vertice, normal, texture));
        }

    }
    return Polygon(vertices, normals, textures, faces);
}
