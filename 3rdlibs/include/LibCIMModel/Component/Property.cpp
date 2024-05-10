#include <nlohmann/json.hpp>

#include "Property.hpp"

NNU::OpenCIM::Component::Property::Property() : _fieldType(UNKNOWNFIE), _source(UNKNOWNSRC) {
    _componentType = PROPERTY;
}

JSONSTR NNU::OpenCIM::Component::Property::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["ComponentType"] = _componentType;
    json["FieldName"] = _fieldName;
    json["Source"] = _source;
    json["FieldType"] = _fieldType;
    json["FieldValue"] = _fieldValue;

    for (const auto &belongConcept: _belongConcepts) {
        nlohmann::json belongConceptJson;
        json["BelongConcepts"].emplace_back(nlohmann::json::parse(belongConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Component::Property::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _componentType = json["ComponentType"];
    _fieldName = json["FieldName"];
    _source = json["Source"];
    _fieldType = json["FieldType"];
    _fieldValue = json["FieldValue"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept);
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::Property::getFieldName() const {
    return _fieldName;
}

[[maybe_unused]] void NNU::OpenCIM::Component::Property::setFieldName(const std::string &fieldName) {
    _fieldName = fieldName;
}

[[maybe_unused]] NNU::OpenCIM::Component::Source NNU::OpenCIM::Component::Property::getSource() const {
    return _source;
}

[[maybe_unused]] void NNU::OpenCIM::Component::Property::setSource(NNU::OpenCIM::Component::Source source) {
    _source = source;
}

[[maybe_unused]] NNU::OpenCIM::Component::FieldType NNU::OpenCIM::Component::Property::getFieldType() const {
    return _fieldType;
}

[[maybe_unused]] void
NNU::OpenCIM::Component::Property::setFieldType(NNU::OpenCIM::Component::FieldType fieldType) {
    _fieldType = fieldType;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Component::Property::getFieldValue() const {
    return _fieldValue;
}

[[maybe_unused]] void NNU::OpenCIM::Component::Property::setFieldValue(const std::string &fieldValue) {
    _fieldValue = fieldValue;
}
