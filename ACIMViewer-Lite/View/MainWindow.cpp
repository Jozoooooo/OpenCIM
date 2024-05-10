#include "MainWindow.hpp"

#include <QMessageBox>
#include <QCoreApplication>
#include <QDir>
#include <QApplication>
#include <QKeyEvent>

#include "../ViewModel/MainWindowViewModel.hpp"
#include "osgGA/TrackballManipulator"

MainWindow::MainWindow() {
    MainWindowViewModel::getInstance()->iCIMStandard = CreateCIMSchema();
    MainWindowViewModel::getInstance()->iCIMStandard->fromJson(
            MainWindowViewModel::getInstance()->standardFilePath.toStdString().c_str());
    MainWindowViewModel::getInstance()->iCIMContent = CreateCIMSynthetic();
    MainWindowViewModel::getInstance()->iCIMContent->fromJson(
            MainWindowViewModel::getInstance()->filePathList[0].toStdString().c_str());

    initUi();
}

void MainWindow::initUi() {
    this->setWindowTitle(tr("ACIMViewer"));
    this->setCentralWidget((QWidget *) MainWindowViewModel::getInstance()->modelWidget->osgQOpenGlWidget);

    auto font = this->font();
    font.setPointSize(10);
    this->setFont(font);
}

void MainWindow::initEntityFile(const QString &filePath, bool init) {
    if (filePath.isEmpty()) {
        return;
    }

    MainWindowViewModel::getInstance()->iCIMContent = CreateCIMSynthetic();
    MainWindowViewModel::getInstance()->iCIMContent->fromJson(filePath.toLocal8Bit());

    const QFileInfo fileInfo(filePath);
    MainWindowViewModel::getInstance()->contentFileDir = fileInfo.path();
    MainWindowViewModel::getInstance()->addEntityToEarth();

    MainWindowViewModel::getInstance()->modelWidget->viewer->getCameraManipulator()->computeHomePosition();
    MainWindowViewModel::getInstance()->modelWidget->viewer->getCameraManipulator()->home(0.0);

    MainWindowViewModel::getInstance()->standardFilePath = "";
    MainWindowViewModel::getInstance()->contentFilePath = filePath;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_F) {
        MainWindowViewModel::getInstance()->modelWidget->viewer->getCameraManipulator()->computeHomePosition();
        MainWindowViewModel::getInstance()->modelWidget->viewer->getCameraManipulator()->home(0.0);
    } else if (event->key() == Qt::Key_T) {
        auto trackball = new osgGA::TrackballManipulator();
        trackball->setAllowThrow(false);
        MainWindowViewModel::getInstance()->modelWidget->viewer->setCameraManipulator(trackball);
    } else if (event ->key() == Qt::Key_A ) {
        MainWindowViewModel::getInstance()->modelWidget->viewer->setCameraManipulator(nullptr);
        MainWindowViewModel::getInstance()->modelWidget->viewer->setCameraManipulator(
                new osgGA::TrackballManipulator());
    }
    QWidget::keyPressEvent(event);
}



