/**
@版权 (c) 2023, NanJin Normal University
@文件名 IPlugin.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景机制采用外部插件来实现机制功能，本文件提供对场景插件的标准定义。
@修订历史 2023.7.28 创建
**/

# pragma once

namespace NNU::OpenCIM {
    struct ICIMSynthetic;
}

struct IPlugin {
public:
    virtual const char *getName() = 0;

    virtual const char *getComments() = 0;

    virtual int getVersion() = 0;

    [[maybe_unused]] virtual void preprocessing(NNU::OpenCIM::ICIMSynthetic *iCIMContent) = 0;

    [[maybe_unused]] virtual void run() = 0;
};

