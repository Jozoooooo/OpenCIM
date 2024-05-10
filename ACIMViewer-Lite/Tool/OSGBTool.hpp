#pragma once

#include <QObject>
#include <osg/Node>
#include <QMap>
#include <QList>
#include <osg/ref_ptr>

class OSGBTool final : public QObject {
Q_OBJECT

private:
    static QMap<QString, QMap<QString, osg::ref_ptr<osg::Node>>> drawObjNode(const QString &objPath, const QString &mtlPath);

    static int vertexExist(const osg::ref_ptr<osg::Vec3Array> &vertexArray, osg::Vec3 vertex);

    void insertObjModel(double rx, double ry, double rz, const QString &name,const QString &objFilePath, double longitude,
                        double latitude, double height, double scale, const QString &epsg,
                        const QString &innerUrl = "");

public:
    void run(QList<QVariant> *in);

    OSGBTool();
};

