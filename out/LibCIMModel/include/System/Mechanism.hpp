/**
@版权 (c) 2023, NanJin Normal University
@文件名 Mechanism.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 机制系统的定义，继承自系统基类，是场景学信息七要素之一。机制系统作用于整个场景，实现整个场景从标准到内容的运算推演。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "../Common/IPlugin.hpp"
#include "System.hpp"

namespace NNU::OpenCIM {
    class CIMSyntheticImpl;
}

namespace NNU::OpenCIM::System {
    /**
     * 机制类，继承自系统类
     */
    class Mechanism : public System {
    private:
        std::string _mechanismName;
        std::string _mechanismComments;
        int _mechanismVersion;
        std::string _mechanismPath;

        Mechanism();

        void fromJson(const JSONSTR &jsonStr);

        friend class NNU::OpenCIM::CIMSyntheticImpl;

    public:
        IPlugin *plugin;

        /**
         * 生成数据对应json
         * @return json
         */
        [[nodiscard]] JSONSTR toJson() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getMechanismPath() const;

        [[maybe_unused]] void setMechanismPath(const std::string &mechanismPath);

        [[maybe_unused]] [[nodiscard]] const std::string &getMechanismName() const;

        [[maybe_unused]] void setMechanismName(const std::string &mechanismName);

        [[maybe_unused]] [[nodiscard]] const std::string &getMechanismComments() const;

        [[maybe_unused]] void setMechanismComments(const std::string &mechanismComments);

        [[maybe_unused]] [[nodiscard]] int getMechanismVersion() const;

        [[maybe_unused]] void setMechanismVersion(int mechanismVersion);

        [[maybe_unused]] [[nodiscard]] IPlugin *getMechanismPlugin() const;

        [[maybe_unused]] void load();

        [[maybe_unused]] void getMechanismMeta();
    };
}