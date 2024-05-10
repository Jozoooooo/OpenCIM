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
    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM::Component {
    /**
     * 空间系统组件类，继承自组件类
     */
    class SpatialSystem : public Component {
    private:
        std::string _epsg;

        /**
         * 空间系统初始化
         */
        SpatialSystem();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        [[nodiscard]] const std::string &getEpsg() const;

        void setEpsg(const std::string &epsg);
    };
}