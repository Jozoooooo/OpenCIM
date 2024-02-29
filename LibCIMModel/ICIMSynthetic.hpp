/**
@版权 (c) 2023, NanJin Normal University
@文件名 ICIMSynthetic.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景内容接口文件，提供对场景内容的增删改查等原子操作
@修订历史 2023.7.28 创建
**/

#pragma once

#define  CIM_MODEL_EXPORTS

#ifdef CIM_MODEL_EXPORTS
#define CIM_MODEL_API __declspec(dllexport)
#else
#define CIM_MODEL_API __declspec(dllimport)
#endif

#include "Core/Axiom.hpp"
#include "Core/Concept.hpp"

#include "Common/Define.hpp"
#include "Common/ExternalData.hpp"

#include "Component/Component.hpp"
#include "Component/Semantics.hpp"
#include "Component/SpatialGeometry.hpp"
#include "Component/SpatialLocation.hpp"
#include "Component/SpatialSystem.hpp"
#include "Component/TemporalRange.hpp"
#include "Component/TemporalPoint.hpp"
#include "Component/TemporalSystem.hpp"
#include "Component/Property.hpp"
#include "Entity/Entity.hpp"
#include "System/System.hpp"
#include "System/Relation.hpp"
#include "System/Evolution.hpp"
#include "System/Mechanism.hpp"

#include "CIMHeader.hpp"
#include "ICIMSchema.hpp"

namespace NNU::OpenCIM {
    struct ICIMSynthetic {
        [[maybe_unused]] virtual CIMHeader *getHeader() = 0; // 获取场景头

        [[maybe_unused]]  virtual void toJson(const char *jsonPath) = 0; // 输出为json

        [[maybe_unused]]  virtual void fromJson(const char *jsonPath) = 0; // 读取json

        [[maybe_unused]] virtual void release() = 0; // 释放资源

        [[maybe_unused]] virtual ICIMSchema *getIncludeCIMStandard() = 0;

        [[maybe_unused]] virtual Common::ExternalData *createExternalData() = 0; // 创建外部数据

        [[maybe_unused]] virtual Component::Semantics *createSemantics() = 0; // 创建语义

        [[maybe_unused]] virtual Component::SpatialGeometry *createSpatialGeometry() = 0; // 创建空间几何

        [[maybe_unused]] virtual Component::SpatialLocation *createSpatialLocation() = 0; // 创建空间位置

        [[maybe_unused]] virtual Component::SpatialSystem *createSpatialSystem() = 0; // 创建空间系统

        [[maybe_unused]] virtual Component::TemporalRange *createTemporalRange() = 0; // 创建时间段

        [[maybe_unused]] virtual Component::TemporalPoint *createTemporalPoint() = 0; // 创建时间点

        [[maybe_unused]] virtual Component::TemporalSystem *createTemporalSystem() = 0; // 创建时间系统

        [[maybe_unused]] virtual Component::Property *createProperty() = 0; // 创建属性

        [[maybe_unused]] virtual Entity::Entity *createEntity() = 0; // 创建实体

        [[maybe_unused]] virtual System::Relation *createRelation() = 0; // 创建关系

        [[maybe_unused]] virtual System::Evolution *createEvolution() = 0; // 创建演化

        [[maybe_unused]] virtual System::Mechanism *createMechanism() = 0; // 创建机制

        [[maybe_unused]] virtual Common::ExternalData *getExternalDataFromCode(const char *uid) = 0; // 根据id获取外部数据

        [[maybe_unused]] virtual Component::Component *getComponentFromCode(const char *uid) = 0; // 根据id获取组件

        [[maybe_unused]] virtual Entity::Entity *getEntityFromCode(const char *uid) = 0; // 根据id获取实体

        [[maybe_unused]] virtual System::System *getSystemFromCode(const char *uid) = 0; // 根据id获取系统

        [[maybe_unused]] virtual int getExternalDataCount() = 0; // 获取外部数据总数

        [[maybe_unused]] virtual int getComponentsCount() = 0; // 获取组件总数

        [[maybe_unused]] virtual int getEntitiesCount() = 0; // 获取实体总数

        [[maybe_unused]] virtual int getSystemsCount() = 0; // 获取系统总数

        [[maybe_unused]] virtual const char *getExternalDataCodeFromIndex(int index) = 0; // 根据索引获取外部数据id

        [[maybe_unused]] virtual const char *getComponentCodeFromIndex(int index) = 0; // 根据索引获取组件id

        [[maybe_unused]] virtual const char *getEntityCodeFromIndex(int index) = 0; // 根据索引获取实体id

        [[maybe_unused]] virtual const char *getSystemCodeFromIndex(int index) = 0; // 根据索引获取系统id

        [[maybe_unused]] virtual const char *getExternalDataCodeFromComments(const char *comments) = 0; // 根据注释获取外部数据id

        [[maybe_unused]] virtual const char *getComponentCodeFromComments(const char *comments) = 0; // 根据注释获取外部数据id

        [[maybe_unused]] virtual const char *getEntityCodeFromComments(const char *comments) = 0; // 根据注释获取外部数据id

        [[maybe_unused]] virtual const char *getSystemCodeFromComments(const char *comments) = 0; // 根据注释获取外部数据id

        [[maybe_unused]] virtual void removeExternalData(const char *uid) = 0; // 删除外部数据

        [[maybe_unused]] virtual void removeComponent(const char *uid) = 0; // 删除组件

        [[maybe_unused]] virtual void removeEntity(const char *uid) = 0; // 删除实体

        [[maybe_unused]] virtual void removeSystem(const char *uid) = 0; // 删除系统

        [[maybe_unused]] virtual const char *getAreaNumber() = 0; // 获取行政区代码

        [[maybe_unused]] virtual void setAreaNumber(const char *areNumber) = 0; // 设置行政区代码

        [[maybe_unused]] virtual int getIncludeCIMContentCount() = 0; // 获取引用的外部场景内容的数量

        [[maybe_unused]] virtual ICIMSynthetic *getIncludeCIMContent(int index) = 0; // 根据索引获取引用的外部场景内容接口

        virtual bool mergeCIMSynthetic(const char *syntheticPath, bool mergeSame) = 0; // 合并综合模型（传入模型向当前模型合并）
    };

    extern "C" [[maybe_unused]]  CIM_MODEL_API ICIMSynthetic *CreateCIMSynthetic(); // 创建场景内容接口

    extern "C" [[maybe_unused]]  CIM_MODEL_API void DestroyCIMSynthetic(ICIMSynthetic *iCIMSynthetic); // 销毁场景模型接口
}


