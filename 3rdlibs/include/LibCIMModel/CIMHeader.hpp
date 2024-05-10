/****************************************************************************
- Copyright (c) 2023, NanJin Normal University
- File _name:CIMHeader.hpp
- Author:南京师范大学
- Version:1.0
 -Data:20223.7.28
- Description: 场景头文件，用于描述场景标准/场景内容文件的基础信息
- History : 2023.7.28 创建
******************************************************************************/

#pragma once

#include <string>
#include <vector>

#include "Common/Define.hpp"

namespace NNU::OpenCIM {
    class CIMSchemaImpl;

    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM {
    enum CIMType {
        STANDARD [[maybe_unused]],
        CONTENT [[maybe_unused]],
        UNKNOWNSCE
    };

    struct Include {
        Include(CIMType CIMType, std::string CIMPath) : CIMType(CIMType), CIMPath(std::move(CIMPath)) {

        }

        CIMType CIMType;
        std::string CIMPath;

        bool operator==(const Include &rhs) const {
            return CIMPath == rhs.CIMPath;
        }

        bool operator!=(const Include &rhs) const {
            return !(rhs == *this);
        }
    };


    class CIMHeader {
    private:
        std::string _CIMName; // 场景名
        CIMType _CIMType; // 场景类型
        std::string _CIMDate; // 场景创建日期 自动填写
        std::string _CIMDescription; // 场景描述信息
        std::vector<Include> _includes; // 引用的外部场景

        CIMHeader();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSchemaImpl;

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        [[nodiscard]] JSONSTR toJson() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getCIMName() const;

        [[maybe_unused]] void setCIMName(const std::string &CIMName);

        [[maybe_unused]] [[nodiscard]] const std::string &getCIMDate() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getCIMDescription() const;

        [[maybe_unused]] void setCIMDescription(const std::string &CIMDescription);

        [[maybe_unused]] [[nodiscard]] int getIncludeCount() const;

        [[maybe_unused]] [[nodiscard]] const Include &getInclude(int index) const;

        [[maybe_unused]] void addInclude(const Include &include);

        [[maybe_unused]] void removeInclude(const Include &include);

        [[maybe_unused]] [[nodiscard]] CIMType getCIMType() const;
    };
}