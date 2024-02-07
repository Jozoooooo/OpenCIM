/**
@版权 (c) 2023, NanJin Normal University
@文件名 TemporalPoint.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 时间点组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM::Component {
    /**
     * 时间位置组件类，继承自组件类
     */
    class TemporalPoint : public Component {
    private:
        TIMESTAMP _timeStamp; // 时间戳
        /**
         * 时间位置初始化
         */
        TemporalPoint();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 时间位置Getter方法
         * @return 时间戳
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getTimeStamp() const;

        /**
         * 时间位置Setter方法
         * @param timeStamp 时间戳
         */
        [[maybe_unused]] void setTimeStamp(const std::string &timeStamp);
    };
}