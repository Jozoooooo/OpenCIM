# pragma once

#include <vector>
#include <string>

struct TreeNode {
    std::string data;
    std::vector<TreeNode *> children;
};