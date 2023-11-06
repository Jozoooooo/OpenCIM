#include <fstream>

#include <nlohmann/json.hpp>

#include "CIMStandardImpl.hpp"

NNU::OpenCIM::CIMHeader *NNU::OpenCIM::CIMStandardImpl::getHeader() {
    return _CIMHeader;
}

int NNU::OpenCIM::CIMStandardImpl::getIncludeCIMStandardCount() {
    return static_cast<int>(_includeStandard.size());
}

NNU::OpenCIM::ICIMStandard *NNU::OpenCIM::CIMStandardImpl::getIncludeCIMStandard(int index) {
    return _includeStandard[index];
}

void NNU::OpenCIM::CIMStandardImpl::toJson(const char *jsonPath) {
    nlohmann::json json;

    // 输出文件头
    json["Header"] = nlohmann::json::parse(_CIMHeader->toJson());

    // 输出公理
    for (auto axiom: _axioms) {
        json["Axioms"].emplace_back(nlohmann::json::parse(axiom->toJson()));
    }

    // 输出概念
    for (auto concept: _concepts) {
        json["Concepts"].emplace_back(nlohmann::json::parse(concept->toJson()));
    }

    std::ofstream file(jsonPath);
    file << json.dump(JSONINDENT);
}

void NNU::OpenCIM::CIMStandardImpl::fromJson(const char *jsonPath) {
    FILE *fp;
    auto error = fopen_s(&fp, jsonPath, "r");
    if (error) {
        return;
    }
    char buffer[1024 * 8];
    std::string result;
    while (fgets(buffer, 1024 * 8, fp) != nullptr) {
        result.append(buffer);
    }
    fclose(fp);

    nlohmann::json json = nlohmann::json::parse(result);

    if (json.contains("Header")) {
        _CIMHeader->fromJson(json["Header"].dump());
    }

    if (json.contains("Axioms")) {
        for (const auto &item: json["Axioms"]) {
            auto axiom = new Core::Axiom;
            axiom->fromJson(item.dump());
            _axioms.emplace_back(axiom);

            auto it = std::find(Core::Axiom::AxiomBasisSet.begin(), Core::Axiom::AxiomBasisSet.end(),
                                axiom->getBasis());

            if (it == Core::Axiom::AxiomBasisSet.end()) {
                Core::Axiom::AxiomBasisSet.emplace_back(axiom->getBasis());
            }
        }
    }

    if (json.contains("Concepts")) {
        for (const auto &item: json["Concepts"]) {
            auto concept = new Core::Concept;
            concept->fromJson(item.dump());
            _concepts.emplace_back(concept);
        }
    }

    for (const auto &include: _CIMHeader->_includes) {
        if (include.CIMType == STANDARD) {
            auto tempCIMStandard = CreateCIMStandard();
            tempCIMStandard->fromJson(include.CIMPath.c_str());
            _includeStandard.emplace_back(tempCIMStandard);
        }
    }
}

void NNU::OpenCIM::CIMStandardImpl::release() {
    delete this;
}

NNU::OpenCIM::Core::Axiom *NNU::OpenCIM::CIMStandardImpl::createAxiom() {
    auto axiom = new NNU::OpenCIM::Core::Axiom();
    _axioms.emplace_back(axiom);
    return axiom;
}

NNU::OpenCIM::Core::Concept *NNU::OpenCIM::CIMStandardImpl::createConcept() {
    auto concept = new NNU::OpenCIM::Core::Concept();
    _concepts.emplace_back(concept);
    return concept;
}

NNU::OpenCIM::Core::Axiom *NNU::OpenCIM::CIMStandardImpl::getAxiomFromCode(const char *uid) {
    for (auto axiom: _axioms) {
        if (axiom->_id->getCode() == uid)
            return axiom;
    }
    return nullptr;
}

NNU::OpenCIM::Core::Concept *NNU::OpenCIM::CIMStandardImpl::getConceptFromCode(const char *uid) {
    for (auto concept: _concepts) {
        if (concept->_id->getCode() == uid)
            return concept;
    }
    return nullptr;
}

int NNU::OpenCIM::CIMStandardImpl::getAxiomsCount() {
    return static_cast<int>(_axioms.size());
}

int NNU::OpenCIM::CIMStandardImpl::getConceptsCount() {
    return static_cast<int>(_concepts.size());
}

const char *NNU::OpenCIM::CIMStandardImpl::getAxiomCodeFromIndex(int index) {
    return _axioms[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMStandardImpl::getConceptCodeFromIndex(int index) {
    return _concepts[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMStandardImpl::getConceptCodeFromName(const char *name) {
    for (auto concept: _concepts) {
        if (concept->getName() == name)
            return concept->getId()->getCode().c_str();
    }
    return nullptr;
}

void NNU::OpenCIM::CIMStandardImpl::removeAxiom(const char *uid) {
    for (auto axiom: _axioms) {
        if (axiom->_id->getCode() == uid) {
            auto it = std::find(_axioms.begin(), _axioms.end(), axiom);
            _axioms.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMStandardImpl::removeConcept(const char *uid) {
    for (auto concept: _concepts) {
        if (concept->_id->getCode() == uid) {
            auto it = std::find(_concepts.begin(), _concepts.end(), concept);
            _concepts.erase(it);
        }
    }
}

NNU::OpenCIM::CIMStandardImpl::CIMStandardImpl() : _CIMHeader(new CIMHeader()) {
    _CIMHeader->_CIMType = STANDARD;
}

NNU::OpenCIM::CIMStandardImpl::~CIMStandardImpl() {
    delete _CIMHeader;

    for (auto axiom: _axioms) {
        delete axiom;
    }

    for (auto concept: _concepts) {
        delete concept;
    }
}