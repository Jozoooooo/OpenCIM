# OpenCIM

<img src="https://pic.imgdb.cn/item/64c325591ddac507cc9a5a6e.jpg" style="zoom:50%;"  alt=""/>

[![Static Badge](https://img.shields.io/badge/南师大-地科院-orange)](http://dky.njnu.edu.cn/)
![Static Badge](https://img.shields.io/badge/OpenCIM-LibCIMModel-blue)![Static Badge](https://img.shields.io/badge/OpenCIM-CIMCreator-blue)![Static Badge](https://img.shields.io/badge/OpenCIM-CIMViewer-blue)
![Static Badge](https://img.shields.io/badge/C%2B%2B-v17-green)![Static Badge](https://img.shields.io/badge/CMake-v3.25-green)

本仓库包含以下内容：

- LibCIMModel —— OpenCIM核心库，提供CIM交换格式操作SDK。
- ACIMTest —— OpenCIM创建的简单示例，调用LibCIMModel实现简单场景用例。
- SchemaConvert —— 读取指定格式xlsx文件自动生成CIM模式信息的可执行控制台程序。
- ACIMViewer_Lite——轻量化读取ACIM文件并可视化的可执行控制台程序。
- Paper —— 场景学主要著作。

## 文件结构

- 3rdlibs 外部库文件
- LibCIMModel、ACIMTest、SchemaConvert、ACIMViewer_Lite
- out 编译输出文件

## 安装

无需安装，采用CMake编译运行

## LibCIMModel

### 库依赖

LibCIMModel对JSON文件的读写依赖于nlohmann库。

### 库功能

- 创建、读取、查询、修改、保存CIMDataSet
- 创建、读取、查询、修改、保存CIMSchema
- 创建、读取、查询、修改、保存CIMSynthetic

### 使用说明

1. 编译LibCIMModel
2. 引入LibCIMModel头文件、静态链接库
3. 通过CreateCIMDataSet、CreateCIMSchema、CreateCIMSynthetic创建CIM操作接口
4. 通过场景接口实现场景功能

### 快速开始

#### 1、创建CIM模式信息

1. 引用"ICIMSchema.hpp"头文件
2. 使用命名空间"NNU::OpenCIM"
3. 调用CreateCIMSchema（）函数，创建CIMSchema接口
4. 使用CIMSchema创建公理和概念
5. 将公理和概念进行关联
6. 使用toJson（）方法将CIMSchema进行保存

示例如下：

```c++
#include "ICIMSchema.hpp"

using namespace NNU::OpenCIM;

void CIMSchema() {
    auto sceneStandard = CreateCIMSchema(); // 创建场景

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

    sceneStandard->toJson("Example/CIMSchema.json");
}
```

#### 2、创建CIM综合模型

1. 引用"ICIMDataSet.hpp"和 "ICIMSynthetic.hpp"头文件
2. 使用命名空间"NNU::OpenCIM"
3. 调用CreateCIMSchema（）函数，加载模式信息
4. 调用CreateCIMSynthetic（）函数，创建CIMSynthetic接口
5. 创建组件
6. 设置属性组件对应模式信息概念
7. 创建实体
8. 设置实体对应模式信息概念
9. 设置实体所包含组件
10. 创建系统
11. 设置关系组件对应模式信息概念
12. 将实体与系统进行关联
13. 使用toJson（）方法将CIMSynthetic进行保存

示例如下：

```c++
#include "ICIMSchema.hpp"
#include "ICIMSynthetic.hpp"

using namespace NNU::OpenCIM;

void CIMSynthetic() {
    // 打开场景标准
    auto sceneStandard = CreateCIMSchema();
    sceneStandard->fromJson("./Example/CIMSchema.json");

    // 创建场景
    auto sceneContent = CreateCIMSynthetic();

    // 创建场景头
    auto header = sceneContent->getHeader();
    header->setCIMName("NNU-ACIM");
    header->setCIMDescription("南师大老北区CIM3层级ACIM示例");
    header->addInclude(Include{STANDARD, "./CIMSchema.json"});

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
    spatialSystem->setEpsg("epsg:4549");

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
    entity->setBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("地形"))->getId());
    entity->addComponent(semantics_terrain->getId());
    entity->addComponent(geo_terrain->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());
    entity->addComponent(texture_terrain->getId());

    entity = sceneContent->createEntity();
    entity->getId()->setComments("建筑实体");
    entity->setBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("建筑"))->getId());
    entity->addComponent(semantic_building->getId());
    entity->addComponent(geo_building->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());

    entity = sceneContent->createEntity();
    entity->getId()->setComments("道路实体");
    entity->setBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("道路"))->getId());
    entity->addComponent(semantic_road->getId());
    entity->addComponent(geo_road->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());
    entity->addComponent(texture_road->getId());

    entity = sceneContent->createEntity();
    entity->getId()->setComments("水体实体");
    entity->setBelongConcept(
            sceneStandard->getConceptFromCode(sceneStandard->getConceptCodeFromName("水体"))->getId());
    entity->addComponent(semantic_water->getId());
    entity->addComponent(geo_water->getId());
    entity->addComponent(spatialSystem->getId());
    entity->addComponent(spatialLocation->getId());
    entity->addComponent(texture_water->getId());

    sceneContent->toJson("Example/NNU-ACIM/NNU-ACIM.json");
}
```

#### 3、创建CIM数据集

1. 引用"ICIMDataSet.hpp"头文件
2. 使用命名空间"NNU::OpenCIM"
3. 调用CreateCIMDataSet（）函数，创建CIMDataSet接口
4. 使用CIMDataSet接口读/写CIM数据集名称、CIM数据集作者、CIM数据集创建单位、CIM数据集创建时间、CIM数据集版本、模式信息路径、综合模型路径、表达模型路径等（详见"ICIMDataSet.hpp"头文件）
5. 使用toJson（）方法将CIMDataSet进行保存

示例如下：

```c++
#include "ICIMDataSet.hpp"

using namespace NNU::OpenCIM;

void CIMDateSet() {
    auto cimDateSet = CreateCIMDataSet();
    cimDateSet->fromJson("BasicInfo.CIM");
    cimDateSet->setInstitution("NNU");
    cimDateSet->toJson("test.CIM");
}
```

### 保存格式

采用JSON格式进行保存，JSON中为场景中各类型对象的列表，每一列表中储存着该类型下的所有对象，每一对象的JSON结构与逻辑结构一致。

![](https://pic.imgdb.cn/item/64c23f591ddac507cc386dea.jpg)

公理JSON结构示例

![](https://pic.imgdb.cn/item/64c2450f1ddac507cc44e24e.jpg)

概念JSON结构示例

### 更新记录

|  更新时间  | 更新类型 |                           更新内容                           |
| :--------: | :------: | :----------------------------------------------------------: |
| 2023.7.17  |   修改   |           场景头字段<br />场景头字段创建、查询接口           |
| 2023.7.17  |   新增   |                  用于描述场景信息的场景头类                  |
| 2023.7.17  |   修改   |              在【属性】中增加对“材质”描述的能力              |
| 2023.7.17  |   修改   | 将【时间位置】更名为【时间点】<br />将【时间几何】更名为【时间段】 |
| 2023.7.18  |   修改   |         “fromJson”函数实现代码<br />要素删除实现代码         |
| 2023.7.18  |   修改   |        外部场景模型字段<br />外部场景模型字段查询接口        |
| 2023.7.18  |   修改   |                    【机制】热拔插实现代码                    |
| 2023.7.21  |   修改   |                      将SetUv更名为SetUV                      |
| 2023.7.21  |   修改   |               将IMechanismPlugin更名为IPlugin                |
| 2023.7.21  |   修改   |               将CIMHeader.hpp/cpp移动至根目录                |
| 2023.7.21  |   新增   |                         用于描述材质                         |
| 2023.7.21  |   修改   |             材质字段<br />材质字段创建、查询接口             |
| 2023.7.21  |   修改   |                  删除【属性】中的“材质”描述                  |
| 2023.7.22  |   修改   | 将Property作为基类，派生出内部属性类和外部数据线类（纹理材质） |
| 2023.7.22  |   修改   |                   在Element添加“注解”字段                    |
| 2023.7.22  |   修改   |      添加“Meta”类型，场景间相互调用采用Meta类型进行调用      |
| 2023.7.22  |   新增   |                  getMeta函数实现获取元数据                   |
| 2023.7.22  |   修改   |                     将场景和场景标准拆分                     |
| 2023.7.24  |   修改   |                       整体结构进行微调                       |
|  2023.8.1  |   新增   |                新增根据注释查询场景要素的接口                |
| 2023.12.15 |   新增   |                       新增编码修改接口                       |
| 2023.12.15 |   新增   |                     概念新增概念类型字段                     |
| 2023.12.15 |   修改   |               实体、组件、系统概念映射接口调整               |
|  2024.2.6  |   修改   |                  接口名称与现有标准保持一致                  |
|  2024.2.6  |   新增   |               CIM数据集接口，用于读写.CIM文件                |
|  2024.2.6  |   修复   |             LibCIMModel setAreaNumber导致的错误              |
| 2024.2.27  |   修改   |                     空间系统改为EPSG描述                     |
| 2024.4.12  |   新增   |              新增实体名、实体编码、概念编码字段              |
| 2024.4.12  |   修改   |                    实体所属概念修改为唯一                    |

## ACIMTest

### 背景

### 库依赖

* ACIMTest 依赖于LibCIMModel库。

### 程序功能

程序中共有四个个示例函数：CIMSchema、CIMSynthetic、CIMDataSet、TestPlugin，分别用于测试模式层、ACIM综合模型、CIM数据集、ACIM插件接口。

### 快速开始

将CMakeList对应位置修改为如下形式，编译程序即可。

```cmake
#add_executable(ACIMCreator CIMSchema.cpp Mechanism/TestPlugin.cpp main.cpp NNU-ACIM.cpp)
add_library(ACIMCreator SHARED Mechanism/Plugin/HelloMechanism.cpp)
```

将CMakeList对应位置修改为如下形式。

```cmake
add_executable(ACIMCreator CIMSchema.cpp Mechanism/TestPlugin.cpp main.cpp NNU-ACIM.cpp)
# add_library(ACIMCreator SHARED Mechanism/Plugin/HelloMechanism.cpp)
```

在main.cpp文件中选择想要运行的函数。

```c++
int main() {
    CIMSchema();
    CIMSynthetic();
    CIMDataSet();
}
```

### 更新记录

|   更新时间    | 更新类型 |        更新内容         |
|:---------:|:----:|:-------------------:|
| 2023.7.17 |  修改  |       调整文件结构        |
| 2023.7.17 |  新增  | CIM1层级【公理】-【概念】标准示例 |
| 2023.7.17 |  新增  |     【材质】【纹理】示例      |
| 2023.7.18 |  新增  |       【机制】示例        |
| 2024.2.6  |  新增  |     CIM数据集构建示例      |

## SchemaConvert

### 功能

本程序为读取指定格式xlsx文件自动生成CIM模式信息的可执行控制台程序。

### 依赖库

- LibCIMModel
- xlnt

### 快速上手

1. 打开控制台。
2. 定位至程序路径。
3. 参数：程序名 xlsx路径 输出模式信息json路径【缺省】。

### xlsx格式

- 必须包含名为“分类表”和“颗粒表”的sheet。

- 可以包含名为“属性表”和“关系表”的sheet。

- 表单第一列为父概念名。

- 表单第二列为分类/颗粒依据。

- 表单第三列为子概念名。

- 表单第四列为叶子概念CIM编码。

- 示例：

  | FJGN       | GLYJ             | ZJGN           | BM     |
  | ---------- | ---------------- | -------------- | ------ |
  | 行政区     | 行政区的分类     | CIM1行政区     |        |
  | CIM1行政区 | CIM1行政区的分类 | CIM1国家       | 601000 |
  | CIM1行政区 | CIM1行政区的分类 | CIM1省级行政区 |        |

### 注

- 输出模式信息json路径可以缺省，缺省值为当前程序路径，自动生成result.json。
- 可以直接将xlsx文件拖拽至可执行程序上，便捷运行。

## ACIMViewer_Lite

### 功能

轻量化读取ACIM文件并可视化的可执行控制台程序

### 依赖库

- LibCIMModel

- OSG 3.6.5

- Qt 5.15.2

- OSGEarth 3.5

### 注意事项

- 本程序所需头文件与第三方库文件都已提供，可以编译生成可执行程序。
- **由于Gitee上传文件大小限制，本程序运行所需第三方DLL文件都未提供，需要用户自行编译并放于程序运行路径下。**
- OSG库地址为：[GitHub - openscenegraph/OpenSceneGraph: OpenSceneGraph git repository](https://github.com/openscenegraph/OpenSceneGraph)
- OSGEarth库地址为：[GitHub - gwaldron/osgearth: A 3D Mapping Engine & SDK for OpenSceneGraph.](https://github.com/gwaldron/osgearth)
- 程序中IFC解析的代码未提供，需要用户补全。
- **需要将Temp文件夹拷贝至程序运行目录。**
- 为方便用户测试，本程序提供了示例数据CIMDataSet-test，可以直接调用运行。
- CIMDataSet-test数据集为测试数据集，只有CIM3层级有地形和建筑，其他层级为空。
-  程序所在路径不能有中文。

### 快速上手

- 打开控制台。
- 定位至程序路径。
-  程序需要传入两个参数：数据集.CIM文件路径、要可视化的层级。如：“D:\NNU_CIM_DataSet_2024.01.28\BasicInfo.CIM 3”， 其中第二个参数”3“表示可视化数据集的CIM3层级。
- 键盘事件：点击F键缩放到场景、点击T键取消鼠标拖动场景后的"Throw"操作、点击A键打开"Throw"操作。
