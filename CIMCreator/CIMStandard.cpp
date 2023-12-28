/**
@版权 (c) 2023, NanJin Normal University
@文件名 CIMStandard.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 CIM场景公共基础标准的定义，作为场景标准定义样例。
@修订历史 2023.7.28 创建
**/

#include <ICIMStandard.hpp>

using namespace NNU::OpenCIM;

void CIMStandard() {
    auto sceneStandard = CreateCIMStandard(); // 创建场景

    // 设置头
    auto header = sceneStandard->getHeader();
    header->setCIMName("CIM数据集标准规范");
    header->setCIMDescription("仅作示例");

    // 创建概念
    auto cimSet = sceneStandard->createConcept();
    cimSet->setName("CIM数据集"); // 概念名
    cimSet->getId()->setComments(cimSet->getName()); // 概念描述

    auto cim1 = sceneStandard->createConcept();
    cim1->setName("CIM1层级"); // 概念名
    cim1->getId()->setComments(cim1->getName()); // 概念描述

    auto cim2 = sceneStandard->createConcept();
    cim2->setName("CIM2层级"); // 概念名
    cim2->getId()->setComments(cim2->getName()); // 概念描述

    auto cim3 = sceneStandard->createConcept();
    cim3->setName("CIM3层级"); // 概念名
    cim3->getId()->setComments(cim3->getName()); // 概念描述

    auto cim4 = sceneStandard->createConcept();
    cim4->setName("CIM4层级"); // 概念名
    cim4->getId()->setComments(cim4->getName()); // 概念描述

    auto cim5 = sceneStandard->createConcept();
    cim5->setName("CIM5层级"); // 概念名
    cim5->getId()->setComments(cim5->getName()); // 概念描述

    auto cim6 = sceneStandard->createConcept();
    cim6->setName("CIM6层级"); // 概念名
    cim6->getId()->setComments(cim6->getName()); // 概念描述

    auto cim7 = sceneStandard->createConcept();
    cim7->setName("CIM7层级"); // 概念名
    cim7->getId()->setComments(cim7->getName()); // 概念描述

    auto surface = sceneStandard->createConcept();
    surface->setName("地表模型"); // 概念名
    surface->getId()->setComments(surface->getName()); // 概念描述

    auto frame = sceneStandard->createConcept();
    frame->setName("框架模型"); // 概念名
    frame->getId()->setComments(frame->getName()); // 概念描述

    auto scenery = sceneStandard->createConcept();
    scenery->setName("实景模型"); // 概念名
    scenery->getId()->setComments(scenery->getName()); // 概念描述

    auto profession = sceneStandard->createConcept();
    profession->setName("专业模型"); // 概念名
    profession->getId()->setComments(profession->getName()); // 概念描述

    auto feature = sceneStandard->createConcept();
    feature->setName("功能模型"); // 概念名
    feature->getId()->setComments(feature->getName()); // 概念描述

    auto ops = sceneStandard->createConcept();
    ops->setName("运维模型"); // 概念名
    ops->getId()->setComments(ops->getName()); // 概念描述

    auto dynamic = sceneStandard->createConcept();
    dynamic->setName("动态模型"); // 概念名
    dynamic->getId()->setComments(dynamic->getName()); // 概念描述

    auto terrain = sceneStandard->createConcept();
    terrain->setName("地形"); // 概念名
    terrain->getId()->setComments(terrain->getName()); // 概念描述

    auto district = sceneStandard->createConcept();
    district->setName("行政区"); // 概念名
    district->getId()->setComments(district->getName()); // 概念描述

    auto arch = sceneStandard->createConcept();
    arch->setName("建筑"); // 概念名
    arch->getId()->setComments(arch->getName()); // 概念描述

    auto archIn = sceneStandard->createConcept();
    archIn->setName("建筑内部"); // 概念名
    archIn->getId()->setComments(archIn->getName()); // 概念描述

    auto archOut = sceneStandard->createConcept();
    archOut->setName("建筑外部"); // 概念名
    archOut->getId()->setComments(archOut->getName()); // 概念描述

    auto road = sceneStandard->createConcept();
    road->setName("道路"); // 概念名
    road->getId()->setComments(road->getName()); // 概念描述

    auto water = sceneStandard->createConcept();
    water->setName("水体"); // 概念名
    water->getId()->setComments(water->getName()); // 概念描述

    auto vegetation = sceneStandard->createConcept();
    vegetation->setName("植被"); // 概念名
    vegetation->getId()->setComments(vegetation->getName()); // 概念描述

    auto site = sceneStandard->createConcept();
    site->setName("场地"); // 概念名
    site->getId()->setComments(site->getName()); // 概念描述

    auto geology = sceneStandard->createConcept();
    geology->setName("地质"); // 概念名
    geology->getId()->setComments(geology->getName()); // 概念描述

    auto pipe = sceneStandard->createConcept();
    pipe->setName("管网"); // 概念名
    pipe->getId()->setComments(pipe->getName()); // 概念描述

    auto pipeIn = sceneStandard->createConcept();
    pipeIn->setName("管网内部"); // 概念名
    pipeIn->getId()->setComments(pipeIn->getName()); // 概念描述

    auto pipeOut = sceneStandard->createConcept();
    pipeOut->setName("管网外部"); // 概念名
    pipeOut->getId()->setComments(pipeOut->getName()); // 概念描述

    auto facility = sceneStandard->createConcept();
    facility->setName("设施"); // 概念名
    facility->getId()->setComments(facility->getName()); // 概念描述

    auto field = sceneStandard->createConcept();
    field->setName("环境场"); // 概念名
    field->getId()->setComments(field->getName()); // 概念描述

    // 创建公理依据
    Core::Axiom::addBasis("信息等级");
    Core::Axiom::addBasis("模型等级");
    Core::Axiom::addBasis("实体");

    // 创建公理
    auto axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM数据集按照信息等级的分类");
    axiom->setAxiomType(NNU::OpenCIM::Core::SUPEROF);
    axiom->setBasis(0);
    axiom->addConcept(cim1->getId());
    axiom->addConcept(cim2->getId());
    axiom->addConcept(cim3->getId());
    axiom->addConcept(cim4->getId());
    axiom->addConcept(cim5->getId());
    axiom->addConcept(cim6->getId());
    axiom->addConcept(cim7->getId());

    cimSet->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM数据集按照信息等级的分类");
    axiom->setAxiomType(NNU::OpenCIM::Core::SUBOF);
    axiom->setBasis(0);
    axiom->addConcept(cimSet->getId());

    cim1->addAxiom(axiom->getId());
    cim2->addAxiom(axiom->getId());
    cim3->addAxiom(axiom->getId());
    cim4->addAxiom(axiom->getId());
    cim5->addAxiom(axiom->getId());
    cim6->addAxiom(axiom->getId());
    cim7->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM数据集按照模型等级的分类");
    axiom->setAxiomType(NNU::OpenCIM::Core::SUPEROF);
    axiom->setBasis(1);
    axiom->addConcept(surface->getId());
    axiom->addConcept(frame->getId());
    axiom->addConcept(scenery->getId());
    axiom->addConcept(profession->getId());
    axiom->addConcept(feature->getId());
    axiom->addConcept(ops->getId());
    axiom->addConcept(dynamic->getId());

    cimSet->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM数据集按照模型等级的分类");
    axiom->setAxiomType(NNU::OpenCIM::Core::SUBOF);
    axiom->setBasis(1);
    axiom->addConcept(cimSet->getId());

    surface->addAxiom(axiom->getId());
    frame->addAxiom(axiom->getId());
    scenery->addAxiom(axiom->getId());
    profession->addAxiom(axiom->getId());
    feature->addAxiom(axiom->getId());
    ops->addAxiom(axiom->getId());
    dynamic->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("建筑按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(archIn->getId());
    axiom->addConcept(archOut->getId());

    arch->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("建筑按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(arch->getId());
    axiom->addConcept(archOut->getId());

    archIn->addAxiom(axiom->getId());
    archOut->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("管网按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(pipeIn->getId());
    axiom->addConcept(pipeOut->getId());

    pipe->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("管网按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(pipe->getId());

    pipeIn->addAxiom(axiom->getId());
    pipeOut->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM1等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    cim1->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM1等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(cim1->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM2等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    cim2->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM2等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(cim2->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM3等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    cim3->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM3等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(cim3->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM4等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());

    cim4->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM4等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(cim4->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM5等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());

    cim5->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM5等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(cim5->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM6等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());
    axiom->addConcept(facility->getId());

    cim6->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM6等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(cim6->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());
    facility->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM7等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());
    axiom->addConcept(facility->getId());
    axiom->addConcept(field->getId());

    cim7->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("CIM7等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(cim7->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());
    facility->addAxiom(axiom->getId());
    field->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("表面模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    surface->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("表面模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(surface->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("框架模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    frame->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("框架模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(frame->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("实景模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    scenery->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("实景模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(scenery->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("专业模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());

    profession->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("专业模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(profession->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("功能模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());

    feature->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("功能模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(feature->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("运维模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());
    axiom->addConcept(facility->getId());

    ops->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("运维模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(ops->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());
    facility->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("动态模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(2);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(arch->getId());
    axiom->addConcept(road->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(terrain->getId());
    axiom->addConcept(pipe->getId());
    axiom->addConcept(facility->getId());
    axiom->addConcept(field->getId());

    dynamic->addAxiom(axiom->getId());

    axiom = sceneStandard->createAxiom();
    axiom->getId()->setComments("动态模型数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(2);
    axiom->addConcept(dynamic->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    arch->addAxiom(axiom->getId());
    road->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    terrain->addAxiom(axiom->getId());
    pipe->addAxiom(axiom->getId());
    facility->addAxiom(axiom->getId());
    field->addAxiom(axiom->getId());

    sceneStandard->toJson("Example/CIMStandard.json");
}