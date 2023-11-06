/**
@版权 (c) 2023, NanJin Normal University
@文件名 Evolution.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 演化系统的定义，继承自系统基类，是场景学信息七要素之一。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "System.hpp"

namespace NNU::OpenCIM {
    class CIMContentImpl;
}

namespace NNU::OpenCIM::System {
    /**
     * 演化类，集成自系统类
     */
    class Evolution : public System {
    private:
        UniqueID *_fromEntity; // 开始实体
        UniqueID *_toEntity; // 结束实体

        /**
         * 演化初始化
         */
        Evolution();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMContentImpl;

    public:
        /**
         * 生成数据对应json
         * @return json
         */
        [[maybe_unused]] [[nodiscard]] JSONSTR toJson() const;

        /**
         * 开始实体Getter方法
         * @return 开始实体
         */
        [[maybe_unused]]  [[nodiscard]] UniqueID *getFromEntity() const;

        /**
         * 开始实体Setter方法
         * @param fromEntity 开始实体
         */
        [[maybe_unused]] void setFromEntity(UniqueID *fromEntity);

        /**
         * 结束实体Getter方法
         * @return 结束实体
         */
        [[maybe_unused]] [[nodiscard]] UniqueID *getToEntity() const;

        /**
         * 结束实体Setter方法
         * @param toEntity 结束实体
         */
        [[maybe_unused]] void setToEntity(UniqueID *toEntity);
    };
}
