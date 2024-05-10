#include "MainWindowViewModel.hpp"

#include <QVariant>
#include <QtConcurrent/QtConcurrent>
#include <QProgressBar>

MainWindowViewModel *MainWindowViewModel::mainWindowViewModel = nullptr;

MainWindowViewModel::MainWindowViewModel() {
    osgbTool = new OSGBTool;
    modelWidget = new ModelWidget;
}

MainWindowViewModel *MainWindowViewModel::getInstance() {
    if (mainWindowViewModel == nullptr) {
        mainWindowViewModel = new MainWindowViewModel;
    }
    return mainWindowViewModel;
}

void MainWindowViewModel::addEntityToEarth() {
    //进度条
    QProgressBar progressBar;
    progressBar.setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    progressBar.setRange(0, 100);
    progressBar.setValue(0);
    progressBar.show();

    for (int i = 0; i < iCIMContent->getEntitiesCount(); i++) {
        QThread::msleep(100);
        int progress = static_cast<int>(((double) (i) / (double) iCIMContent->getEntitiesCount()) * 100);
        progressBar.setValue(progress);
        QCoreApplication::processEvents();

        const auto entityCode = iCIMContent->getEntityCodeFromIndex(i);
        const auto entity = iCIMContent->getEntityFromCode(entityCode);

        Component::SpatialSystem *spatialSystem;
        Component::SpatialLocation *spatialLocation;
        Component::SpatialGeometry *spatialGeometry;

        auto count = 0;
        for (int j = 0; j < entity->getComponentsCount(); j++) {
            const auto componentId = entity->getComponent(j);
            const auto component = iCIMContent->getComponentFromCode(componentId->getCode().c_str());

            if (component->getComponentType() == NNU::OpenCIM::Component::SPATIALSYSTEM) {
                spatialSystem = (Component::SpatialSystem *) component;
                count++;
            } else if (component->getComponentType() == NNU::OpenCIM::Component::SPATIALLOCATION) {
                spatialLocation = (NNU::OpenCIM::Component::SpatialLocation *) component;
                count++;
            } else if (component->getComponentType() == NNU::OpenCIM::Component::SPATIALGEOMETRY) {
                spatialGeometry = (NNU::OpenCIM::Component::SpatialGeometry *) component;
                count++;
            }

            if (count == 3) {
                break;
            }
        }

        auto in = new QList<QVariant>;

        if (count != 3) {
            continue;
        }
        in->append(QString::fromStdString(spatialSystem->getEpsg()));
        in->append(spatialLocation->getRotateX());
        in->append(spatialLocation->getRotateY());
        in->append(spatialLocation->getRotateZ());
        in->append(spatialLocation->getPanX());
        in->append(spatialLocation->getPanY());
        in->append(spatialLocation->getPanZ());
        in->append(spatialLocation->getScale());

        // 目前支持外部数据
        if (spatialGeometry->getSpatialGeometryType() == NNU::OpenCIM::Component::EXTERNALGEO) {
            const auto &externalDataId = spatialGeometry->getGeometry();
            auto externalData = MainWindowViewModel::getInstance()->iCIMContent->getExternalDataFromCode(
                    externalDataId.c_str());

            // 目前支持OSGB、IFC
            if (externalData->getDataFormat() == NNU::OpenCIM::Common::OSGB ||
                externalData->getDataFormat() == NNU::OpenCIM::Common::IFC ) {
                in->append(MainWindowViewModel::getInstance()->contentFileDir + "/" +
                           QString::fromStdString(externalData->getOuterUrl()));
                in->append(QString::fromStdString(externalData->getInnerUrl()));
            }

            in->append(QString::fromStdString(entity->getId()->getComments()));
            in->append(QString::fromStdString(entity->getId()->getCode()));

            if (externalData->getDataFormat() == NNU::OpenCIM::Common::OSGB || NNU::OpenCIM::Common::IFC) {
                osgbTool->run(in);
            }
        }
        delete in;
    }
}
