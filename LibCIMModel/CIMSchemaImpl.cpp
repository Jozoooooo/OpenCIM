#include <fstream>

#include <nlohmann/json.hpp>

#include "CIMSchemaImpl.hpp"

NNU::OpenCIM::CIMHeader *NNU::OpenCIM::CIMSchemaImpl::getHeader() {
    return _cimHeader;
}

int NNU::OpenCIM::CIMSchemaImpl::getIncludeCIMStandardCount() {
    return static_cast<int>(_includeStandard.size());
}

NNU::OpenCIM::ICIMSchema *NNU::OpenCIM::CIMSchemaImpl::getIncludeCIMStandard(int index) {
    return _includeStandard[index];
}

void NNU::OpenCIM::CIMSchemaImpl::toJson(const char *jsonPath) {
    nlohmann::json json;

    // 输出文件头
    json["Header"] = nlohmann::json::parse(_cimHeader->toJson());

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

void NNU::OpenCIM::CIMSchemaImpl::fromJson(const char *jsonPath) {
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
        _cimHeader->fromJson(json["Header"].dump());
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

    for (const auto &include: _cimHeader->_includes) {
        if (include.CIMType == STANDARD) {
            auto tempCIMStandard = CreateCIMSchema();
            tempCIMStandard->fromJson(include.CIMPath.c_str());
            _includeStandard.emplace_back(tempCIMStandard);
        }
    }
}

void NNU::OpenCIM::CIMSchemaImpl::release() {
    delete this;
}

NNU::OpenCIM::Core::Axiom *NNU::OpenCIM::CIMSchemaImpl::createAxiom() {
    auto axiom = new NNU::OpenCIM::Core::Axiom();
    _axioms.emplace_back(axiom);
    return axiom;
}

NNU::OpenCIM::Core::Concept *NNU::OpenCIM::CIMSchemaImpl::createConcept() {
    auto concept = new NNU::OpenCIM::Core::Concept();
    _concepts.emplace_back(concept);
    return concept;
}

NNU::OpenCIM::Core::Axiom *NNU::OpenCIM::CIMSchemaImpl::getAxiomFromCode(const char *uid) {
    for (auto axiom: _axioms) {
        if (axiom->_id->getCode() == uid)
            return axiom;
    }
    return nullptr;
}

NNU::OpenCIM::Core::Concept *NNU::OpenCIM::CIMSchemaImpl::getConceptFromCode(const char *uid) {
    for (auto concept: _concepts) {
        if (concept->_id->getCode() == uid)
            return concept;
    }
    return nullptr;
}

int NNU::OpenCIM::CIMSchemaImpl::getAxiomsCount() {
    return static_cast<int>(_axioms.size());
}

int NNU::OpenCIM::CIMSchemaImpl::getConceptsCount() {
    return static_cast<int>(_concepts.size());
}

const char *NNU::OpenCIM::CIMSchemaImpl::getAxiomCodeFromIndex(int index) {
    return _axioms[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMSchemaImpl::getConceptCodeFromIndex(int index) {
    return _concepts[index]->_id->getCode().c_str();
}

const char *NNU::OpenCIM::CIMSchemaImpl::getConceptCodeFromName(const char *name) {
    for (auto concept: _concepts) {
        if (concept->getName() == name)
            return concept->getId()->getCode().c_str();
    }
    return nullptr;
}

void NNU::OpenCIM::CIMSchemaImpl::removeAxiom(const char *uid) {
    for (auto axiom: _axioms) {
        if (axiom->_id->getCode() == uid) {
            auto it = std::find(_axioms.begin(), _axioms.end(), axiom);
            _axioms.erase(it);
        }
    }
}

void NNU::OpenCIM::CIMSchemaImpl::removeConcept(const char *uid) {
    for (auto concept: _concepts) {
        if (concept->_id->getCode() == uid) {
            auto it = std::find(_concepts.begin(), _concepts.end(), concept);
            _concepts.erase(it);
        }
    }
}

NNU::OpenCIM::CIMSchemaImpl::CIMSchemaImpl() : _cimHeader(new CIMHeader()) {
    _cimHeader->_CIMType = STANDARD;
}

NNU::OpenCIM::CIMSchemaImpl::~CIMSchemaImpl() {
    delete _cimHeader;

    for (auto axiom: _axioms) {
        delete axiom;
    }

    for (auto concept: _concepts) {
        delete concept;
    }
}