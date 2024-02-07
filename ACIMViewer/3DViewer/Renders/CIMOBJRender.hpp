#pragma once

#include <string>

#include "ICIMSynthetic.hpp"

using namespace NNU::OpenCIM;

class CIMOBJRender {
private:
    std::vector<std::string> _objs;
    std::vector<std::string> _textures;
public:
    explicit CIMOBJRender(const std::string &CIMPath);

    void render();
};