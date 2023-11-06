/**
@版权 (c) 2023, NanJin Normal University
@文件名 CPSTabControlViewModel.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 读取场景中所有的公理依据，做为创建树的标准。
@修订历史 2023.7.28 创建
**/

# pragma once

#include <iostream>
#include <codecvt>
#include "../Model/CombItem.h"
#include "MainWidgetViewModel.h"

class CPSTabControlViewModel {
public:
    explicit CPSTabControlViewModel() : combItem(new CombItem) {
        for (auto i = 0; i < Core::Axiom::getBasisCount(); i++) {
            combItem->items.emplace_back(Core::Axiom::getBasis(i));
        }
    }

    CombItem *combItem;
};