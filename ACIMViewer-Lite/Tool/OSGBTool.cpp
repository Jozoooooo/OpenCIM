#include "OSGBTool.hpp"
#include "../View/ModelWidget.hpp"
#include "../ViewModel/MainWindowViewModel.hpp"
#include "osgEarth/GeoTransform"

#include <QVBoxLayout>
#include <QFileInfo>
#include <QDebug>
#include <osgDB/ReadFile>
#include <osg/Group>
#include <osg/Array>
#include <osg/PositionAttitudeTransform>
#include <osg/ComputeBoundsVisitor>
#include <osgEarth/SpatialReference>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>

void
OSGBTool::insertObjModel(double rx, double ry, double rz, const QString &name, const QString &objFilePath,
                         double longitude,
                         double latitude,
                         double height,
                         double scale, const QString &epsg, const QString &innerUrl) {

    QFileInfo objPath(objFilePath);
    auto baseName = objPath.baseName();

    osg::ref_ptr<osg::Group> model = new osg::Group;

    if (objPath.suffix() == "ifc") {
        int i = 0;
        for (const auto &temp: MainWindowViewModel::getInstance()->ifc2objList) {
            if (temp.contains(baseName)) {
                break;
            }
            ++i;
        }

        /********************************************************************************
         * 这里需要将IFC进行解析并加载
         * 由于各家IFC版本不同，解析方法不同，因此这里提前将IFC解析为OBJ格式并存放于exe所在的Temp文件夹下
         * 使用时需要根据实际情况进行调整
         ********************************************************************************/

        QFileInfo objFileInfo(QCoreApplication::applicationDirPath() + "/temp/" + baseName + ".obj");
        QFileInfo mtlFileInfo(QCoreApplication::applicationDirPath() + "/temp/" + baseName + ".mtl");

        auto tempObjList = drawObjNode(objFileInfo.absoluteFilePath(),
                                       mtlFileInfo.absoluteFilePath());
        MainWindowViewModel::getInstance()->ifc2objList.push_back(tempObjList);

        auto innerList = innerUrl.split(",");
        for (const auto &tempInner: innerList) {
            model->addChild(MainWindowViewModel::getInstance()->ifc2objList[i][baseName][tempInner].get());
        }

    } else
        model->addChild(osgDB::readNodeFile(objFilePath.toStdString()));
    if (!model) {
        qDebug() << "Model is  null";
        return;
    }
    model->setName("model");
    model->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);

    auto rotate = new osg::PositionAttitudeTransform;
    rotate->addChild(model);

    double rotationAngleX = osg::DegreesToRadians(rx);
    double rotationAngleY = osg::DegreesToRadians(ry);
    double rotationAngleZ = osg::DegreesToRadians(rz);
    osg::Quat rotationQuat(rotationAngleX, osg::Vec3d(1.0, 0.0, 0.0),
                           rotationAngleY, osg::Vec3d(0.0, 1.0, 0.0),
                           rotationAngleZ, osg::Vec3d(0.0, 0.0, 1.0));
    rotate->setAttitude(rotationQuat);

    osg::ComputeBoundsVisitor computeBoundsVisitor;
    rotate->accept(computeBoundsVisitor);

    auto center = computeBoundsVisitor.getBoundingBox().center();

    auto pan = new osg::PositionAttitudeTransform;
    pan->addChild(rotate);
    pan->setPosition(
            osg::Vec3d(-center.x() * scale, -center.y() * scale, -center.z() * scale));
    pan->setScale(
            osg::Vec3d(scale, scale, scale));

    auto radius = (computeBoundsVisitor.getBoundingBox().zMax() - computeBoundsVisitor.getBoundingBox().zMin()) / 2;

    auto geoTransform = new osgEarth::GeoTransform();
    geoTransform->setPosition(
            osgEarth::GeoPoint(osgEarth::SpatialReference::get(epsg.toStdString()), longitude, latitude,
                               height + radius * scale,
                               osgEarth::AltitudeMode::ALTMODE_RELATIVE));

    geoTransform->addChild(pan);

    geoTransform->setName(name.toStdString());
    geoTransform->setNodeMask(1);

    try {
        MainWindowViewModel::getInstance()->modelWidget->root->addChild(geoTransform);
    }
    catch (_exception e) {
        QMessageBox::information(nullptr, "Warning", e.name);
    }
}

void OSGBTool::run(QList<QVariant> *in) {
    if (in != nullptr) {
        auto epsg = (*in)[0].toString();
        double rx = (*in)[1].toDouble();
        double ry = (*in)[2].toDouble();
        double rz = (*in)[3].toDouble();
        double tx = (*in)[4].toDouble();
        double ty = (*in)[5].toDouble();
        double tz = (*in)[6].toDouble();
        double s = (*in)[7].toDouble();
        QString objPath = (*in)[8].toString();
        QString innerUrl = (*in)[9].toString();
        QString name = (*in)[10].toString();

        insertObjModel(rx, ry, rz, name, objPath, tx, ty, tz, s, epsg, innerUrl);
    }
}

