#ifdef _WIN32

#include <objbase.h>

#elif defined(__linux__)
#include <uuid/uuid.h>
#endif

#include <nlohmann/json.hpp>

#include "UniqueID.hpp"

UniqueID::UniqueID(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _comments = json["Comments"];
    _code = json["Code"];
}

JSONSTR UniqueID::toJson() const {
    nlohmann::json json;

    json["Code"] = _code;
    json["Comments"] = _comments;

    return json.dump();
}

UniqueID::UniqueID() {
#ifdef _WIN32
    GUID winGuid;
    CoCreateGuid(&winGuid);
    char guidStr[39];
    sprintf_s(guidStr, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
              winGuid.Data1, winGuid.Data2, winGuid.Data3,
              winGuid.Data4[0], winGuid.Data4[1], winGuid.Data4[2], winGuid.Data4[3],
              winGuid.Data4[4], winGuid.Data4[5], winGuid.Data4[6], winGuid.Data4[7]);
    _code = guidStr;
#elif defined(__linux__)
    uuid_t linuxGuid;
    uuid_generate_random(linuxGuid);
    char guidStr[37];
    uuid_unparse(linuxGuid, guidStr);
    _code = guidStr;
#endif
}

[[maybe_unused]] const std::string &UniqueID::getComments() const {
    return _comments;
}

[[maybe_unused]] void UniqueID::setComments(const std::string &comments) {
    UniqueID::_comments = comments;
}

const std::string &UniqueID::getCode() const {
    return _code;
}

std::string UniqueID::getCCode() const {
    return _cCode;
}

[[maybe_unused]] void UniqueID::setCCode(const std::string &cCode) {
    UniqueID::_cCode = cCode;
}

void UniqueID::setCode(const std::string &code) {
    _code = code;
}

