/**
@版权 (c) 2023, NanJin Normal University
@文件名 ICIMStandard.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景标准接口文件，提供对场景标准的增删改查等原子操作
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

namespace NNU::OpenCIM {
    struct ICIMStandard {
        [[maybe_unused]] virtual CIMHeader *getHeader() = 0; // 获取场景头

        [[maybe_unused]]  virtual void toJson(const char *jsonPath) = 0; // 输出为json

        [[maybe_unused]]  virtual void fromJson(const char *jsonPath) = 0; // 输出为json

        [[maybe_unused]] virtual void release() = 0; // 释放资源

        [[maybe_unused]] virtual int getIncludeCIMStandardCount() = 0;

        [[maybe_unused]] virtual ICIMStandard *getIncludeCIMStandard(int index) = 0;

        [[maybe_unused]] virtual Core::Axiom *createAxiom() = 0; // 创建公理

        [[maybe_unused]] virtual Core::Concept *createConcept() = 0; // 创建概念

        [[maybe_unused]] virtual Core::Axiom *getAxiomFromCode(const char *uid) = 0; // 根据id获取公理

        [[maybe_unused]] virtual Core::Concept *getConceptFromCode(const char *uid) = 0; // 根据id获取概念

        [[maybe_unused]] virtual int getAxiomsCount() = 0; // 获取公理总数

        [[maybe_unused]] virtual int getConceptsCount() = 0; // 获取概念总数

        [[maybe_unused]] virtual const char *getAxiomCodeFromIndex(int index) = 0; // 根据索引获取公理id

        [[maybe_unused]] virtual const char *getConceptCodeFromIndex(int index) = 0; // 根据索引获取概念id

        [[maybe_unused]] virtual const char *getConceptCodeFromName(const char *name) = 0;

        [[maybe_unused]] virtual void removeAxiom(const char *uid) = 0; // 删除公理

        [[maybe_unused]] virtual void removeConcept(const char *uid) = 0; // 删除概念
    };


    extern "C" [[maybe_unused]]  CIM_MODEL_API ICIMStandard *CreateCIMStandard(); // 创建场景标准接口

    extern "C" [[maybe_unused]]  CIM_MODEL_API void DestroyCIMStandard(ICIMStandard *iCIMStandard); // 销毁场景标准接口
}