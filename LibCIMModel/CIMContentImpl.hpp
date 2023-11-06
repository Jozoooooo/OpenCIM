/**
@版权 (c) 2023, NanJin Normal University
@文件名 CIMContentImpl.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景内容接口的实现文件
@修订历史 2023.7.28 创建
**/

# pragma once

#include "ICIMContent.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl : public ICIMContent {
    public:
        CIMHeader *getHeader() override;

        ICIMStandard *getIncludeCIMStandard() override;

        void toJson(const char *jsonPath) override;

        void fromJson(const char *jsonPath) override;

        void release() override;

        Common::ExternalData *createExternalData() override;

        Component::Semantics *createSemantics() override;

        Component::SpatialGeometry *createSpatialGeometry() override;

        Component::SpatialLocation *createSpatialLocation() override;

        Component::SpatialSystem *createSpatialSystem() override;

        Component::TemporalRange *createTemporalRange() override;

        Component::TemporalPoint *createTemporalPoint() override;

        Component::TemporalSystem *createTemporalSystem() override;

        Component::Property *createProperty() override;

        Entity::Entity *createEntity() override;

        System::Relation *createRelation() override;

        System::Evolution *createEvolution() override;

        System::Mechanism *createMechanism() override;

        Common::ExternalData *getExternalDataFromCode(const char *uid) override;

        Component::Component *getComponentFromCode(const char *uid) override;

        Entity::Entity *getEntityFromCode(const char *uid) override;

        System::System *getSystemFromCode(const char *uid) override;

        int getExternalDataCount() override;

        int getComponentsCount() override;

        int getEntitiesCount() override;

        int getSystemsCount() override;

        const char *getExternalDataCodeFromIndex(int index) override;

        const char *getComponentCodeFromIndex(int index) override;

        const char *getEntityCodeFromIndex(int index) override;

        const char *getSystemCodeFromIndex(int index) override;

        const char *getExternalDataCodeFromComments(const char* comments) override;

        const char *getComponentCodeFromComments(const char* comments) override;

        const char *getEntityCodeFromComments(const char* comments) override;

        const char *getSystemCodeFromComments(const char* comments) override;

        void removeExternalData(const char *uid) override;

        void removeComponent(const char *uid) override;

        void removeEntity(const char *uid) override;

        void removeSystem(const char *uid) override;

        int getIncludeCIMContentCount() override;

        ICIMContent *getIncludeCIMContent(int index) override;

    private:
        ICIMStandard *_includeStandard;
        std::vector<ICIMContent *> _includeContent;

        CIMHeader *_CIMHeader;
        std::vector<Common::ExternalData *> _externalDatas;
        std::vector<Component::Component *> _components;
        std::vector<Entity::Entity *> _entities;
        std::vector<System::System *> _systems;

        friend ICIMContent *CreateCIMContent();

        CIMContentImpl();

        ~CIMContentImpl();
    };
}