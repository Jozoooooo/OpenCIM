/**
@版权 (c) 2023, NanJin Normal University
@文件名 TestPlugin.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景机制的导入、读取和运行样例。
@修订历史 2023.7.28 创建
**/

#include <iostream>
#include "ICIMSynthetic.hpp"

using namespace NNU::OpenCIM;

void TestPlugin() {
    system("chcp 65001");

    // 创建场景
    auto cimSynthetic = CreateCIMSynthetic();

    // 导入场景
    cimSynthetic->fromJson("Example/NNU-ACIM/NNU-ACIM.json");

    // 创建机制
    auto mechanism = cimSynthetic->createMechanism();
    mechanism->setMechanismPath("SceneCreator.dll"); // 设置机制路径

    // 读取机制信息
    mechanism->load();
    mechanism->getMechanismMeta();

    std::cout << mechanism->getMechanismName() << "\n";

    // 运行机制
    auto plugin = mechanism->getMechanismPlugin();
    plugin->preprocessing(cimSynthetic); // 传入当前场景

    plugin->run(); // 机制运行
}