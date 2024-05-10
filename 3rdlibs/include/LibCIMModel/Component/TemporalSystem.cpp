#include <nlohmann/json.hpp>

#include "TemporalSystem.hpp"

NNU::OpenCIM::Component::TemporalSystem::TemporalSystem() : _temporalSystemType(UNKNOWNTES) {
    _componentType = ComponentType::TEMPORALSYSTEM;
}

JSONSTR NNU::OpenCIM::Component::TemporalSystem::toJson() const {
    nlohmann::json json;


    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["TemporalSystemName"] = _temporalSystemName;
    json["TemporalSystemType"] = _temporalSystemType;
    json["RelativeTemporalSystem"] = _relativeTemporalSystem;
    json["Trans"] = _trans;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::TemporalSystem::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _temporalSystemName = json["TemporalSystemName"];
    _temporalSystemType = json["TemporalSystemType"];
    _relativeTemporalSystem = json["RelativeTemporalSystem"];
    _trans = json["Trans"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::TemporalSystem::getTemporalSystemName() const {
    return _temporalSystemName;
}

[[maybe_unused]] void
NNU::OpenCIM::Component::TemporalSystem::setTemporalSystemName(const std::string &temporalSystemName) {
    NNU::OpenCIM::Component::TemporalSystem::_temporalSystemName = temporalSystemName;
}

[[maybe_unused]] NNU::OpenCIM::Component::TemporalSystemType
NNU::OpenCIM::Component::TemporalSystem::getTemporalSystemType() const {
    return _temporalSystemType;
}

[[maybe_unused]] void
NNU::OpenCIM::Component::TemporalSystem::setTemporalSystemType(TemporalSystemType temporalSystemType) {
    NNU::OpenCIM::Component::TemporalSystem::_temporalSystemType = temporalSystemType;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::TemporalSystem::getRelativeTemporalSystem() const {
    return _relativeTemporalSystem;
}

[[maybe_unused]] void
NNU::OpenCIM::Component::TemporalSystem::setRelativeTemporalSystem(const std::string &relativeTemporalSystem) {
    NNU::OpenCIM::Component::TemporalSystem::_relativeTemporalSystem = relativeTemporalSystem;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::TemporalSystem::getTrans() const {
    return _trans;
}

[[maybe_unused]] void NNU::OpenCIM::Component::TemporalSystem::setTrans(const std::string &trans) {
    NNU::OpenCIM::Component::TemporalSystem::_trans = trans;
}
