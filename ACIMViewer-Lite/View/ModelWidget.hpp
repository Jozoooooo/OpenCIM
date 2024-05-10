# pragma once

#include <QWidget>
#include <osgViewer/Viewer>
#include <osg/ref_ptr>
#include <osgEarth/MapNode>
#include <osgQOpenGL/osgQOpenGLWidget>

class osgQOpenGLWidget;

class ModelWidget : public QWidget {
Q_OBJECT

public slots:

    void initEarth();

public:
    osgQOpenGLWidget *osgQOpenGlWidget;
    osgViewer::Viewer *viewer;
    osg::ref_ptr<osg::Camera> camera;
    osg::ref_ptr<osg::Group> root;

    ModelWidget();
};