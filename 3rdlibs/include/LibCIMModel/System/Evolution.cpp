#include <nlohmann/json.hpp>

#include "Evolution.hpp"

NNU::OpenCIM::System::Evolution::Evolution() : _fromEntity(new UniqueID()), _toEntity(new UniqueID()) {
    _systemType = SystemType::EVOLUTION;
}

JSONSTR NNU::OpenCIM::System::Evolution::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["SystemType"] = _systemType;
    json["FromEntity"] = nlohmann::json::parse(_fromEntity->toJson());
    json["ToEntity"] = nlohmann::json::parse(_toEntity->toJson());

    return json.dump();
}

void NNU::OpenCIM::System::Evolution::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _systemType = json["SystemType"];
    _fromEntity = new UniqueID(json["FromEntity"].dump());
    _toEntity = new UniqueID(json["ToEntity"].dump());

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::System::Evolution::getFromEntity() const {
    return _fromEntity;
}

[[maybe_unused]] void NNU::OpenCIM::System::Evolution::setFromEntity(UniqueID *fromEntity) {
    Evolution::_fromEntity = fromEntity;
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::System::Evolution::getToEntity() const {
    return _toEntity;
}

[[maybe_unused]] void NNU::OpenCIM::System::Evolution::setToEntity(UniqueID *toEntity) {
    Evolution::_toEntity = toEntity;
}
