/**
@版权 (c) 2023, NanJin Normal University
@文件名 Property.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 属性组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM::Component {
    /**
    * 属性字段类型
    */
    enum FieldType {
        INT [[maybe_unused]],
        FLOAT [[maybe_unused]],
        STRING [[maybe_unused]],
        COMPLEX [[maybe_unused]],
        UNKNOWNFIE [[maybe_unused]]
    };

    /**
     * 属性字段来源
     */
    enum Source {
        EXTERNALPRO [[maybe_unused]],
        INTERNALPRO [[maybe_unused]],
        UNKNOWNSRC [[maybe_unused]]
    };

    class Property : public Component {
    private:
        std::string _fieldName; // 字段名
        Source _source; // 字段值来源
        FieldType _fieldType; // 字段类型
        std::string _fieldValue; // 字段值

        Property();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]]  JSONSTR toJson() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getFieldName() const;

        [[maybe_unused]] void setFieldName(const std::string &fieldName);

        [[maybe_unused]] [[nodiscard]] Source getSource() const;

        [[maybe_unused]] void setSource(Source source);

        [[maybe_unused]] [[nodiscard]] FieldType getFieldType() const;

        [[maybe_unused]] void setFieldType(FieldType fieldType);

        [[maybe_unused]] [[nodiscard]] const std::string &getFieldValue() const;

        [[maybe_unused]] void setFieldValue(const std::string &fieldValue);

    };
}
