/**
@版权 (c) 2023, NanJin Normal University
@文件名 UniqueID.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 唯一身份标识，用于对场景做所有对象进行标识，采用编码+注释的方式进行标识。
@修订历史 2023.7.28 创建
**/

#pragma once

#include <string>

#include "Define.hpp"

struct UniqueID {
private:
    std::string _code;
    std::string _comments;

public:
    explicit UniqueID();

    explicit UniqueID(const std::string &jsonStr);

    void setCode(const std::string &code);

    [[nodiscard]] const std::string &getCode() const;

    [[maybe_unused]] [[nodiscard]] const std::string &getComments() const;

    [[maybe_unused]] void setComments(const std::string &comments);

    bool operator==(UniqueID *rhs) const {
        return _code == rhs->getCode();
    }

    bool operator!=(UniqueID *rhs) const {
        return rhs != this;
    }

    [[nodiscard]] JSONSTR toJson() const;
};