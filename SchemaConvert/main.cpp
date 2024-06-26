#include <ICIMSchema.hpp>
#include <string>
#include <vector>
#include <set>
#include <xlnt/xlnt.hpp>

using namespace NNU::OpenCIM;
using namespace std;

struct ConceptWithCode {
    string name;
    string code;
};
struct ConceptDefinition {
    string name;
    string basis;
    vector<ConceptWithCode> children;
    int axiomType;
    Core::ConceptType conceptType;
};

void processSheet(xlnt::workbook &wb, const string &sheetName, int axiomType, Core::ConceptType conceptType,
                  vector<ConceptDefinition> &definitions) {
    auto ws = wb.sheet_by_title(sheetName);
    string currentName, currentBasis;
    vector<ConceptWithCode> currentChildren;

    for (auto row = ++ws.rows().begin(); row != ws.rows().end(); ++row) {
        string name = (*row)[0].to_string();
        string basis = (*row)[1].to_string();
        string child = (*row)[2].to_string();
        string BM = (*row)[3].to_string();

        if (name.empty() && basis.empty() && child.empty()) continue;

        if (currentName == name) {
            currentChildren.push_back({child, BM});
        } else {
            if (!currentName.empty()) {
                definitions.push_back({currentName, currentBasis, currentChildren, axiomType, conceptType});
            }
            currentName = name;
            currentBasis = basis;
            ConceptWithCode temp;
            temp.name = child;
            temp.code = BM;
            currentChildren = {temp};
        }
    }
    if (!currentName.empty()) {
        definitions.push_back({currentName, currentBasis, currentChildren, axiomType, conceptType});
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    string outputPath;
    if (argc < 3) {
        outputPath = "result.json";
    } else {
        outputPath = argv[2];
    }

    auto schema = CreateCIMSchema();
    schema->getHeader()->setCIMName("Example");
    schema->getHeader()->setCIMDescription("Dataset Standard Specification");

    xlnt::workbook wb;
    wb.load(argv[1]);

    vector<ConceptDefinition> definitions;
    processSheet(wb, "分类表", 4, Core::ENTITY, definitions);
    processSheet(wb, "颗粒表", 5, Core::ENTITY, definitions);
    processSheet(wb, "属性表", 1, Core::PROPERTY, definitions);
    processSheet(wb, "关系表", 7, Core::RELATION, definitions);

    set<string> processed;
    map<string, NNU::OpenCIM::Core::Concept *> concepts;
    for (const auto &def: definitions) {
        if (processed.find(def.name) == processed.end()) {
            auto concept = schema->createConcept();
            concept->setName(def.name);
            concept->setConceptType(def.conceptType);
            concept->getId()->setComments(def.name);
            processed.insert(def.name);
            concepts[def.name] = concept;
        }

        auto axiom = schema->createAxiom();
        axiom->setAxiomType(static_cast<NNU::OpenCIM::Core::AxiomType>(def.axiomType));
        if (def.axiomType == 4) {
            axiom->getId()->setComments(concepts[def.name]->getName() + "的分类");
        }
        if (def.axiomType == 5) {
            axiom->getId()->setComments(concepts[def.name]->getName() + "的颗粒");
        }
        if (def.axiomType == 1) {
            axiom->getId()->setComments(concepts[def.name]->getName() + "的属性");
        }
        if (def.axiomType == 7) {
            axiom->getId()->setComments(concepts[def.name]->getName() + "的关系");
        }

        bool hasBasis = false;
        for (auto i = 0; i < NNU::OpenCIM::Core::Axiom::getBasisCount(); i++) {
            auto basis = NNU::OpenCIM::Core::Axiom::getBasis(i);
            if (basis == def.basis) {
                axiom->setBasis(i);
                hasBasis = true;
                break;
            }
        }
        if (!hasBasis) {
            NNU::OpenCIM::Core::Axiom::addBasis(def.basis);
            axiom->setBasis(NNU::OpenCIM::Core::Axiom::getBasisCount() - 1);
        }

        for (const auto &childName: def.children) {
            if (processed.find(childName.name) == processed.end()) {
                auto childConcept = schema->createConcept();
                childConcept->setName(childName.name);
                childConcept->getId()->setComments(childName.name + childName.code);
                childConcept->setConceptType(def.conceptType);
                processed.insert(childName.name);
                concepts[childName.name] = childConcept;
                axiom->addConcept(childConcept->getId());
            } else {
                axiom->addConcept(concepts[childName.name]->getId());
            }
        }

        concepts[def.name]->addAxiom(axiom->getId());
    }

    schema->toJson(outputPath.c_str());
    return 0;
}