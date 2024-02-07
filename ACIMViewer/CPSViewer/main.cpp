/**
@版权 (c) 2023, NanJin Normal University
@文件名 main.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 分类颗粒树预览程序启动入口，依赖于ImGUI，采用类MVVM框架实现。
@修订历史 2023.7.28 创建
**/

#include <filesystem>

#include "ViewModel/MainWidgetViewModel.h"
#include "ViewModel/CPSTabControlViewModel.h"
#include "ViewModel/TreeViewModel.h"

MainWidgetViewModel *mainWidgetViewModel;
CPSTabControlViewModel *cpsTabControlViewModel;
TreeViewModel *csTreeViewModel;
TreeViewModel *psTreeViewModel;

void MainWidget(const std::string &fileName);

void InitialMainWidgetViewModel(int type, const char *CIMPath) {
    mainWidgetViewModel = new MainWidgetViewModel;

    if (type == 1) {
        mainWidgetViewModel->iCIMSchema = CreateCIMSchema();
        mainWidgetViewModel->iCIMSchema->fromJson(CIMPath);
    }

    if (type == 2) {
        mainWidgetViewModel->iCIMSynthetic = CreateCIMSynthetic();
        mainWidgetViewModel->iCIMSynthetic->fromJson(CIMPath);
    }
}

void InitialCPSTabControlViewModel(int type) {
    if (type == 1) {
        cpsTabControlViewModel = new CPSTabControlViewModel();
    }

    if (type == 2) {
        cpsTabControlViewModel = new CPSTabControlViewModel();
    }
}

void InitialCsTreeViewModel(int type) {
    if (type == 1) {
        csTreeViewModel = new TreeViewModel(mainWidgetViewModel->iCIMSchema);
    }

    if (type == 2) {
        csTreeViewModel = new TreeViewModel(
                mainWidgetViewModel->iCIMSynthetic->getIncludeCIMStandard());
    }
}

void InitialPSTreeViewModel(int type) {
    if (type == 1) {
        psTreeViewModel = new TreeViewModel(mainWidgetViewModel->iCIMSchema);
    }

    if (type == 2) {
        psTreeViewModel = new TreeViewModel(
                mainWidgetViewModel->iCIMSynthetic->getIncludeCIMStandard());
    }
}


void InitialViewModel(int type, const char *CIMPath) {
    InitialMainWidgetViewModel(type, CIMPath);
    InitialCPSTabControlViewModel(type);
    InitialCsTreeViewModel(type);
    InitialPSTreeViewModel(type);
}

int main(int argc, const char **argv) {
    if (argc < 3) return -1;

    InitialViewModel(strtol(argv[1], nullptr, 10), argv[2]);

    std::filesystem::path pathObj(argv[2]);
    std::filesystem::path fileName = pathObj.filename();

    MainWidget(fileName.string());

    return 0;
}
