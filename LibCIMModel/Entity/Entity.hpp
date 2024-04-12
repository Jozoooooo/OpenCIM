/**
@版权 (c) 2023, NanJin Normal University
@文件名 Entity.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 实体描述文件，场景中的主要活动对象，实体本身并不包含任何逻辑或功能，只是一个标识符，实体功能由组件和系统形成。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "../Core/Element.hpp"

namespace NNU::OpenCIM {
    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM::Entity {
    /**
     * 实体类
     */
    class Entity : public Core::Element {
    private:
        std::vector<UniqueID *> _components; // 构成组件集合
        std::string _entityCode;//实体编码
        std::string _entityName;//实体名称

        Entity();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 添加组件
         * @param componentId 组件id
         */
        [[maybe_unused]] void addComponent(UniqueID *component);

        /**
         * 获取实体组件集合中的组件数量
         * @return 组件数量
         */
        [[maybe_unused]] [[nodiscard]] int getComponentsCount() const;

        /**
         * 根据组件序号获取组件
         * @param index 组件序号
         * @return 组件id
         */
        [[maybe_unused]] [[nodiscard]] const UniqueID *getComponent(int index) const;

        /**
         * 根据组件序号删除组件
         * @param componentId 组件id
         */
        [[maybe_unused]] void removeComponent(const UniqueID *component);

        [[maybe_unused]] UniqueID *getBelongConcept();

        [[maybe_unused]] void setBelongConcept(UniqueID *uniqueId);

        [[maybe_unused]] std::string getEntityCode();

        [[maybe_unused]] void setEntityCode(const std::string& entityCode);

        [[maybe_unused]] std::string getEntityName();

        [[maybe_unused]] void setEntityName(const std::string& entityName);
    };
}