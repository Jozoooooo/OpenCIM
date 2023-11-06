#include <nlohmann/json.hpp>

#include "Relation.hpp"

NNU::OpenCIM::System::Relation::Relation() {
    _systemType = SystemType::RELATION;
}

JSONSTR NNU::OpenCIM::System::Relation::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["SystemType"] = _systemType;
    json["Description"] = _description;

    for (const auto &fromEntity: _fromEntities) {
        json["FromEntities"].emplace_back(nlohmann::json::parse(fromEntity->toJson()));
    }

    for (const auto &toEntity: _toEntities) {
        json["ToEntities"].emplace_back(nlohmann::json::parse(toEntity->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::System::Relation::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _systemType = json["SystemType"];
    _description = json["Description"];

    for (const auto &fromEntity: json["FromEntities"]) {
        auto meta = new UniqueID(fromEntity.dump());
        _fromEntities.emplace_back(meta);
    }

    for (const auto &toEntity: json["ToEntities"]) {
        auto meta = new UniqueID(toEntity.dump());
        _toEntities.emplace_back(meta);
    }

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] const std::string &NNU::OpenCIM::System::Relation::getDescription() const {
    return _description;
}

[[maybe_unused]] void NNU::OpenCIM::System::Relation::setDescription(const std::string &description) {
    Relation::_description = description;
}


[[maybe_unused]] void NNU::OpenCIM::System::Relation::addFromEntity(UniqueID *entity) {
    _fromEntities.emplace_back(entity);
}

[[maybe_unused]] int NNU::OpenCIM::System::Relation::getFromEntitiesCount() const {
    return static_cast<int>(_fromEntities.size());
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::System::Relation::getFromEntity(int index) const {
    return _fromEntities[index];
}

[[maybe_unused]] void NNU::OpenCIM::System::Relation::removeFromEntity(UniqueID *entity) {
    auto it = std::find(_fromEntities.begin(), _fromEntities.end(), entity);
    _fromEntities.erase(it);
}

[[maybe_unused]] void NNU::OpenCIM::System::Relation::addToEntity(UniqueID *entity) {
    _toEntities.emplace_back(entity);
}

[[maybe_unused]] int NNU::OpenCIM::System::Relation::getToEntitiesCount() const {
    return static_cast<int>(_toEntities.size());
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::System::Relation::getToEntity(int index) const {
    return _toEntities[index];
}

[[maybe_unused]] void NNU::OpenCIM::System::Relation::removeToEntity(UniqueID *entity) {
    auto it = std::find(_toEntities.begin(), _toEntities.end(), entity);
    _toEntities.erase(it);
}

