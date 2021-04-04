#pragma once

#include <map>

#include "polygon.hh"

std::map<size_t, Material> parse_materials(const char* filename);
Polygon parse_obj_to_polygon(const char* filename, std::map<size_t, Material> materials);
