/**
@版权 (c) 2023, NanJin Normal University
@文件名 SpatialSystem.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 空间系统组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl;
}

namespace NNU::OpenCIM::Component {

    enum CoordinateSystem {
        CGCS2000_3 [[maybe_unused]], // 2000坐标系3度带120中心投影
        GSC_WGS84 [[maybe_unused]], // 84投影坐标
        BEIJIN54_3 [[maybe_unused]], // 北京54坐标系3度带120中心
        XIAN80_3 [[maybe_unused]], // 西安80坐标系3度带120中心
        ALBERS [[maybe_unused]], // 亚洲北部阿尔伯斯等积圆锥投影坐标系
        UNKNOWNCOOR // 未知投影
    };

    /**
     * 空间系统组件类，继承自组件类
     */
    class SpatialSystem : public Component {
    private:
        CoordinateSystem _coordinateSystem; // 空间系统对应标准EPSG
        double _centralMeridian; // 中央经线

        /**
         * 空间系统初始化
         */
        SpatialSystem();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMContentImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        [[maybe_unused]] [[nodiscard]] double getCentralMeridian() const;

        [[maybe_unused]] void setCentralMeridian(double centralMeridian);

        [[maybe_unused]] [[nodiscard]] CoordinateSystem getCoordinateSystem() const;

        [[maybe_unused]] void setCoordinateSystem(CoordinateSystem coordinateSystem);
    };
}