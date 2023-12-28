/**
@版权 (c) 2023, NanJin Normal University
@文件名 ACIM3.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 定义了南师大老北区CIM3层级ACIM文件，作为ACIM文件描述样例。
@修订历史 2023.7.28 创建
**/

#include <ICIMStandard.hpp>
#include <ICIMContent.hpp>

using namespace NNU::OpenCIM;

void NNUACIM() {
    // 打开场景标准
    auto sceneStandard = CreateCIMStandard();
    sceneStandard->fromJson("./Example/CIMStandard.json");

    // 创建场景
    auto sceneContent = CreateCIMContent();

    // 创建场景头
    auto header = sceneContent->getHeader();
    header->setCIMName("NNU-ACIM");
    header->setCIMDescription("南师大老北区CIM3层级ACIM示例");
    header->addInclude(Include{STANDARD, "./CIMStandard.json"});

    // 创建外部数据
    auto external_terrain = sceneContent->createExternalData();
    external_terrain->getId()->setComments("地形外部数据");
    external_terrain->setDataFormat(NNU::OpenCIM::Common::OBJ);
    external_terrain->setOuterUrl("./NNE.obj");

    auto external_terrainTEX = sceneContent->createExternalData();
    external_terrainTEX->getId()->setComments("地形纹理外部数据");
    external_terrainTEX->setDataFormat(NNU::OpenCIM::Common::PNG);
    external_terrainTEX->setOuterUrl("./NNU1.png");

    auto external_building = sceneContent->createExternalData();
    external_building->getId()->setComments("建筑外部数据");
    external_building->setDataFormat(NNU::OpenCIM::Common::OBJ);
    external_building->setOuterUrl("./building.obj");

    auto external_road = sceneContent->createExternalData();
    external_road->getId()->setComments("道路外部数据");
    external_road->setDataFormat(NNU::OpenCIM::Common::OBJ);
    external_road->setOuterUrl("./road.obj");

    auto external_roadTEX = sceneContent->createExternalData();
    external_roadTEX->getId()->setComments("道路纹理外部数据");
    external_roadTEX->setDataFormat(NNU::OpenCIM::Common::JPG);
    external_roadTEX->setOuterUrl("./RoadSurface.jpg");

    auto external_water = sceneContent->createExternalData();
    external_water->getId()->setComments("水体外部数据");
    external_water->setDataFormat(NNU::OpenCIM::Common::OBJ);
    external_water->setOuterUrl("./lake.obj");

    auto external_waterTEX = sceneContent->createExternalData();
    external_waterTEX->getId()->setComments("水体纹理外部数据");
    external_waterTEX->setDataFormat(NNU::OpenCIM::Common::JPG);
    external_waterTEX->setOuterUrl("./shuiwen.jpg");

    // 创建语义
    auto semantics_terrain = sceneContent->createSemantics();
    semantics_terrain->getId()->setComments("地形语义");
    semantics_terrain->setDefinition("地形");
    semantics_terrain->setDescription("地球表面上各种地貌、地势特征以及地面的形态");

    auto semantic_building = sceneContent->createSemantics();
    semantic_building->getId()->setComments("建筑语义");
    semantic_building->setDefinition("建筑");
    semantic_building->setDescription("构筑物、房屋、建物");

    auto semantic_road = sceneContent->createSemantics();
    semantic_road->getId()->setComments("道路语义");
    semantic_road->setDefinition("道路");
    semantic_road->setDescription("街道、路线、道途");

    auto semantic_water = sceneContent->createSemantics();
    semantic_water->getId()->setComments("水体语义");
    semantic_water->setDefinition("水体");
    semantic_water->setDescription("湖、河、海洋");

    // 创建几何
    auto geo_terrain = sceneContent->createSpatialGeometry();
    geo_terrain->getId()->setComments("地形几何");
    geo_terrain->setSpatialGeometryType(NNU::OpenCIM::Component::EXTERNALGEO);
    geo_terrain->setGeometry(external_terrain->getId()->getCode());

    auto geo_building = sceneContent->createSpatialGeometry();
    geo_building->getId()->setComments("建筑几何");
    geo_building->setSpatialGeometryType(NNU::OpenCIM::Component::EXTERNALGEO);
    geo_building->setGeometry(external_building->getId()->getCode());

    auto geo_road = sceneContent->createSpatialGeometry();
    geo_road->getId()->setComments("道路几何");
    geo_road->setSpatialGeometryType(NNU::OpenCIM::Component::EXTERNALGEO);
    geo_road->setGeometry(external_road->getId()->getCode());

    auto geo_water = sceneContent->createSpatialGeometry();
    geo_water->getId()->setComments("水体几何");
    geo_water->setSpatialGeometryType(NNU::OpenCIM::Component::EXTERNALGEO);
    geo_water->setGeometry(external_water->getId()->getCode());

    // 创建坐标系
    auto spatialSystem = sceneContent->createSpatialSystem();
    spatialSystem->getId()->setComments("2000坐标系");
    spatialSystem->setCoordinateSystem(NNU::OpenCIM::Component::CGCS2000_3);
    spatialSystem->setCentralMeridian(120);

    // 创建位置
    auto spatialLocation = sceneContent->createSpatialLocation();
    spatialLocation->getId()->setComments("不做变换");

    // 创建属性
    auto texture_terrain = sceneContent->createProperty();
    texture_terrain->getId()->setComments("地形漫反射纹理");
    texture_terrain->setFieldName(MaterialType[9]);
    texture_terrain->setSource(NNU::OpenCIM::Component::EXTERNALPRO);
    texture_terrain->setFieldType(NNU::OpenCIM::Component::COMPLEX);
    texture_terrain->setFieldValue(external_terrainTEX->getId()->getCode());

    auto texture_road = sceneContent->createProperty();
    texture_road->getId()->setComments("道路漫反射纹理");
    texture_road->setFieldName(MaterialType[9]);
    texture_road->setSource(NNU::OpenCIM::Component::EXTERNALPRO);
    texture_road->setFieldType(NNU::OpenCIM::Component::COMPLEX);
    texture_road->setFieldValue(external_roadTEX->getId()->getCode());

    auto texture_water = sceneContent->createProperty();
    texture_water->getId()->setComments("水体漫反射纹理");
    texture_water->setFieldName(MaterialType[9]);
    texture_water->setSource(NNU::OpenCIM::Component::EXTERNALPRO);
    texture_water->setFieldType(NNU::OpenCIM::Component::COMPLEX);
    texture_water->setFieldValue(external_waterTEX->getId()->getCode());

    // 创建实体
    auto entity = sceneContent->createEntity();
    entity->getId()->setComments("地形实体");
    entity->setClassificationBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("地形"))->getId());
    entity->setParticleBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("实景模型"))->getId());
    entity->addComponent(semantics_terrain->getId());
    entity->addComponent(geo_terrain->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());
    entity->addComponent(texture_terrain->getId());

    entity = sceneContent->createEntity();
    entity->getId()->setComments("建筑实体");
    entity->setClassificationBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("建筑"))->getId());
    entity->setParticleBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("实景模型"))->getId());
    entity->addComponent(semantic_building->getId());
    entity->addComponent(geo_building->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());

    entity = sceneContent->createEntity();
    entity->getId()->setComments("道路实体");
    entity->setClassificationBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("道路"))->getId());
    entity->setParticleBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("实景模型"))->getId());
    entity->addComponent(semantic_road->getId());
    entity->addComponent(geo_road->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());
    entity->addComponent(texture_road->getId());

    entity = sceneContent->createEntity();
    entity->getId()->setComments("水体实体");
    entity->setClassificationBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("水体"))->getId());
    entity->setParticleBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("实景模型"))->getId());
    entity->addComponent(semantic_water->getId());
    entity->addComponent(geo_water->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());
    entity->addComponent(texture_water->getId());

    sceneContent->toJson("Example/NNU-ACIM/NNU-ACIM.json");
}