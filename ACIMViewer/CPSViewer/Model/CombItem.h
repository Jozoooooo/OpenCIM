#pragma once

#include <vector>

struct CombItem {
    CombItem() {
        currentItemIndex = 0;
    }

    int currentItemIndex;
    std::vector<std::string> items;
};