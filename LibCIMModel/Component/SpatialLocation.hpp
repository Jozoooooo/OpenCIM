/**
@版权 (c) 2023, NanJin Normal University
@文件名 SpatialLocation.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 空间位置组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl;
}

namespace NNU::OpenCIM::Component {
    /**
     * 空间位置组件类，继承自组件类
     */
    class SpatialLocation : public Component {
    private:
        double _panX; // x平移距离
        double _panY; // y平移距离
        double _panZ; // z平移距离
        double _rotateX; // x旋转角度
        double _rotateY; // y旋转角度
        double _rotateZ; // z旋转角度
        double _scale; // 模型缩放

        /**
         * 空间位置初始化，默认为不变换
         */
        SpatialLocation();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMContentImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        [[maybe_unused]] [[nodiscard]] double getPanX() const;

        [[maybe_unused]] void setPanX(double panX);

        [[maybe_unused]] [[nodiscard]] double getPanY() const;

        [[maybe_unused]] void setPanY(double panY);

        [[maybe_unused]] [[nodiscard]] double getPanZ() const;

        [[maybe_unused]] void setPanZ(double panZ);

        [[maybe_unused]] [[nodiscard]] double getRotateX() const;

        [[maybe_unused]] void setRotateX(double rotateX);

        [[maybe_unused]] [[nodiscard]] double getRotateY() const;

        [[maybe_unused]] void setRotateY(double rotateY);

        [[maybe_unused]] [[nodiscard]] double getRotateZ() const;

        [[maybe_unused]] void setRotateZ(double rotateZ);

        [[maybe_unused]] [[nodiscard]] double getScale() const;

        [[maybe_unused]] void setScale(double scale);
    };
}
