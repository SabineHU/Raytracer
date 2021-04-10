#pragma once

#include <vector>
#include <optional>
#include "vector3.hh"
#include "light.hh"
#include "camera.hh"
#include "scene.hh"
#include "json.hpp"

#include "object.hh"

class SceneParser {
public:
    SceneParser(const std::string& path);
    Scene parse();
private:
    const std::string& _path;
};
