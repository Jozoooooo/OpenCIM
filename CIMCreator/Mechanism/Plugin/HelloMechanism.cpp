/**
@版权 (c) 2023, NanJin Normal University
@文件名 HelloMechanism.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景机制插件的创建样例。
@修订历史 2023.7.28 创建
**/

#include <Common/IPlugin.hpp>
#include <ICIMContent.hpp>
#include <iostream>

#define  MECHANISM_EXPORTS

#ifdef MECHANISM_EXPORTS
#define MECHANISM_API __declspec(dllexport)
#else
#define MECHANISM_API __declspec(dllimport)
#endif

class HelloMechanism : public IPlugin {
private:
    NNU::OpenCIM::ICIMContent *_iSceneContent;
public:
    HelloMechanism() : _iSceneContent(nullptr) {};

    const char *getName() override {
        return "HelloMechanism";
    }

    const char *getComments() override {
        return "删除所有公理";
    }

    int getVersion() override {
        return 1;
    }

    void preprocessing(NNU::OpenCIM::ICIMContent *iSceneContent) override {
        _iSceneContent = iSceneContent;
    }

    void run() override {
        std::cout << "场景中具有" << _iSceneContent->getIncludeCIMStandard()->getAxiomsCount() << "个公理"
                  << std::endl;
    }
};


extern "C" [[maybe_unused]] MECHANISM_API  IPlugin *CreateMechanism() {
    return new HelloMechanism;
}
