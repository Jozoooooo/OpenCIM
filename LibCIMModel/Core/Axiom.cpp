#include <nlohmann/json.hpp>

#include "Axiom.hpp"

std::vector<std::string> NNU::OpenCIM::Core::Axiom::AxiomBasisSet;

NNU::OpenCIM::Core::Axiom::Axiom() : _id(new UniqueID()), _axiomType(NONE) {
}

[[maybe_unused]] void NNU::OpenCIM::Core::Axiom::addBasis(const std::string &basis) {
    AxiomBasisSet.emplace_back(basis);
}

[[maybe_unused]] int NNU::OpenCIM::Core::Axiom::getBasisCount() {
    return static_cast<int> (AxiomBasisSet.size());
}

[[maybe_unused]] std::string NNU::OpenCIM::Core::Axiom::getBasis(int index) {
    return AxiomBasisSet[index];
}

[[maybe_unused]] void NNU::OpenCIM::Core::Axiom::removeBasis(const std::string &basis) {
    auto it = std::find(AxiomBasisSet.begin(), AxiomBasisSet.end(), basis);
    AxiomBasisSet.erase(it);
}


JSONSTR NNU::OpenCIM::Core::Axiom::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["AxiomType"] = _axiomType;
    json["Basis"] = _basis;

    for (const auto &correspondingConcept: _correspondingConcepts) {
        json["CorrespondingConcepts"].emplace_back(nlohmann::json::parse(correspondingConcept->toJson()));
    }

    return json.dump();
}

void NNU::OpenCIM::Core::Axiom::fromJson(const JSONSTR &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _axiomType = json["AxiomType"];
    _basis = json["Basis"];

    for (const auto &correspondingConcept: json["CorrespondingConcepts"]) {
        auto uid = new UniqueID(correspondingConcept.dump());
        _correspondingConcepts.emplace_back(uid);
    }
}

bool NNU::OpenCIM::Core::Axiom::operator==(const Axiom &rhs) const {
    return _axiomType == rhs._axiomType &&
           _basis == rhs._basis;
}

bool NNU::OpenCIM::Core::Axiom::operator!=(const Axiom &rhs) const {
    return !(rhs == *this);
}

[[maybe_unused]] NNU::OpenCIM::Core::AxiomType NNU::OpenCIM::Core::Axiom::getAxiomType() const {
    return _axiomType;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Core::Axiom::getBasis() const {
    return _basis;
}

[[maybe_unused]] int NNU::OpenCIM::Core::Axiom::getBasisId() const {
    for (auto i = 0; i < AxiomBasisSet.size(); i++) {
        if (AxiomBasisSet[i] == _basis) {
            return i;
        }
    }
    return -1;
}

[[maybe_unused]] void NNU::OpenCIM::Core::Axiom::setAxiomType(AxiomType axiomType) {
    Axiom::_axiomType = axiomType;
}

[[maybe_unused]] void NNU::OpenCIM::Core::Axiom::setBasis(int index) {
    Axiom::_basis = AxiomBasisSet[index];
}

[[maybe_unused]] void NNU::OpenCIM::Core::Axiom::addConcept(UniqueID *conceptId) {
    _correspondingConcepts.emplace_back(conceptId);
}

[[maybe_unused]] int NNU::OpenCIM::Core::Axiom::getConceptCount() {
    return static_cast<int>(_correspondingConcepts.size());
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::Core::Axiom::getConcept(int index) {
    return _correspondingConcepts[index];
}

[[maybe_unused]] void NNU::OpenCIM::Core::Axiom::removeConcept(const UniqueID *conceptId) {
    auto it = std::find(_correspondingConcepts.begin(), _correspondingConcepts.end(), conceptId);
    _correspondingConcepts.erase(it);
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::Core::Axiom::getId() const {
    return _id;
}