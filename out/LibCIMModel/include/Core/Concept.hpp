/**
@版权 (c) 2023, NanJin Normal University
@文件名 Concept.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 概念描述文件，是对场景中所有要素的抽象，哲学上的描述，受公理的约束。
@修订历史 2023.7.28 创建
**/

#pragma once

#include <string>

#include "Axiom.hpp"

namespace NNU::OpenCIM {
    class CIMSchemaImpl;
}

namespace NNU::OpenCIM::Core {
    enum ConceptType {
        PROPERTY, //属性
        ENTITY, // 实体
        RELATION, // 关系
    };

    /**
     * 概念类
     */
    class [[maybe_unused]] Concept {
    private:
        UniqueID *_id; // 概念唯一标识
        std::string _name; // 概念名
        std::string _conceptCode; // 概念编码
        std::vector<UniqueID *> _axioms; // 公理集合
        ConceptType _conceptType;

        /**
          * 初始化概念，为概念构建唯一id
          */
        Concept();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSchemaImpl;

    public:
        /**
         * 概念唯一标识Getter方法
         * @return 概念唯一标识
         */
        [[maybe_unused]] [[nodiscard]] UniqueID *getId() const;

        /**
         * 重载相等运算符
         * @param rhs 对比的概念
         * @return 是否相等
         */
        bool operator==(const Concept &rhs) const;

        /**
         * 重载不相等运算符
         * @param rhs 对比的概念
         * @return 是否不相等
         */
        bool operator!=(const Concept &rhs) const;

        [[nodiscard]] virtual JSONSTR toJson() const;

        /**
         * 获取概念对应公理数量
         * @return
         */
        [[maybe_unused]] [[nodiscard]] int getAxiomsCount() const;

        /**
         * 根据序号获取公理
         * @param index 序号
         * @return 公理
         */
        [[maybe_unused]] [[nodiscard]] UniqueID *getAxiomId(int index) const;

        /**
         * 概念名Getter方法
         * @return 概念名
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getName() const;

        /**
         * 概念名Setter方法
         * @param name 概念名
         */
        [[maybe_unused]] void setName(const std::string &name);

        /**
        * 概念编码Getter方法
        * @return 概念编码
        */
        [[maybe_unused]] [[nodiscard]] const std::string &getConceptCode() const;

        /**
         * 概念编码Setter方法
         * @param name 概念编码
         */
        [[maybe_unused]] void setConceptCode(const std::string &conceptCode);

        /**
         * 添加公理
         * @param axiom 公理
         */
        [[maybe_unused]] void addAxiom(UniqueID *axiomId);

        /**
         * 删除公理
         * @param axiomId 公理Id
         */
        [[maybe_unused]] void removeAxiom(UniqueID *axiomId);

        [[nodiscard]] ConceptType getConceptType() const;

        void setConceptType(ConceptType conceptType);
    };
}
