#pragma once

#include <ICIMSchema.hpp>
#include <ICIMSynthetic.hpp>
#include <ICIMDataSet.hpp>

#include "../View/ModelWidget.hpp"
#include "../Tool/OSGBTool.hpp"

using namespace NNU::OpenCIM;

class MainWindowViewModel {
private:
    static MainWindowViewModel *mainWindowViewModel;
    OSGBTool *osgbTool;

    MainWindowViewModel();

public:
    QString standardFilePath;
    QString contentFilePath;

    QString contentFileDir;

    ModelWidget *modelWidget;

    QList<QMap<QString, QMap<QString, osg::ref_ptr<osg::Node>>>> ifc2objList;

    ICIMSynthetic *iCIMContent;
    ICIMSchema *iCIMStandard;
    ICIMDataSet *iCIMDataSet;

    static MainWindowViewModel *getInstance();

    QList<QString> CIMList;
    QString currentCIM;
    QList<QString> filePathList;

    void addEntityToEarth();
};
