/**
@版权 (c) 2023, NanJin Normal University
@文件名 TemporalRange.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 时间范围组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM::Component {
    /**
     * 时间几何组件类，继承自组件类
     */
    class TemporalRange : public Component {
    private:
        TIMESTAMP _startTime; // 开始时间时间戳
        TIMESTAMP _endTime; // 结束时间时间戳

        /**
         * 时间几何初始化
         */
        TemporalRange();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 开始时间Getter方法
         * @return 开始时间
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getStartTime() const;

        /**
         * 开始时间Setter方法
         * @param startTime 开始时间
         */
        [[maybe_unused]] void setStartTime(const std::string &startTime);

        /**
         * 结束时间Getter方法
         * @return 结束时间
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getEndTime() const;

        /**
         * 结束时间Setter方法
         * @param endTime 结束时间
         */
        [[maybe_unused]] void setEndTime(const std::string &endTime);
    };
}
