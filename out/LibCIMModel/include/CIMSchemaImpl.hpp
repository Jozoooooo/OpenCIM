/**
@版权 (c) 2023, NanJin Normal University
@文件名 CIMSchemaImpl.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景标准接口的实现文件
@修订历史 2023.7.28 创建
**/

# pragma once

#include "ICIMSchema.hpp"

namespace NNU::OpenCIM {
    class CIMSchemaImpl : public ICIMSchema {
    public:
        CIMHeader *getHeader() override;

        int getIncludeCIMStandardCount() override;

        ICIMSchema *getIncludeCIMStandard(int index) override;

        void toJson(const char *jsonPath) override;

        void fromJson(const char *jsonPath) override;

        void release() override;

        Core::Axiom *createAxiom() override;

        Core::Concept *createConcept() override;

        Core::Axiom *getAxiomFromCode(const char *uid) override;

        Core::Concept *getConceptFromCode(const char *uid) override;

        int getAxiomsCount() override;

        int getConceptsCount() override;

        const char *getAxiomCodeFromIndex(int index) override;

        const char *getConceptCodeFromIndex(int index) override;

        void removeAxiom(const char *uid) override;

        void removeConcept(const char *uid) override;

        const char *getConceptCodeFromName(const char *name) override;

    private:
        std::vector<ICIMSchema *> _includeStandard;

        CIMHeader *_cimHeader;
        std::vector<Core::Axiom *> _axioms;
        std::vector<Core::Concept *> _concepts;

        friend ICIMSchema *CreateCIMSchema();

        CIMSchemaImpl();

        ~CIMSchemaImpl();
    };

}