/**
@版权 (c) 2023, NanJin Normal University
@文件名 Element.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 要素描述文件，场景的最基础组成，每一要素归属于零至多个概念，受概念对应公理的制约。
@修订历史 2023.7.28 创建
**/

#pragma once

#include <vector>

#include "../Common/Define.hpp"
#include "../Common/UniqueID.hpp"

namespace NNU::OpenCIM::Core {
    /**
     * 场景要素
     */
    class Element {
    protected:
        UniqueID *_id;
        std::vector<UniqueID *> _belongConcepts;

        /**
         * 初始化要素，为要素构建唯一id
         */
        Element() : _id(new UniqueID()) {

        }

    public:
        [[nodiscard]] UniqueID *getId() const {
            return _id;
        }

        /**
         * 重载相等运算符
         * @param rhs 对比的概念
         * @return 是否相等
         */
        bool operator==(const Element &rhs) const {
            return _id == rhs._id;
        }

        /**
         * 重载不相等运算符
         * @param rhs 对比的概念
         * @return 是否不相等
         */
        bool operator!=(const Element &rhs) const {
            return !(rhs == *this);
        }

        [[maybe_unused]] void addBelongConcept(UniqueID *conceptId) {
            _belongConcepts.emplace_back(conceptId);
        }

        [[maybe_unused]] [[nodiscard]] int getBelongConceptsCount() const {
            return static_cast<int>( _belongConcepts.size());
        }

        [[maybe_unused]] [[nodiscard]] UniqueID *getBelongConcept(int index) const {
            return _belongConcepts[index];
        }

        [[maybe_unused]] void removeBelongConcept(const UniqueID *concept) {
            auto it = std::find(_belongConcepts.begin(), _belongConcepts.end(), concept);
            _belongConcepts.erase(it);
        }
    };
}