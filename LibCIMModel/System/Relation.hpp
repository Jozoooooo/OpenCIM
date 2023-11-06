/**
@版权 (c) 2023, NanJin Normal University
@文件名 Relation.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 关系系统的定义，继承自系统基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "System.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl;
}

namespace NNU::OpenCIM::System {
    /**
     * 关系类，继承自系统类
     */
    class Relation : public System {
    private:
        std::string _description; // 关系描述，例："{F1}与{T1}为同学关系"
        std::vector<UniqueID *> _fromEntities; // 关系出发实体集合
        std::vector<UniqueID *> _toEntities; // 关系指向实体几何

        /**
         * 关系初始化
         */
        Relation();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMContentImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[maybe_unused]] [[nodiscard]] JSONSTR toJson() const;

        /**
         * 关系描述Getter方法
         * @return 关系描述
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getDescription() const;

        /**
         * 关系描述Setter方法
         * @param description 关系描述
         */
        [[maybe_unused]] void setDescription(const std::string &description);

        /**
         * 添加出发实体
         * @param entity 出发实体id
         */
        [[maybe_unused]] void addFromEntity(UniqueID *entityId);

        /**
         * 获取出发实体几何中实体数量
         * @return 出发实体数量
         */
        [[maybe_unused]] [[nodiscard]] int getFromEntitiesCount() const;

        /**
         * 根据出发实体序号，获取出发实体Id
         * @param index 出发实体序号
         * @return 出发实体id
         */
        [[maybe_unused]]  [[nodiscard]] UniqueID *getFromEntity(int index) const;

        /**
         * 删除出发实体
         * @param entity 出发实体
         */
        [[maybe_unused]] void removeFromEntity(UniqueID *entity);

        /**
         * 添加指向实体
         * @param entity 指向实体id
         */
        [[maybe_unused]] void addToEntity(UniqueID *entity);

        /**
         * 添加指向实体几何中指向实体数量
         * @return 指向实体数量
         */
        [[maybe_unused]]  [[nodiscard]] int getToEntitiesCount() const;

        /**
         * 根据指向实体序号，获取指向实体id
         * @param index 指向实体序号
         * @return 指向实体id
         */
        [[maybe_unused]] [[nodiscard]] UniqueID *getToEntity(int index) const;

        /**
         * 删除指向实体
         * @param entity 指向实体
         */
        [[maybe_unused]] void removeToEntity(UniqueID *entity);
    };
}
