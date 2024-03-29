﻿#include <nlohmann/json.hpp>

#include "Entity.hpp"

NNU::OpenCIM::Entity::Entity::Entity() = default;

JSONSTR NNU::OpenCIM::Entity::Entity::toJson() const {
    nlohmann::json json;


    json["Id"] = nlohmann::json::parse(_id->toJson());

    for (const auto &component: _components) {
        json["Components"].emplace_back(nlohmann::json::parse(component->toJson()));
    }

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Entity::Entity::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());

    for (const auto &component: json["Components"]) {
        auto uid = new UniqueID(component.dump());
        _components.emplace_back(uid);
    }

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] void NNU::OpenCIM::Entity::Entity::addComponent(UniqueID *componentId) {
    _components.emplace_back(componentId);
}

[[maybe_unused]] int NNU::OpenCIM::Entity::Entity::getComponentsCount() const {
    return static_cast<int>(_components.size());
}

[[maybe_unused]] const UniqueID *NNU::OpenCIM::Entity::Entity::getComponent(int index) const {
    return _components[index];
}

[[maybe_unused]] void NNU::OpenCIM::Entity::Entity::removeComponent(const UniqueID *componentId) {
    auto it = std::find(_components.begin(), _components.end(), componentId);
    _components.erase(it);
}