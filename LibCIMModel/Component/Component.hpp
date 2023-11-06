/**
@版权 (c) 2023, NanJin Normal University
@文件名 Component.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 组件基类的定义，继承自要素基类，包含组件类型字段，是场景中无状态的要素，描述实体内信息。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "../Core/Element.hpp"

namespace NNU::OpenCIM::Component {
    /**
     * 组件类型
     */
    enum ComponentType {
        SEMANTICS, // 语义
        SPATIALLOCATION, // 空间位置
        SPATIALSYSTEM, // 空间系统
        SPATIALGEOMETRY, // 空间几何
        TEMPORALPOINT, // 时间点
        TEMPORALSYSTEM, // 时间系统
        TEMPORALRANGE, // 时间段
        PROPERTY, // 属性
        UNKNOWCMP // 未知组件
    };

    /**
     * 组件基类，继承自概念基类
     */
    class Component : public Core::Element {
    protected:
        ComponentType _componentType; // 组件类型

        Component() : _componentType(UNKNOWCMP) {};

    public:
        /**
         * 组件类型Getter方法
         * @return 组件类型
         */
        [[nodiscard]] ComponentType getComponentType() const {
            return _componentType;
        }
    };
}