QMap<QString, QMap<QString, osg::ref_ptr<osg::Node>>>
OSGBTool::drawObjNode(const QString &objPath, const QString &mtlPath) {
    QFileInfo objFileInfo(objPath);
    QFileInfo mtlFileInfo(mtlPath);

    QFile readObjFile(objFileInfo.absoluteFilePath());
    QFile readMtlFile(mtlFileInfo.absoluteFilePath());
    if ((!readObjFile.open(QIODevice::ReadOnly | QIODevice::Text) ||
         (!readMtlFile.open(QIODevice::ReadOnly | QIODevice::Text)))) {
        return {};
    }

    typedef struct point {
        double x;
        double y;
        double z;
    } point;

    QTextStream objStream(&readObjFile);
    QTextStream mtlStream(&readMtlFile);

    QList<point> vertex;
    QMap<QString, QList<double>> mtlColor;

    while (!mtlStream.atEnd()) {
        auto line = mtlStream.readLine();
        if (line == "")
            continue;
        if (line.mid(0, 6) == "newmtl") {
            auto mtlId = line.split(" ");
            auto kdColor = mtlStream.readLine().split(" ");
            auto transplant = mtlStream.readLine().split(" ");
            QList<double> tempList;
            tempList.push_back(kdColor[1].toDouble());
            tempList.push_back(kdColor[2].toDouble());
            tempList.push_back(kdColor[3].toDouble());
            tempList.push_back(transplant[1].toDouble());

            mtlColor[mtlId[1]] = tempList;
        }
    }

    while (!objStream.atEnd()) {
        auto line = objStream.readLine();
        if (line == "")
            continue;
        if (line[0] == "v" && line[1] == " ") {
            auto tempVertex = line.split(" ");

            auto x = tempVertex[1].toDouble();
            auto y = tempVertex[2].toDouble();
            auto z = tempVertex[3].toDouble();
            x /= 1000;
            y /= 1000;
            z /= 1000;
            auto tempX = ((int) x % 10000 + (x - (int) x));
            auto tempY = ((int) y % 10000 + (y - (int) y));
            vertex.push_back(point{tempX, tempY, z});
        }
    }

    QMap<QString, osg::ref_ptr<osg::Node>> singleObj;

    readObjFile.seek(0);
    QTextStream objStream2(&readObjFile);

    while (!objStream2.atEnd()) {
        auto line = objStream2.readLine();
        if (line == "")
            continue;
        if (line[0] == "g" && line[1] == " ") {
            QList<QList<int>> edgeList;
            osg::ref_ptr<osg::Geode> tempGeode = new osg::Geode();
            osg::ref_ptr<osg::Geometry> tempGeometry = new osg::Geometry();
            osg::ref_ptr<osg::Vec3Array> tempObjVertex = new osg::Vec3Array();
            osg::ref_ptr<osg::DrawElementsUInt> triangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

            auto singleObjId = line.split(" ");
            auto mtlId = objStream2.readLine().split(" ");
            auto tempLine = objStream2.readLine();
            while (!tempLine.contains(" normals")) {
                tempLine = objStream2.readLine();
            }
            tempLine = objStream2.readLine();
            while (tempLine[0] == "f" && tempLine[1] == " ") {
                QList<int> edgeIndex;
                auto fIndex = tempLine.split(" ");
                edgeIndex.push_back(fIndex[1].split("/")[0].toInt());
                edgeIndex.push_back(fIndex[2].split("/")[0].toInt());
                edgeIndex.push_back(fIndex[3].split("/")[0].toInt());
                edgeList.push_back(edgeIndex);
                tempLine = objStream2.readLine();
            }
            for (auto tempEdge: edgeList) {
                for (auto i = 0; i < 3; i++) {
                    auto flag = vertexExist(tempObjVertex,
                                            osg::Vec3(vertex[tempEdge[i] - 1].x, vertex[tempEdge[i] - 1].y,
                                                      vertex[tempEdge[i] - 1].z));
                    if (flag == -1) {
                        tempObjVertex->push_back(osg::Vec3(vertex[tempEdge[i] - 1].x, vertex[tempEdge[i] - 1].y,
                                                           vertex[tempEdge[i] - 1].z));
                        triangle->push_back(tempObjVertex->size() - 1);
                    } else {
                        triangle->push_back(flag);
                    }
                }
            }

            tempGeometry->addPrimitiveSet(triangle.get());
            tempGeometry->setVertexArray(tempObjVertex.get());

            osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
            colors->push_back(osg::Vec4(mtlColor[mtlId[1]][0], mtlColor[mtlId[1]][1], mtlColor[mtlId[1]][2],
                                        mtlColor[mtlId[1]][3]));
            tempGeometry->setColorArray(colors.get());
            tempGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
            tempGeode->addDrawable(tempGeometry.get());

            singleObj[singleObjId[1].mid(5)] = tempGeode->asNode();
        }
    }

    QFileInfo obj(objPath);
    QMap<QString, QMap<QString, osg::ref_ptr<osg::Node>>> tempObjList;
    tempObjList[obj.baseName()] = singleObj;

    readObjFile.close();
    readMtlFile.close();
    return tempObjList;
}

OSGBTool::OSGBTool() = default;

int OSGBTool::vertexExist(const osg::ref_ptr<osg::Vec3Array> &vertexArray, osg::Vec3 vertex) {
    for (auto i = 0; i < vertexArray->size(); i++) {
        if (vertexArray->at(i).x() == vertex.x() &&
            vertexArray->at(i).y() == vertex.y() &&
            vertexArray->at(i).z() == vertex.z()) {
            return i;
        }
    }
    return -1;
}

