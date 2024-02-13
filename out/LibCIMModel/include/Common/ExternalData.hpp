/**
@版权 (c) 2023, NanJin Normal University
@文件名 ExternalData.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景中所使用的外联数据格式定义。
@修订历史 2023.7.28 创建
**/

#pragma once

#include <string>

#include "UniqueID.hpp"
#include "Define.hpp"

namespace NNU::OpenCIM {
    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM::Common {
    /**
     * 支持的外部数据格式
     */
    enum DataFormat {
        OBJ [[maybe_unused]],
        IFC [[maybe_unused]],
        EXCEL [[maybe_unused]],
        JSON [[maybe_unused]],
        TXT [[maybe_unused]],
        PNG [[maybe_unused]],
        JPG [[maybe_unused]],
        SHP [[maybe_unused]],
        TIF [[maybe_unused]],
        LAS [[maybe_unused]],
        OSGB [[maybe_unused]],
        UNKNOWNDAT [[maybe_unused]]
    };

    /**
     * 外联数据
     */
    class ExternalData {
    private:
        UniqueID *_id; // 外部数据唯一标识
        DataFormat _dataFormat; // 数据格式
        std::string _outerUrl; // 数据在硬盘中储存位置
        std::string _innerUrl; // 数据在外部数据内部位置

        ExternalData();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        [[nodiscard]] JSONSTR toJson() const;

        /**
         * 外部数据唯一标识Getter方法
         * @return 外部数据id
         */
        [[maybe_unused]] [[nodiscard]] UniqueID *getId() const;

        /**
         * 数据格式Getter方法
         * @return 数据格式
         */
        [[maybe_unused]] [[nodiscard]] DataFormat getDataFormat() const;

        /**
         * 外部地址Getter方法
         * @return 外部地址
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getOuterUrl() const;

        /**
         * 内部地址Getter方法
         * @return 内部地址
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getInnerUrl() const;

        /**
         * 数据格式Setter方法
         * @param dataFormat 数据格式
         */
        [[maybe_unused]] void setDataFormat(DataFormat dataFormat);

        /**
         * 外部地址Setter方法
         * @param outerUrl 外部地址
         */
        [[maybe_unused]] void setOuterUrl(const std::string &outerUrl);

        /**
         * 内部地址Setter方法
         * @param innerUrl 内部地址
         */
        [[maybe_unused]] void setInnerUrl(const std::string &innerUrl);

        /**
         * 重载相等运算符
         * @param rhs 对比的外部数据
         * @return 是否相等
         */
        bool operator==(const ExternalData &rhs) const;

        /**
         * 重载不相等运算符
         * @param rhs 对比的外部数据
         * @return 是否不相等
         */
        bool operator!=(const ExternalData &rhs) const;
    };
}