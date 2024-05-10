#include <QApplication>
#include <QFileInfo>
#include <QDir>

#include "View/MainWindow.hpp"
#include "ViewModel/MainWindowViewModel.hpp"

#include <QFile>
#include <osg\State>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <QTranslator>

int main(int argc, char *argv[]) {
    HWND hWnd = GetConsoleWindow();
    if (hWnd != nullptr) {
        ShowWindow(hWnd, SW_HIDE);
    }
    freopen("log.txt", "w", stderr);
    freopen("log.txt", "w", stdout);

    osg::setNotifyLevel(osg::NotifySeverity::ALWAYS);

    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);

    if (argc < 3)
        return 0;

    auto filePath = QString::fromStdString(argv[1]);
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    QFileInfo CIMPath(filePath);

    MainWindowViewModel::getInstance()->iCIMDataSet = CreateCIMDataSet();
    MainWindowViewModel::getInstance()->iCIMDataSet->fromJson(filePath.toStdString().c_str());

    for (auto i = 0; i < MainWindowViewModel::getInstance()->iCIMDataSet->getSyntheticCount(); i++) {
        MainWindowViewModel::getInstance()->CIMList.append(
                QString::fromStdString(MainWindowViewModel::getInstance()->iCIMDataSet->getSyntheticName(i)));
        MainWindowViewModel::getInstance()->filePathList.append(CIMPath.absolutePath() +
                                                                QString::fromStdString(
                                                                        MainWindowViewModel::getInstance()->iCIMDataSet->getSyntheticPath(
                                                                                i)).mid(1));
    }

    MainWindowViewModel::getInstance()->standardFilePath = CIMPath.absolutePath() + QString::fromStdString(
            MainWindowViewModel::getInstance()->iCIMDataSet->getSchemaPath()).mid(1);

    MainWindow mainWindow;
    mainWindow.setMinimumSize(1600, 800);
    mainWindow.setWindowIcon(QIcon("./image/Earth.png"));
    mainWindow.setWindowTitle(
            QString::fromStdString(MainWindowViewModel::getInstance()->iCIMDataSet->getName()) + "-" +
            QString::fromStdString(MainWindowViewModel::getInstance()->iCIMDataSet->getVersion()));
    mainWindow.showMaximized();

    char *endPtr = nullptr;
    auto level=std::strtol(argv[2],&endPtr,10);
    if (endPtr == argv[2]) {
        std::cerr << "Invalid number." << std::endl;
        return 1;
    }
    if(level>0&&level<=7){
        MainWindow::initEntityFile(MainWindowViewModel::getInstance()->filePathList[level-1]);
    }

    return QApplication::exec();
}