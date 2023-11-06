#include <nlohmann/json.hpp>

#include "Concept.hpp"

NNU::OpenCIM::Core::Concept::Concept() : _id(new UniqueID()) {

}

JSONSTR NNU::OpenCIM::Core::Concept::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["Names"] = _name;

    for (const auto &axiom: _axioms) {
        json["Axioms"].emplace_back(nlohmann::json::parse(axiom->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Core::Concept::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _name = json["Names"];

    for (const auto &axiom: json["Axioms"]) {
        auto uid = new UniqueID(axiom.dump());
        _axioms.emplace_back(uid);
    }
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::Core::Concept::getId() const {
    return _id;
}

[[maybe_unused]] int NNU::OpenCIM::Core::Concept::getAxiomsCount() const {
    return static_cast<int>(this->_axioms.size());
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::Core::Concept::getAxiomId(int index) const {
    return this->_axioms[index];
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Core::Concept::getName() const {
    return _name;
}

[[maybe_unused]] void NNU::OpenCIM::Core::Concept::addAxiom(UniqueID *axiom) {
    _axioms.emplace_back(axiom);
}

[[maybe_unused]] void NNU::OpenCIM::Core::Concept::removeAxiom(UniqueID *axiom) {
    auto it = std::find(_axioms.begin(), _axioms.end(), axiom);
    _axioms.erase(it);
}

[[maybe_unused]] void NNU::OpenCIM::Core::Concept::setName(const std::string &name) {
    Concept::_name = name;
}

bool NNU::OpenCIM::Core::Concept::operator==(const NNU::OpenCIM::Core::Concept &rhs) const {
    return _id == rhs._id;
}

bool NNU::OpenCIM::Core::Concept::operator!=(const NNU::OpenCIM::Core::Concept &rhs) const {
    return !(rhs == *this);
}

