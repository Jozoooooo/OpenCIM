#include <nlohmann/json.hpp>

#include "Semantics.hpp"

NNU::OpenCIM::Component::Semantics::Semantics() {
    _componentType = SEMANTICS;
}

JSONSTR NNU::OpenCIM::Component::Semantics::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["Definition"] = _definition;
    json["Description"] = _description;

    for (const auto &belongConcept: _belongConcepts) {
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::Semantics::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _definition = json["Definition"];
    _description = json["Description"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}


[[maybe_unused]] const std::string &NNU::OpenCIM::Component::Semantics::getDefinition() const {
    return _definition;
}

[[maybe_unused]] void NNU::OpenCIM::Component::Semantics::setDefinition(const std::string &definition) {
    _definition = definition;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::Semantics::getDescription() const {
    return _description;
}

[[maybe_unused]] void NNU::OpenCIM::Component::Semantics::setDescription(const std::string &description) {
    _description = description;
}