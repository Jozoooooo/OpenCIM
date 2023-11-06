/**
@版权 (c) 2023, NanJin Normal University
@文件名 main.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景三维预览程序启动入口，依赖于VTK。
@修订历史 2023.7.28 创建
**/

#include "Renders/CIMOBJRender.hpp"

int main(int argc, const char **argv) {
    if (argc < 2) return -1;

    auto CIMRender = new CIMOBJRender(argv[1]);
    CIMRender->render();

    return 0;
}
