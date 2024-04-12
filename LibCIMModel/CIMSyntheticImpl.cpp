#include <fstream>

#include <nlohmann/json.hpp>
#include <sstream>

#include "ICIMSchema.hpp"
#include "CIMSyntheticImpl.hpp"

NNU::OpenCIM::CIMHeader *NNU::OpenCIM::CIMSyntheticImpl::getHeader() {
    return _cimHeader;
}

NNU::OpenCIM::ICIMSchema *NNU::OpenCIM::CIMSyntheticImpl::getIncludeCIMStandard() {
    return _includeStandard;
}

void NNU::OpenCIM::CIMSyntheticImpl::toJson(const char *jsonPath) {
    nlohmann::json json;

    // 输出文件头
    json["Header"] = nlohmann::json::parse(_cimHeader->toJson());

    // 输出外部数据
    for (auto externalData: _externalDatas) {
        json["ExternalDatas"].emplace_back(nlohmann::json::parse(externalData->toJson()));
    }

    // 输出组件
    for (auto component: _components) {
        if (component->getComponentType() == NNU::OpenCIM::Component::SEMANTICS) {
            auto item = (NNU::OpenCIM::Component::Semantics *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else if (component->getComponentType() == NNU::OpenCIM::Component::SPATIALGEOMETRY) {
            auto item = (NNU::OpenCIM::Component::SpatialGeometry *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else if (component->getComponentType() == NNU::OpenCIM::Component::SPATIALLOCATION) {
            auto item = (NNU::OpenCIM::Component::SpatialLocation *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else if (component->getComponentType() == NNU::OpenCIM::Component::SPATIALSYSTEM) {
            auto item = (NNU::OpenCIM::Component::SpatialSystem *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else if (component->getComponentType() == NNU::OpenCIM::Component::TEMPORALRANGE) {
            auto item = (NNU::OpenCIM::Component::TemporalRange *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else if (component->getComponentType() == NNU::OpenCIM::Component::TEMPORALPOINT) {
            auto item = (NNU::OpenCIM::Component::TemporalPoint *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else if (component->getComponentType() == NNU::OpenCIM::Component::TEMPORALSYSTEM) {
            auto item = (NNU::OpenCIM::Component::TemporalSystem *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else {
            auto item = (NNU::OpenCIM::Component::Property *) component;
            json["Components"].emplace_back(nlohmann::json::parse(item->toJson()));
        }
    }

    // 输出实体
    for (auto entity: _entities) {
        json["Entities"].emplace_back(nlohmann::json::parse(entity->toJson()));
    }

    // 输出系统
    for (auto system: _systems) {
        if (system->getSystemType() == NNU::OpenCIM::System::RELATION) {
            auto item = (NNU::OpenCIM::System::Relation *) system;
            json["Systems"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else if (system->getSystemType() == NNU::OpenCIM::System::EVOLUTION) {
            auto item = (NNU::OpenCIM::System::Evolution *) system;
            json["Systems"].emplace_back(nlohmann::json::parse(item->toJson()));
        } else {
            auto item = (NNU::OpenCIM::System::Mechanism *) system;
            json["Systems"].emplace_back(nlohmann::json::parse(item->toJson()));
        }
    }

    std::ofstream file(jsonPath);
    file << json.dump(JSONINDENT);
}

void NNU::OpenCIM::CIMSyntheticImpl::fromJson(const char *jsonPath) {
    FILE *fp;
    auto error = fopen_s(&fp, jsonPath, "r");
    if (error) {
        return;
    }
    char buffer[1024 * 8];
    std::string result;
    while (fgets(buffer, 1024 * 8, fp) != nullptr) {
        result.append(buffer);
    }
    fclose(fp);

    nlohmann::json json = nlohmann::json::parse(result);

    if (json.contains("Header")) {
        _cimHeader->fromJson(json["Header"].dump());
    }

    if (json.contains("ExternalDatas")) {
        for (const auto &item: json["ExternalDatas"]) {
            auto externalData = new Common::ExternalData;
            externalData->fromJson(item.dump());
            _externalDatas.emplace_back(externalData);
        }
    }

    if (json.contains("Components")) {
        for (auto item: json["Components"]) {
            if (item["ComponentType"] == 0) {
                auto semantics = new Component::Semantics;
                semantics->fromJson(item.dump());
                _components.emplace_back(semantics);
            }

            if (item["ComponentType"] == 1) {
                auto spatialLocation = new Component::SpatialLocation;
                spatialLocation->fromJson(item.dump());
                _components.emplace_back(spatialLocation);
            }

            if (item["ComponentType"] == 2) {
                auto spatialSystem = new Component::SpatialSystem;
                spatialSystem->fromJson(item.dump());
                _components.emplace_back(spatialSystem);
            }

            if (item["ComponentType"] == 3) {
                auto spatialGeometry = new Component::SpatialGeometry;
                spatialGeometry->fromJson(item.dump());
                _components.emplace_back(spatialGeometry);
            }

            if (item["ComponentType"] == 4) {
                auto temporalPoint = new Component::TemporalPoint;
                temporalPoint->fromJson(item.dump());
                _components.emplace_back(temporalPoint);
            }

            if (item["ComponentType"] == 5) {
                auto temporalSystem = new Component::TemporalSystem;
                temporalSystem->fromJson(item.dump());
                _components.emplace_back(temporalSystem);
            }

            if (item["ComponentType"] == 6) {
                auto temporalRange = new Component::TemporalRange;
                temporalRange->fromJson(item.dump());
                _components.emplace_back(temporalRange);
            }

            if (item["ComponentType"] == 7) {
                auto property = new Component::Property;
                property->fromJson(item.dump());
                _components.emplace_back(property);
            }
        }
    }

    if (json.contains("Entities")) {
        for (const auto &item: json["Entities"]) {
            auto entity = new Entity::Entity;
            entity->fromJson(item.dump());
            _entities.emplace_back(entity);
        }
    }

    if (json.contains("Systems")) {
        for (auto item: json["Systems"]) {
            if (item["SystemType"] == 0) {
                auto relation = new System::Relation;
                relation->fromJson(item.dump());
                _systems.emplace_back(relation);
            }

            if (item["SystemType"] == 1) {
                auto evolution = new System::Evolution;
                evolution->fromJson(item.dump());
                _systems.emplace_back(evolution);
            }

            if (item["SystemType"] == 2) {
                auto mechanism = new System::Mechanism;
                mechanism->fromJson(item.dump());
                _systems.emplace_back(mechanism);
            }
        }
    }

    for (const auto &include: _cimHeader->_includes) {
        std::filesystem::path pathObj(jsonPath);
        std::filesystem::path parentPath = pathObj.parent_path();
        auto path = parentPath.string() + "/" + include.CIMPath;
        if (include.CIMType == STANDARD) {
            auto tempCIMStandard = CreateCIMSchema();
            tempCIMStandard->fromJson(path.c_str());
            _includeStandard = tempCIMStandard;
        }

        if (include.CIMType == CONTENT) {
            auto tempCIMContent = CreateCIMSynthetic();
            tempCIMContent->fromJson(path.c_str());
            _includeContent.emplace_back(tempCIMContent);
        }
    }
}

void NNU::OpenCIM::CIMSyntheticImpl::release() {
    delete this;
}

NNU::OpenCIM::Common::ExternalData *NNU::OpenCIM::CIMSyntheticImpl::createExternalData() {
    auto externalData = new NNU::OpenCIM::Common::ExternalData;
    _externalDatas.emplace_back(externalData);
    return externalData;
}

NNU::OpenCIM::Component::Semantics *NNU::OpenCIM::CIMSyntheticImpl::createSemantics() {
    auto semantics = new NNU::OpenCIM::Component::Semantics;
    _components.emplace_back(semantics);
    return semantics;
}

NNU::OpenCIM::Component::SpatialGeometry *NNU::OpenCIM::CIMSyntheticImpl::createSpatialGeometry() {
    auto geometry = new NNU::OpenCIM::Component::SpatialGeometry;
    _components.emplace_back(geometry);
    return geometry;
}

NNU::OpenCIM::Component::SpatialLocation *NNU::OpenCIM::CIMSyntheticImpl::createSpatialLocation() {
    auto location = new NNU::OpenCIM::Component::SpatialLocation;
    _components.emplace_back(location);
    return location;
}

NNU::OpenCIM::Component::SpatialSystem *NNU::OpenCIM::CIMSyntheticImpl::createSpatialSystem() {
    auto system = new NNU::OpenCIM::Component::SpatialSystem;
    _components.emplace_back(system);
    return system;
}

NNU::OpenCIM::Component::TemporalRange *NNU::OpenCIM::CIMSyntheticImpl::createTemporalRange() {
    auto geometry = new NNU::OpenCIM::Component::TemporalRange;
    _components.emplace_back(geometry);
    return geometry;
}

NNU::OpenCIM::Component::TemporalPoint *NNU::OpenCIM::CIMSyntheticImpl::createTemporalPoint() {
    auto location = new NNU::OpenCIM::Component::TemporalPoint;
    _components.emplace_back(location);
    return location;
}

NNU::OpenCIM::Component::TemporalSystem *NNU::OpenCIM::CIMSyntheticImpl::createTemporalSystem() {
    auto system = new NNU::OpenCIM::Component::TemporalSystem;
    _components.emplace_back(system);
    return system;
}

NNU::OpenCIM::Component::Property *NNU::OpenCIM::CIMSyntheticImpl::createProperty() {
    auto innerProperty = new NNU::OpenCIM::Component::Property;
    _components.emplace_back(innerProperty);
    return innerProperty;
}

NNU::OpenCIM::Entity::Entity *NNU::OpenCIM::CIMSyntheticImpl::createEntity() {
    auto entity = new NNU::OpenCIM::Entity::Entity;
    _entities.emplace_back(entity);
    return entity;
}

NNU::OpenCIM::System::Relation *NNU::OpenCIM::CIMSyntheticImpl::createRelation() {
    auto relation = new NNU::OpenCIM::System::Relation;
    _systems.emplace_back(relation);
    return relation;
}

NNU::OpenCIM::System::Evolution *NNU::OpenCIM::CIMSyntheticImpl::createEvolution() {
    auto evolution = new NNU::OpenCIM::System::Evolution;
    _systems.emplace_back(evolution);
    return evolution;
}

NNU::OpenCIM::System::Mechanism *NNU::OpenCIM::CIMSyntheticImpl::createMechanism() {
    auto mechanism = new NNU::OpenCIM::System::Mechanism;
    _systems.emplace_back(mechanism);
    return mechanism;
}


NNU::OpenCIM::Common::ExternalData *NNU::OpenCIM::CIMSyntheticImpl::getExternalDataFromCode(const char *uid) {
    for (auto externalData: _externalDatas) {
        if (externalData->_id->getCode() == uid)
            return externalData;
    }
    return nullptr;
}

NNU::OpenCIM::Component::Component *NNU::OpenCIM::CIMSyntheticImpl::getComponentFromCode(const char *uid) {
    for (auto component: _components) {
        if (component->getId()->getCode() == uid)
            return component;
    }
    return nullptr;
}

NNU::OpenCIM::Entity::Entity *NNU::OpenCIM::CIMSyntheticImpl::getEntityFromCode(const char *uid) {
    for (auto entity: _entities) {
        if (entity->_id->getCode() == uid)
            return entity;
    }
    return nullptr;
}

NNU::OpenCIM::System::System *NNU::OpenCIM::CIMSyntheticImpl::getSystemFromCode(const char *uid) {
    for (auto system: _systems) {
        if (system->getId()->getCode() == uid)
            return system;
    }
    return nullptr;
}


int NNU::OpenCIM::CIMSyntheticImpl::getExternalDataCount() {
    return static_cast<int>(_externalDatas.size());
}

int NNU::OpenCIM::CIMSyntheticImpl::getComponentsCount() {
    return static_cast<int>(_components.size());
}

int NNU::OpenCIM::CIMSyntheticImpl::getEntitiesCount() {
    return static_cast<int>(_entities.size());
}

int NNU::OpenCIM::CIMSyntheticImpl::getSystemsCount() {
    return static_cast<int>(_systems.size());
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getExternalDataCodeFromIndex(int index) {
    return _externalDatas[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getComponentCodeFromIndex(int index) {
    return _components[index]->getId()->getCode().c_str();
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getEntityCodeFromIndex(int index) {
    return _entities[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getSystemCodeFromIndex(int index) {
    return _systems[index]->getId()->getCode().c_str();
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getExternalDataCodeFromComments(const char *comments) {
    for (auto item: _externalDatas) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getComponentCodeFromComments(const char *comments) {
    for (auto item: _components) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getEntityCodeFromComments(const char *comments) {
    for (auto item: _entities) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getSystemCodeFromComments(const char *comments) {
    for (auto item: _systems) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

void NNU::OpenCIM::CIMSyntheticImpl::removeExternalData(const char *uid) {
    for (auto externalData: _externalDatas) {
        if (externalData->_id->getCode() == uid) {
            auto it = std::find(_externalDatas.begin(), _externalDatas.end(), externalData);
            _externalDatas.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMSyntheticImpl::removeComponent(const char *uid) {
    for (auto component: _components) {
        if (component->getId()->getCode() == uid) {
            auto it = std::find(_components.begin(), _components.end(), component);
            _components.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMSyntheticImpl::removeEntity(const char *uid) {
    for (auto entity: _entities) {
        if (entity->getId()->getCode() == uid) {
            auto it = std::find(_entities.begin(), _entities.end(), entity);
            _entities.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMSyntheticImpl::removeSystem(const char *uid) {
    for (auto system: _systems) {
        if (system->getId()->getCode() == uid) {
            auto it = std::find(_systems.begin(), _systems.end(), system);
            _systems.erase(it);
        }
    }
}

int NNU::OpenCIM::CIMSyntheticImpl::getIncludeCIMContentCount() {
    return static_cast<int>(_includeContent.size());
}

NNU::OpenCIM::ICIMSynthetic *NNU::OpenCIM::CIMSyntheticImpl::getIncludeCIMContent(int index) {
    return _includeContent[index];
}

NNU::OpenCIM::CIMSyntheticImpl::CIMSyntheticImpl() : _cimHeader(new CIMHeader), _includeStandard(nullptr) {
    _cimHeader->_CIMType = CONTENT;
}

NNU::OpenCIM::CIMSyntheticImpl::~CIMSyntheticImpl() {
    delete _cimHeader;

    for (auto externalData: _externalDatas) {
        delete externalData;
    }

    for (auto component: _components) {
        delete component;
    }

    for (auto entity: _entities) {
        delete entity;
    }

    for (auto system: _systems) {
        delete system;
    }
}

const char *NNU::OpenCIM::CIMSyntheticImpl::getAreaNumber() {
    return _areaNumber.c_str();
}

void NNU::OpenCIM::CIMSyntheticImpl::setAreaNumber(const char *areNumber) {
    this->_areaNumber = areNumber;
}

bool NNU::OpenCIM::CIMSyntheticImpl::mergeCIMSynthetic(const char *syntheticPath, bool mergeSame) {
    return false;
}
