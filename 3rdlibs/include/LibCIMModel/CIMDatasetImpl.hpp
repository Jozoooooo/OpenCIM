/**
@版权 (c) 2024 NanJin Normal University
@文件名 CIMDataSet.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 2024.2.6
@文件描述 CIM数据集接口的实现文件
@修订历史 2023.2.6 创建
**/

# pragma once

#include <string>
#include "ICIMDataSet.hpp"

namespace NNU::OpenCIM{
    class CIMDataSetImpl : public ICIMDataSet
    {
    public:
        explicit CIMDataSetImpl();

        void toJson(const char *jsonPath) override;

        void fromJson(const char *jsonPath) override;

        void release() override;

        const char *getName() override;

        void setName(const char *name) override;

        const char *getAuthor() override;

        void setAuthor(const char *author) override;

        const char *getInstitution() override;

        void setInstitution(const char *institution) override;

        const char *getDate() override;

        const char *getVersion() override;

        void setVersion(const char *version) override;

        const char *getSchemaPath() override;

        void setSchemaPath(const char *path) override;

        const char *getSyntheticPath(int i) override;

        const char *getSyntheticName(int i) override;

        void addSyntheticPath(const char *name, const char *path) override;

        void removeSyntheticPath(const char *name, const char *path) override;

        const char *getExpressionPath() override;

        void setExpressionPath(const char *path) override;

        ICIMSchema* getSchema() override;

        ICIMSynthetic* getSynthetic(int i) override;

        const char *getMD5() override;

        void setMD5(const char *md5) override;

        int getSyntheticCount() override;

    private:
        std::string _name;
        std::string _author;
        std::string _institution;
        std::string _version;
        std::string _date;
        std::string _schemaPath;
        std::vector<std::string> _syntheticName;
        std::vector<std::string> _syntheticPath;
        std::string _expressionPath;
        std::string _md5;

        ICIMSchema *_iCIMSchema;
        std::vector<ICIMSynthetic*> _iCIMSynthetic;
    };
}