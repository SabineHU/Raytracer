#pragma once

#include <map>
#include <string>

#include "polygon.hh"

std::map<size_t, Material> parse_materials(const std::string& filename);
Polygon parse_obj_to_polygon(const std::string& filename, std::map<size_t, Material> materials);
