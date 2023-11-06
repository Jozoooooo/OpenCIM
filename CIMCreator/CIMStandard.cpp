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
    auto CIMStandard = CreateCIMStandard(); // 创建场景

    // 设置头
    auto header = CIMStandard->getHeader();
    header->setCIMName("CIM数据集标准规范");
    header->setCIMDescription("仅作示例");

    // 创建概念
    auto cimSet = CIMStandard->createConcept();
    cimSet->setName("CIM数据集"); // 概念名
    cimSet->getId()->setComments(cimSet->getName()); // 概念描述

    auto cim1 = CIMStandard->createConcept();
    cim1->setName("CIM1层级"); // 概念名
    cim1->getId()->setComments(cim1->getName()); // 概念描述

    auto cim2 = CIMStandard->createConcept();
    cim2->setName("CIM2层级"); // 概念名
    cim2->getId()->setComments(cim2->getName()); // 概念描述

    auto cim3 = CIMStandard->createConcept();
    cim3->setName("CIM3层级"); // 概念名
    cim3->getId()->setComments(cim3->getName()); // 概念描述

    auto cim4 = CIMStandard->createConcept();
    cim4->setName("CIM4层级"); // 概念名
    cim4->getId()->setComments(cim4->getName()); // 概念描述

    auto cim5 = CIMStandard->createConcept();
    cim5->setName("CIM5层级"); // 概念名
    cim5->getId()->setComments(cim5->getName()); // 概念描述

    auto cim6 = CIMStandard->createConcept();
    cim6->setName("CIM6层级"); // 概念名
    cim6->getId()->setComments(cim6->getName()); // 概念描述

    auto cim7 = CIMStandard->createConcept();
    cim7->setName("CIM7层级"); // 概念名
    cim7->getId()->setComments(cim7->getName()); // 概念描述

    auto terrain = CIMStandard->createConcept();
    terrain->setName("地形模型"); // 概念名
    terrain->getId()->setComments(terrain->getName()); // 概念描述

    auto district = CIMStandard->createConcept();
    district->setName("行政区模型"); // 概念名
    district->getId()->setComments(district->getName()); // 概念描述

    auto city = CIMStandard->createConcept();
    city->setName("城市模型"); // 概念名
    city->getId()->setComments(city->getName()); // 概念描述

    auto archIn = CIMStandard->createConcept();
    archIn->setName("建筑内部模型"); // 概念名
    archIn->getId()->setComments(archIn->getName()); // 概念描述

    auto archOut = CIMStandard->createConcept();
    archOut->setName("建筑外部模型"); // 概念名
    archOut->getId()->setComments(archOut->getName()); // 概念描述

    auto traffic = CIMStandard->createConcept();
    traffic->setName("交通设施模型"); // 概念名
    traffic->getId()->setComments(traffic->getName()); // 概念描述

    auto water = CIMStandard->createConcept();
    water->setName("水系模型"); // 概念名
    water->getId()->setComments(water->getName()); // 概念描述

    auto vegetation = CIMStandard->createConcept();
    vegetation->setName("植被模型"); // 概念名
    vegetation->getId()->setComments(vegetation->getName()); // 概念描述

    auto municipal = CIMStandard->createConcept();
    municipal->setName("市政设施模型"); // 概念名
    municipal->getId()->setComments(municipal->getName()); // 概念描述

    auto site = CIMStandard->createConcept();
    site->setName("场地模型"); // 概念名
    site->getId()->setComments(site->getName()); // 概念描述

    auto geology = CIMStandard->createConcept();
    geology->setName("地质模型"); // 概念名
    geology->getId()->setComments(geology->getName()); // 概念描述

    auto cityparts = CIMStandard->createConcept();
    cityparts->setName("城市部件模型"); // 概念名
    cityparts->getId()->setComments(cityparts->getName()); // 概念描述

    auto waterconservancy = CIMStandard->createConcept();
    waterconservancy->setName("水利模型"); // 概念名
    waterconservancy->getId()->setComments(waterconservancy->getName()); // 概念描述

    auto landscape = CIMStandard->createConcept();
    landscape->setName("园林绿化模型"); // 概念名
    landscape->getId()->setComments(landscape->getName()); // 概念描述

    // 创建公理依据
    Core::Axiom::addBasis("信息等级");
    Core::Axiom::addBasis("实体");

    // 创建公理
    auto axiom = CIMStandard->createAxiom();
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

    axiom = CIMStandard->createAxiom();
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

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM1等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(1);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(city->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(traffic->getId());

    cim1->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM1等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(1);
    axiom->addConcept(cim1->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    traffic->addAxiom(axiom->getId());
    city->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());


    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM2等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(1);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(archIn->getId());
    axiom->addConcept(archOut->getId());
    axiom->addConcept(traffic->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    cim2->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM2等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(1);
    axiom->addConcept(cim2->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    archIn->addAxiom(axiom->getId());
    archOut->addAxiom(axiom->getId());
    traffic->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM3等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(1);
    axiom->addConcept(terrain->getId());
    axiom->addConcept(district->getId());
    axiom->addConcept(archIn->getId());
    axiom->addConcept(archOut->getId());
    axiom->addConcept(traffic->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());

    cim3->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM3等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(1);
    axiom->addConcept(cim3->getId());

    terrain->addAxiom(axiom->getId());
    district->addAxiom(axiom->getId());
    archIn->addAxiom(axiom->getId());
    archOut->addAxiom(axiom->getId());
    traffic->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM4等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(1);
    axiom->addConcept(archIn->getId());
    axiom->addConcept(archOut->getId());
    axiom->addConcept(traffic->getId());
    axiom->addConcept(municipal->getId());
    axiom->addConcept(water->getId());
    axiom->addConcept(vegetation->getId());
    axiom->addConcept(site->getId());
    axiom->addConcept(geology->getId());
    axiom->addConcept(cityparts->getId());

    cim4->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM4等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(1);
    axiom->addConcept(cim4->getId());

    archIn->addAxiom(axiom->getId());
    archOut->addAxiom(axiom->getId());
    traffic->addAxiom(axiom->getId());
    municipal->addAxiom(axiom->getId());
    water->addAxiom(axiom->getId());
    vegetation->addAxiom(axiom->getId());
    site->addAxiom(axiom->getId());
    geology->addAxiom(axiom->getId());
    cityparts->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM5等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(1);
    axiom->addConcept(archIn->getId());
    axiom->addConcept(archOut->getId());
    axiom->addConcept(traffic->getId());
    axiom->addConcept(municipal->getId());
    axiom->addConcept(waterconservancy->getId());
    axiom->addConcept(landscape->getId());

    cim5->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM5等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(1);
    axiom->addConcept(cim5->getId());

    archIn->addAxiom(axiom->getId());
    archOut->addAxiom(axiom->getId());
    traffic->addAxiom(axiom->getId());
    municipal->addAxiom(axiom->getId());
    waterconservancy->addAxiom(axiom->getId());
    landscape->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM6等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(1);
    axiom->addConcept(archIn->getId());
    axiom->addConcept(archOut->getId());
    axiom->addConcept(traffic->getId());
    axiom->addConcept(municipal->getId());
    axiom->addConcept(waterconservancy->getId());
    axiom->addConcept(landscape->getId());


    cim6->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM6等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(1);
    axiom->addConcept(cim6->getId());

    archIn->addAxiom(axiom->getId());
    archOut->addAxiom(axiom->getId());
    traffic->addAxiom(axiom->getId());
    municipal->addAxiom(axiom->getId());
    waterconservancy->addAxiom(axiom->getId());
    landscape->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM7等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::CONSISTOF);
    axiom->setBasis(1);
    axiom->addConcept(archIn->getId());
    axiom->addConcept(archOut->getId());
    axiom->addConcept(traffic->getId());
    axiom->addConcept(municipal->getId());
    axiom->addConcept(waterconservancy->getId());
    axiom->addConcept(landscape->getId());

    cim7->addAxiom(axiom->getId());

    axiom = CIMStandard->createAxiom();
    axiom->getId()->setComments("CIM7等级数据集按照实体的颗粒");
    axiom->setAxiomType(NNU::OpenCIM::Core::PARTOF);
    axiom->setBasis(1);
    axiom->addConcept(cim7->getId());

    archIn->addAxiom(axiom->getId());
    archOut->addAxiom(axiom->getId());
    traffic->addAxiom(axiom->getId());
    municipal->addAxiom(axiom->getId());
    waterconservancy->addAxiom(axiom->getId());
    landscape->addAxiom(axiom->getId());



    CIMStandard->toJson("Example/CIMStandard.json");
}