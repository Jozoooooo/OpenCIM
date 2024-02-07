/**
@版权 (c) 2023, NanJin Normal University
@文件名 Axiom.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 公理结构的定义，主要用于对概念进行逻辑约束。
@修订历史 2023.7.28 创建
**/

#pragma once

#include <vector>

#include "../Common/Define.hpp"
#include "../Common/UniqueID.hpp"

namespace NNU::OpenCIM {
    class CIMSchemaImpl;
}

namespace NNU::OpenCIM::Core {
    /**
     * 公理类型
     */
    enum AxiomType {
        NONE, // 无意义，用于对应公理判断
        EFFECT, // 作用
        DERIVABLE, // 推导
        SUBOF, // 分类关系中的子类关系
        SUPEROF, // 分类关系中的父类关系
        CONSISTOF, // 颗粒中的父颗粒
        PARTOF, // 颗粒中的子颗粒
        AFFILIATE, // 附属关系
    };

    /**
     * 公理
     */
    class [[maybe_unused]] Axiom {
    private:
        static std::vector<std::string> AxiomBasisSet; // “公理依据”集合

        UniqueID *_id; // 组件唯一标识、
        AxiomType _axiomType; // 公理类型
        std::string _basis; // 公理依据
        std::vector<UniqueID *> _correspondingConcepts; // 公理所对应概念集合

        /**
         * 公理初始化函数
         */
        Axiom();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSchemaImpl;

    public:
        /**
         * 添加公理依据，静态函数
         * @param basis 公理依据
         */
        [[maybe_unused]] static void addBasis(const std::string &basis);

        [[maybe_unused]] [[maybe_unused]] static int getBasisCount();

        [[maybe_unused]] [[maybe_unused]] static std::string getBasis(int index);

        [[maybe_unused]] [[maybe_unused]] static void removeBasis(const std::string &basis);

        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 重载相等运算符，公理类型、公理依据相同的判定为同一公理
         * @param rhs
         * @return
         */
        bool operator==(const Axiom &rhs) const;

        /**
         * 重载不相等运算符
         * @param rhs
         * @return
         */
        bool operator!=(const Axiom &rhs) const;

        /**
         * 公理类型Getter方法
         * @return 公理类型
         */
        [[maybe_unused]] [[nodiscard]] AxiomType getAxiomType() const;

        /**
         * 公理依据Getter方法
         * @return 公理依据
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getBasis() const;

        /** 公理依据idGetter方法
        * @return 公理依据id
        */
        [[maybe_unused]] [[maybe_unused]] [[nodiscard]] int getBasisId() const;

        /**
         * 设置公理类型
         * @param axiomType 公理类型
         */
        [[maybe_unused]] void setAxiomType(AxiomType axiomType);

        /**
         * 设置公理依据，公理依据只允许从已设定依据中选择
         * @param index 公理依据在对应公理集合中的序号
         */
        [[maybe_unused]] void setBasis(int index);

        /**
         * 添加当前公理下的对应概念
         * @param conceptId 概念ID
         */
        [[maybe_unused]] void addConcept(UniqueID *conceptId);

        /**
         * 获取公理对应实体数量
         * @return
         */
        [[maybe_unused]] int getConceptCount();

        /**
         * 获取公理对应概念集合中的某一概念
         * @param index 概念序号
         * @return
         */
        [[maybe_unused]] UniqueID *getConcept(int index);

        /**
         * 删除公理对应实体集合中的实体
         * @param conceptId 待删除概念id
         */
        [[maybe_unused]] void removeConcept(const UniqueID *concept);

        [[maybe_unused]] [[nodiscard]] UniqueID *getId() const;
    };
}
