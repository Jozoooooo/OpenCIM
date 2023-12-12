/**
@版权 (c) 2023, NanJin Normal University
@文件名 System.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 系统基类的定义，继承自要素基类，是对实体间信息的描述。
@修订历史 2023.7.28 创建
**/

#pragma once

#include "../Core/Element.hpp"

namespace NNU::OpenCIM::System {
    /**
     * 系统类型
     */
    enum SystemType {
        RELATION, // 关系
        EVOLUTION, // 演化
        MECHANISM, // 机制
        UNKNOWNSYS // 未知系统
    };

    /**
     * 系统类，继承自概念类
     */
    class System : public Core::Element {
    protected:
        SystemType _systemType; // 系统类型

        System() : _systemType(UNKNOWNSYS) {}

    public:
        /**
         * 系统类型Getter方法
         * @return 系统类型
         */
        [[nodiscard]] SystemType getSystemType() const {
            return _systemType;
        }

        [[maybe_unused]] UniqueID* getBelongConcept()
        {
            return _belongConcepts[0];
        }

        [[maybe_unused]] void setBelongConcept(UniqueID* uniqueId){
            if(_belongConcepts.empty())
            {
                _belongConcepts.emplace_back(uniqueId);
            }
            else
            {
                _belongConcepts[0] = uniqueId;
            }
        }
    };
}