#include <nlohmann/json.hpp>

#include "SpatialLocation.hpp"

NNU::OpenCIM::Component::SpatialLocation::SpatialLocation() : _panX(0), _panY(0), _panZ(0), _rotateX(0), _rotateY(0),
                                                                _rotateZ(0), _scale(1) {
    _componentType = SPATIALLOCATION;
}

JSONSTR NNU::OpenCIM::Component::SpatialLocation::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["PanX"] = _panX;
    json["PanY"] = _panY;
    json["PanZ"] = _panZ;
    json["RotateX"] = _rotateX;
    json["RotateY"] = _rotateY;
    json["RotateZ"] = _rotateZ;
    json["Scale"] = _scale;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::SpatialLocation::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _panX = json["PanX"];
    _panY = json["PanY"];
    _panZ = json["PanZ"];
    _rotateX = json["RotateX"];
    _rotateY = json["RotateY"];
    _rotateZ = json["RotateZ"];
    _scale = json["Scale"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialLocation::getPanX() const {
    return _panX;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialLocation::setPanX(double panX) {
    _panX = panX;
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialLocation::getPanY() const {
    return _panY;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialLocation::setPanY(double panY) {
    _panY = panY;
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialLocation::getPanZ() const {
    return _panZ;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialLocation::setPanZ(double panZ) {
    _panZ = panZ;
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialLocation::getRotateX() const {
    return _rotateX;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialLocation::setRotateX(double rotateX) {
    _rotateX = rotateX;
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialLocation::getRotateY() const {
    return _rotateY;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialLocation::setRotateY(double rotateY) {
    _rotateY = rotateY;
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialLocation::getRotateZ() const {
    return _rotateZ;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialLocation::setRotateZ(double rotateZ) {
    _rotateZ = rotateZ;
}

[[maybe_unused]] double NNU::OpenCIM::Component::SpatialLocation::getScale() const {
    return _scale;
}

[[maybe_unused]] void NNU::OpenCIM::Component::SpatialLocation::setScale(double scale) {
    _scale = scale;
}
