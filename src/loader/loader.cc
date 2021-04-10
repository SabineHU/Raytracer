#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "loader.hh"
#include "hash.hh"
#include "file.hh"

std::map<size_t, Material> parse_materials(const std::string& filename) {
    std::map<size_t, Material> res;
    std::ifstream f = file::open_file(filename);

    std::string code;
    Material m;
    ssize_t hash_material_name = -1;
    double x, y, z;

    for (std::string line; std::getline(f, line);) {
        if (line[0] == '#') continue;
        std::istringstream iss(line);
        iss >> code;

        if (code == "newmtl") {
            if (hash_material_name != -1)
                res[hash_material_name] = m;
            m = Material();
            iss >> code;
            hash_material_name = hash::get_value_hash(code);
        } else if (code == "Ns") {
            iss >> m.ns;
        } else if (code == "Ka") {
            iss >> x >> y >> z;
            m.ka = Color(x, y, z);
        } else if (code == "Kd") {
            iss >> x >> y >> z;
            m.kd = Color(x, y, z);
        } else if (code == "Ks") {
            iss >> x >> y >> z;
            m.ks = Color(x, y, z);
        } else if (code == "Ke") {
            iss >> x >> y >> z;
            m.ke = Color(x, y, z);
        }
    }

    if (hash_material_name != -1)
        res[hash_material_name] = m;

    f.close();
    return res;
}

Polygon parse_obj_to_polygon(const std::string& filename, std::map<size_t, Material> materials) {
    std::ifstream f = file::open_file(filename);

    std::vector<Vect> vertices;
    std::vector<Vect> normals;
    std::vector<Vect2> textures;
    std::vector<Face> faces;

    std::string code;
    double x, y, z;

    ssize_t index = -1;

    for (std::string line; std::getline(f, line);)
    {
        if (line[0] == '#')
            continue;

        std::istringstream iss(line);

        iss >> code;

        if (code == "v")
        {
            iss >> x >> y >> z;
            vertices.push_back(Vect(x, y, z));
        }
        else if (code == "vt")
        {
            iss >> x >> y;
            textures.push_back(Vect2(x, y));
        }
        else if (code == "vn")
        {
            iss >> x >> y >> z;
            normals.push_back(Vect(x, y, z));
        }
        else if (code == "usemtl")
        {
            iss >> code;
            index = hash::get_value_hash(code);
        }
        else if (code == "f")
        {
            char w;
            double x1, y1, z1;
            double x2, y2, z2;

            iss >> x   >> w >> y   >> w >> z;
            iss >> x1  >> w >> y1  >> w >> z1;
            iss >> x2  >> w >> y2  >> w >> z2;

            auto vertice = TriangleMesh(x - 1, x1 - 1, x2 - 1);
            auto texture = TriangleMesh(y - 1, y1 - 1, y2 - 1);
            auto normal  = TriangleMesh(z - 1, z1 - 1, z2 - 1);

            faces.push_back(Face(vertice, normal, texture, materials[index]));
        }
    }

    f.close();

    return Polygon(vertices, normals, textures, faces);
}
