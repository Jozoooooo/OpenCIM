/**
@版权 (c) 2023, NanJin Normal University
@文件名 TemporalSystem.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 时间系统组件的定义，继承自组件基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "Component.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl;
}

namespace NNU::OpenCIM::Component {
    /**
     * 时间系统类型
     */
    enum TemporalSystemType {
        UTC [[maybe_unused]], // 世界标准时间
        BEIJIN [[maybe_unused]], // 北京时区时间
        CUSTOM [[maybe_unused]], // 自定义时间系统
        UNKNOWNTES [[maybe_unused]]
    };

    /**
     * 时间系统组件类，继承自组件类
     */
    class TemporalSystem : public Component {
    private:
        std::string _temporalSystemName; // 时间系统名
        TemporalSystemType _temporalSystemType; // 时间系统类型
        std::string _relativeTemporalSystem; // 相对时间系统id
        TIMESTAMP _trans; // 与相对时间系统的转换（时间戳）

        /**
         * 时间系统初始化
         */
        TemporalSystem();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMContentImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 时间系统名Getter方法
         * @return 时间系统名
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getTemporalSystemName() const;

        /**
         * 时间系统名Setter方法
         * @param temporalSystemName 时间系统名
         */
        [[maybe_unused]] void setTemporalSystemName(const std::string &temporalSystemName);

        /**
         * 时间系统类型Getter方法
         * @return 时间系统类型
         */
        [[maybe_unused]] [[nodiscard]] TemporalSystemType getTemporalSystemType() const;

        /**
         * 时间系统类型Setter方法
         * @param temporalSystemType 时间系统类型
         */
        [[maybe_unused]] void setTemporalSystemType(TemporalSystemType temporalSystemType);

        /**
         * 相对时间系统Getter方法
         * @return 相对时间系统id
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getRelativeTemporalSystem() const;

        /**
         * 相对时间系统Setter方法
         * @param relativeTemporalSystem 相对时间系统id
         */
        [[maybe_unused]] void setRelativeTemporalSystem(const std::string &relativeTemporalSystem);

        /**
         * 与相对时间系统转换参数Getter方法
         * @return 与相对时间系统转换参数
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getTrans() const;

        /**
         * 与相对时间系统转换参数Setter方法
         * @param trans 与相对时间系统转换参数
         */
        [[maybe_unused]] void setTrans(const std::string &trans);
    };
}
