/**
@版权 (c) 2023, NanJin Normal University
@文件名 Define.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 通用定义类，用于对库中多处使用的变量类型定义别名，便于理解，及对一些固定参数进行定义。
@修订历史 2023.7.28 创建
**/

#pragma once

#define JSONSTR std::string // JSON字符串
#define TIMESTAMP std::string // 时间戳
#define JSONINDENT 4 // JSON输出缩进格式


/****材质属性名预定义数组****
    序号 参数名 参数含义
    0 KA 环境光颜色(rgb 0~1)
    1 KD 漫反射颜色(rgb 0~1)
    2 KS 镜面反射颜色(rgb 0~1)
    3 KE 自发光颜色(rgb 0~1)
    4 NS 高光度(int 0~1000)
    5 NI 折射率(double 0.0001~10)
    6 D 透明度(double 0~1)
    7 ILLUM 光照模型(int 0~10)
    8 MAP_BUMP 表面凹凸(file)
    9 MAP_KD 漫反射贴图(file)
    10 MAP_KA 环境光贴图(file)
    11 MAP_KS 镜面反射贴图(file)
    12 MAP_D 透明度贴图(file)
*********************************/
[[maybe_unused]] constexpr const char *MaterialType[] = {"KA", "KD", "KS", "KE", "NS", "NI", "D", "ILLUM",
                                                         "MAP_BUMP", "MAP_KD", "MAP_KA", "MAP_KS", "MAP_D"};