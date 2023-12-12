#include <fstream>

#include <nlohmann/json.hpp>
#include <sstream>

#include "ICIMStandard.hpp"
#include "CIMContentImpl.hpp"

NNU::OpenCIM::CIMHeader *NNU::OpenCIM::CIMContentImpl::getHeader() {
    return _CIMHeader;
}

NNU::OpenCIM::ICIMStandard *NNU::OpenCIM::CIMContentImpl::getIncludeCIMStandard() {
    return _includeStandard;
}

void NNU::OpenCIM::CIMContentImpl::toJson(const char *jsonPath) {
    nlohmann::json json;

    // 输出文件头
    json["Header"] = nlohmann::json::parse(_CIMHeader->toJson());

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

    // 调整输出实体编码
    for(auto entity: _entities)
    {
        if(entity->getComponentsCount() == 0)
        {
            continue;
        }

        auto conceptId = entity->getBelongConcept(0);
        auto code = conceptId->getCode();

        int count = 0;
        for(auto e: _entities)
        {
            if(e->getComponentsCount() == 0)
            {
                continue;
            }

            auto t = e->getBelongConcept(0);
            if(t == conceptId)
            {
                count++;
            }
        }

        std::ostringstream oss;
        oss << std::setw(6) << std::setfill('0') << count;
        std::string countString = oss.str();

        // 更新字符串
        code.replace(code.length() - countString.length(), countString.length(), countString);
        entity->getId()->setCode(code);
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

void NNU::OpenCIM::CIMContentImpl::fromJson(const char *jsonPath) {
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
        _CIMHeader->fromJson(json["Header"].dump());
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

    for (const auto &include: _CIMHeader->_includes) {
        std::filesystem::path pathObj(jsonPath);
        std::filesystem::path parentPath = pathObj.parent_path();
        auto path = parentPath.string() + "/" + include.CIMPath;
        if (include.CIMType == STANDARD) {
            auto tempCIMStandard = CreateCIMStandard();
            tempCIMStandard->fromJson(path.c_str());
            _includeStandard = tempCIMStandard;
        }

        if (include.CIMType == CONTENT) {
            auto tempCIMContent = CreateCIMContent();
            tempCIMContent->fromJson(path.c_str());
            _includeContent.emplace_back(tempCIMContent);
        }
    }
}

void NNU::OpenCIM::CIMContentImpl::release() {
    delete this;
}

NNU::OpenCIM::Common::ExternalData *NNU::OpenCIM::CIMContentImpl::createExternalData() {
    auto externalData = new NNU::OpenCIM::Common::ExternalData;
    _externalDatas.emplace_back(externalData);
    return externalData;
}

NNU::OpenCIM::Component::Semantics *NNU::OpenCIM::CIMContentImpl::createSemantics() {
    auto semantics = new NNU::OpenCIM::Component::Semantics;
    _components.emplace_back(semantics);
    return semantics;
}

NNU::OpenCIM::Component::SpatialGeometry *NNU::OpenCIM::CIMContentImpl::createSpatialGeometry() {
    auto geometry = new NNU::OpenCIM::Component::SpatialGeometry;
    _components.emplace_back(geometry);
    return geometry;
}

NNU::OpenCIM::Component::SpatialLocation *NNU::OpenCIM::CIMContentImpl::createSpatialLocation() {
    auto location = new NNU::OpenCIM::Component::SpatialLocation;
    _components.emplace_back(location);
    return location;
}

NNU::OpenCIM::Component::SpatialSystem *NNU::OpenCIM::CIMContentImpl::createSpatialSystem() {
    auto system = new NNU::OpenCIM::Component::SpatialSystem;
    _components.emplace_back(system);
    return system;
}

NNU::OpenCIM::Component::TemporalRange *NNU::OpenCIM::CIMContentImpl::createTemporalRange() {
    auto geometry = new NNU::OpenCIM::Component::TemporalRange;
    _components.emplace_back(geometry);
    return geometry;
}

NNU::OpenCIM::Component::TemporalPoint *NNU::OpenCIM::CIMContentImpl::createTemporalPoint() {
    auto location = new NNU::OpenCIM::Component::TemporalPoint;
    _components.emplace_back(location);
    return location;
}

NNU::OpenCIM::Component::TemporalSystem *NNU::OpenCIM::CIMContentImpl::createTemporalSystem() {
    auto system = new NNU::OpenCIM::Component::TemporalSystem;
    _components.emplace_back(system);
    return system;
}

NNU::OpenCIM::Component::Property *NNU::OpenCIM::CIMContentImpl::createProperty() {
    auto innerProperty = new NNU::OpenCIM::Component::Property;
    _components.emplace_back(innerProperty);
    return innerProperty;
}

NNU::OpenCIM::Entity::Entity *NNU::OpenCIM::CIMContentImpl::createEntity() {
    auto entity = new NNU::OpenCIM::Entity::Entity;
    _entities.emplace_back(entity);
    return entity;
}

NNU::OpenCIM::System::Relation *NNU::OpenCIM::CIMContentImpl::createRelation() {
    auto relation = new NNU::OpenCIM::System::Relation;
    _systems.emplace_back(relation);
    return relation;
}

NNU::OpenCIM::System::Evolution *NNU::OpenCIM::CIMContentImpl::createEvolution() {
    auto evolution = new NNU::OpenCIM::System::Evolution;
    _systems.emplace_back(evolution);
    return evolution;
}

NNU::OpenCIM::System::Mechanism *NNU::OpenCIM::CIMContentImpl::createMechanism() {
    auto mechanism = new NNU::OpenCIM::System::Mechanism;
    _systems.emplace_back(mechanism);
    return mechanism;
}


NNU::OpenCIM::Common::ExternalData *NNU::OpenCIM::CIMContentImpl::getExternalDataFromCode(const char *uid) {
    for (auto externalData: _externalDatas) {
        if (externalData->_id->getCode() == uid)
            return externalData;
    }
    return nullptr;
}

NNU::OpenCIM::Component::Component *NNU::OpenCIM::CIMContentImpl::getComponentFromCode(const char *uid) {
    for (auto component: _components) {
        if (component->getId()->getCode() == uid)
            return component;
    }
    return nullptr;
}

NNU::OpenCIM::Entity::Entity *NNU::OpenCIM::CIMContentImpl::getEntityFromCode(const char *uid) {
    for (auto entity: _entities) {
        if (entity->_id->getCode() == uid)
            return entity;
    }
    return nullptr;
}

NNU::OpenCIM::System::System *NNU::OpenCIM::CIMContentImpl::getSystemFromCode(const char *uid) {
    for (auto system: _systems) {
        if (system->getId()->getCode() == uid)
            return system;
    }
    return nullptr;
}


int NNU::OpenCIM::CIMContentImpl::getExternalDataCount() {
    return static_cast<int>(_externalDatas.size());
}

int NNU::OpenCIM::CIMContentImpl::getComponentsCount() {
    return static_cast<int>(_components.size());
}

int NNU::OpenCIM::CIMContentImpl::getEntitiesCount() {
    return static_cast<int>(_entities.size());
}

int NNU::OpenCIM::CIMContentImpl::getSystemsCount() {
    return static_cast<int>(_systems.size());
}

const char *NNU::OpenCIM::CIMContentImpl::getExternalDataCodeFromIndex(int index) {
    return _externalDatas[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMContentImpl::getComponentCodeFromIndex(int index) {
    return _components[index]->getId()->getCode().c_str();
}

const char *NNU::OpenCIM::CIMContentImpl::getEntityCodeFromIndex(int index) {
    return _entities[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMContentImpl::getSystemCodeFromIndex(int index) {
    return _systems[index]->getId()->getCode().c_str();
}

const char *NNU::OpenCIM::CIMContentImpl::getExternalDataCodeFromComments(const char *comments) {
    for (auto item: _externalDatas) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

const char *NNU::OpenCIM::CIMContentImpl::getComponentCodeFromComments(const char *comments) {
    for (auto item: _components) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

const char *NNU::OpenCIM::CIMContentImpl::getEntityCodeFromComments(const char *comments) {
    for (auto item: _entities) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

const char *NNU::OpenCIM::CIMContentImpl::getSystemCodeFromComments(const char *comments) {
    for (auto item: _systems) {
        if (item->getId()->getComments() == comments) {
            return item->getId()->getCode().c_str();
        }
    }

    return nullptr;
}

void NNU::OpenCIM::CIMContentImpl::removeExternalData(const char *uid) {
    for (auto externalData: _externalDatas) {
        if (externalData->_id->getCode() == uid) {
            auto it = std::find(_externalDatas.begin(), _externalDatas.end(), externalData);
            _externalDatas.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMContentImpl::removeComponent(const char *uid) {
    for (auto component: _components) {
        if (component->getId()->getCode() == uid) {
            auto it = std::find(_components.begin(), _components.end(), component);
            _components.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMContentImpl::removeEntity(const char *uid) {
    for (auto entity: _entities) {
        if (entity->getId()->getCode() == uid) {
            auto it = std::find(_entities.begin(), _entities.end(), entity);
            _entities.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMContentImpl::removeSystem(const char *uid) {
    for (auto system: _systems) {
        if (system->getId()->getCode() == uid) {
            auto it = std::find(_systems.begin(), _systems.end(), system);
            _systems.erase(it);
        }
    }
}

int NNU::OpenCIM::CIMContentImpl::getIncludeCIMContentCount() {
    return static_cast<int>(_includeContent.size());
}

NNU::OpenCIM::ICIMContent *NNU::OpenCIM::CIMContentImpl::getIncludeCIMContent(int index) {
    return _includeContent[index];
}

NNU::OpenCIM::CIMContentImpl::CIMContentImpl() : _CIMHeader(new CIMHeader), _includeStandard(nullptr) {
    _CIMHeader->_CIMType = CONTENT;
}

NNU::OpenCIM::CIMContentImpl::~CIMContentImpl() {
    delete _CIMHeader;

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
