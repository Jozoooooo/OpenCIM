#include <nlohmann/json.hpp>

#include "SpatialSystem.hpp"

NNU::OpenCIM::Component::SpatialSystem::SpatialSystem() : _epsg("epsg:4326") {
    _componentType = ComponentType::SPATIALSYSTEM;
}

JSONSTR NNU::OpenCIM::Component::SpatialSystem::toJson() const {
    nlohmann::json json;


    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["Epsg"] = _epsg;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::SpatialSystem::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _epsg = json["Epsg"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

const std::string &NNU::OpenCIM::Component::SpatialSystem::getEpsg() const {
    return _epsg;
}

void NNU::OpenCIM::Component::SpatialSystem::setEpsg(const std::string &epsg) {
    SpatialSystem::_epsg = epsg;
}