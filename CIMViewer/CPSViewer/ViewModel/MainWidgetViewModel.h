/**
@版权 (c) 2023, NanJin Normal University
@文件名 MainWidgetViewModel.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景内容和场景标准储存模型。
@修订历史 2023.7.28 创建
**/

# pragma once

#include <ICIMStandard.hpp>
#include <ICIMContent.hpp>

using namespace NNU::OpenCIM;

// 储存场景标准和场景内容
class MainWidgetViewModel {
public:
    MainWidgetViewModel() : iCIMStandard(nullptr), iCIMContent(nullptr) {};

    ICIMContent *iCIMContent;
    ICIMStandard *iCIMStandard;
};