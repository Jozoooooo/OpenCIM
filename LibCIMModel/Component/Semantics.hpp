/**
@版权 (c) 2023, NanJin Normal University
@文件名 Semantics.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 语义组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl;
}

namespace NNU::OpenCIM::Component {
    /**
     * 语义组件类，继承自组件类
     */
    class Semantics : public Component {
    private:
        std::string _definition; // 语义定义
        std::string _description; // 语义描述

        /**
         * 语义初始化
         */
        Semantics();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMContentImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 语义定义Getter方法
         * @return 语义定义
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getDefinition() const;

        /**
         * 语义定义Setter方法
         * @param definition 语义定义
         */
        [[maybe_unused]] void setDefinition(const std::string &definition);

        /**
         * 语义描述Getter方法
         * @return 语义描述
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getDescription() const;

        /**
         * 语义描述Setter方法
         * @param description 语义描述
         */
        [[maybe_unused]] void setDescription(const std::string &description);
    };
}