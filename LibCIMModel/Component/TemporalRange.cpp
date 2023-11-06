#include <nlohmann/json.hpp>

#include "TemporalRange.hpp"

NNU::OpenCIM::Component::TemporalRange::TemporalRange() {
    _componentType = ComponentType::TEMPORALRANGE;
}

JSONSTR NNU::OpenCIM::Component::TemporalRange::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["StartTime"] = _startTime;
    json["EndTime"] = _endTime;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::TemporalRange::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _startTime = json["StartTime"];
    _endTime = json["EndTime"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::TemporalRange::getStartTime() const {
    return _startTime;
}

[[maybe_unused]] void NNU::OpenCIM::Component::TemporalRange::setStartTime(const std::string &startTime) {
    TemporalRange::_startTime = startTime;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::TemporalRange::getEndTime() const {
    return _endTime;
}

[[maybe_unused]] void NNU::OpenCIM::Component::TemporalRange::setEndTime(const std::string &endTime) {
    TemporalRange::_endTime = endTime;
}
