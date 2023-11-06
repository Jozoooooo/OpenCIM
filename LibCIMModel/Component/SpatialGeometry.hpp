/**
@版权 (c) 2023, NanJin Normal University
@文件名 SpatialGeometry.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 空间几何组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl;
}

namespace NNU::OpenCIM::Component {
    /**
     * 空间几何类型
     */
    enum SpatialGeometryType {
        WKT [[maybe_unused]], // 内嵌式WKT
        BREP [[maybe_unused]], // 边界表示法 表示格式："0,0,0;0,1,0;1,1,1"
        EXTERNALGEO [[maybe_unused]], // 外链式
        UNKNOWNGEO // 未知几何
    };

    /**
     * 空间几何组件类，继承自组件类
     */
    class SpatialGeometry : public Component {
    private:
        SpatialGeometryType _spatialGeometryType; // 空间几何类型
        std::string _geometry; // 空间几何描述，如果几何类型为外链式，则填写外部数据id
        std::string _uv; // 几何材质uv 表示格式"0,0;0,1"

        /**
         * 空间几何初始化
         */
        SpatialGeometry();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMContentImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 空间几何类型Getter方法
         * @return 空间几何类型
         */
        [[maybe_unused]] [[nodiscard]] SpatialGeometryType getSpatialGeometryType() const;

        /**
         * 空间几何类型Setter方法
         * @param spatialGeometryType 空间几何类型
         */
        [[maybe_unused]] void setSpatialGeometryType(SpatialGeometryType spatialGeometryType);

        /**
         * 空间几何描述Getter方法
         * @return 空间几何描述
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getGeometry() const;

        /**
         * 空间几何描述Setter方法
         * @param geometry 空间几何描述
         */
        [[maybe_unused]] void setGeometry(const std::string &geometry);

        [[maybe_unused]] [[nodiscard]] const std::string &getUV() const;

        [[maybe_unused]] void setUV(const std::string &uv);
    };
}
