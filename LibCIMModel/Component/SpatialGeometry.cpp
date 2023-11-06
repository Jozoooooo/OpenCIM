#include <nlohmann/json.hpp>

#include "SpatialGeometry.hpp"

NNU::OpenCIM::Component::SpatialGeometry::SpatialGeometry() : _spatialGeometryType(UNKNOWNGEO) {
    _componentType = SPATIALGEOMETRY;
}

JSONSTR NNU::OpenCIM::Component::SpatialGeometry::toJson() const {
    nlohmann::json json;


    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["SpatialGeometryType"] = _spatialGeometryType;
    json["Geometry"] = _geometry;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::SpatialGeometry::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _spatialGeometryType = json["SpatialGeometryType"];
    _geometry = json["Geometry"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] NNU::OpenCIM::Component::SpatialGeometryType
NNU::OpenCIM::Component::SpatialGeometry::getSpatialGeometryType() const {
    return _spatialGeometryType;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialGeometry::setSpatialGeometryType(
        NNU::OpenCIM::Component::SpatialGeometryType spatialGeometryType) {
    SpatialGeometry::_spatialGeometryType = spatialGeometryType;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::SpatialGeometry::getGeometry() const {
    return _geometry;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialGeometry::setGeometry(const std::string &geometry) {
    SpatialGeometry::_geometry = geometry;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::SpatialGeometry::getUV() const {
    return _uv;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialGeometry::setUV(const std::string &uv) {
    _uv = uv;
}
