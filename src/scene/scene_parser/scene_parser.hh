#pragma once

#include "json.hpp"
#include "scene.hh"

class SceneParser {
public:
    SceneParser(const std::string& path);

    /* Methods */
    Scene parse();

private:
    /* Attributes */
    const std::string _path;
};
