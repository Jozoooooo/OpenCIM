#include <nlohmann/json.hpp>

#include "TemporalPoint.hpp"

NNU::OpenCIM::Component::TemporalPoint::TemporalPoint() {
    _componentType = ComponentType::TEMPORALPOINT;
}

JSONSTR NNU::OpenCIM::Component::TemporalPoint::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["TimeStamp"] = _timeStamp;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::TemporalPoint::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _timeStamp = json["TimeStamp"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::TemporalPoint::getTimeStamp() const {
    return _timeStamp;
}

[[maybe_unused]] void NNU::OpenCIM::Component::TemporalPoint::setTimeStamp(const std::string &timeStamp) {
    TemporalPoint::_timeStamp = timeStamp;
}
