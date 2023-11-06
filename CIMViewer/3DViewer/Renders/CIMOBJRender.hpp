#pragma once

#include <string>

#include "ICIMContent.hpp"

using namespace NNU::OpenCIM;

class CIMOBJRender {
private:
    std::vector<std::string> _objs;
    std::vector<std::string> _textures;
public:
    explicit CIMOBJRender(const std::string &CIMPath);

    void render();
};