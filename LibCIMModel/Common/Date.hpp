/**
@版权 (c) 2023, NanJin Normal University
@文件名 Date.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 日期类，用于获取计算机当前日期，日期格式为 "%Y-%m-%d %H:%M:%S"
@修订历史 2023.7.28 创建
**/

#pragma once

#include <string>

namespace NNU::OpenCIM::Common {
    class Date {
    public:
        static std::string currentDate();
    };
}