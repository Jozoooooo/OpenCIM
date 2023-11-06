#include <nlohmann/json.hpp>

#include "SpatialSystem.hpp"

NNU::OpenCIM::Component::SpatialSystem::SpatialSystem() : _coordinateSystem(UNKNOWNCOOR), _centralMeridian(120.0) {
    _componentType = ComponentType::SPATIALSYSTEM;
}

JSONSTR NNU::OpenCIM::Component::SpatialSystem::toJson() const {
    nlohmann::json json;


    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["CoordinateSystem"] = _coordinateSystem;
    json["CentralMeridian"] = _centralMeridian;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::SpatialSystem::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _coordinateSystem = json["CoordinateSystem"];
    _centralMeridian = json["CentralMeridian"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialSystem::getCentralMeridian() const {
    return _centralMeridian;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialSystem::setCentralMeridian(double centralMeridian) {
    SpatialSystem::_centralMeridian = centralMeridian;
}

[[maybe_unused]] NNU::OpenCIM::Component::CoordinateSystem
NNU::OpenCIM::Component::SpatialSystem::getCoordinateSystem() const {
    return _coordinateSystem;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialSystem::setCoordinateSystem(
        NNU::OpenCIM::Component::CoordinateSystem coordinateSystem) {
    _coordinateSystem = coordinateSystem;
}
