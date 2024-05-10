#include "ModelWidget.hpp"

#include <osgGA/TrackballManipulator>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgEarth/Common>
#include <QVBoxLayout>
#include <QDebug>

ModelWidget::ModelWidget() {
    viewer = nullptr;
    osgEarth::initialize();
    osgQOpenGlWidget = new osgQOpenGLWidget();
    osgQOpenGlWidget->move(this->pos().x(),this->pos().y());
    osgQOpenGlWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    root = new osg::Group;
    auto vLayout=new QVBoxLayout;
    vLayout->addWidget(osgQOpenGlWidget);
    this->setLayout(vLayout);

    connect(osgQOpenGlWidget, SIGNAL(initialized()), this, SLOT(initEarth()));
}

void ModelWidget::initEarth() {
    viewer = osgQOpenGlWidget->getOsgViewer();
    viewer->setCameraManipulator(new osgGA::TrackballManipulator());
    const auto width = osgQOpenGlWidget->width(), height = osgQOpenGlWidget->height();

    camera = viewer->getCamera();
    camera->setClearColor(osg::Vec4f(0.062f, 0.117f, 0.215f, 1));
    camera->setViewport(new osg::Viewport(0, 0, width, height));
    camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width) / static_cast<double>(height), 1.0f,
                                             10000.0f);
    viewer->setCamera(camera);
    viewer->setSceneData(root);

    osgQOpenGlWidget->showMaximized();
}


