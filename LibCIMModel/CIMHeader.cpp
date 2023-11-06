#include "nlohmann/json.hpp"

#include "CIMHeader.hpp"
#include "Common/Date.hpp"

NNU::OpenCIM::CIMHeader::CIMHeader() : _CIMType(UNKNOWNSCE), _CIMDate(Common::Date::currentDate()) {

}

JSONSTR NNU::OpenCIM::CIMHeader::toJson() const {
    nlohmann::json json;

    json["CIMName"] = _CIMName;
    json["CIMType"] = _CIMType;
    json["CIMDate"] = _CIMDate;
    json["CIMDescription"] = _CIMDescription;

    for (const auto &include: _includes) {
        nlohmann::json includeJson;

        includeJson["type"] = include.CIMType;
        includeJson["path"] = include.CIMPath;

        json["includes"].emplace_back(includeJson);
    }
    return json.dump();
}

void NNU::OpenCIM::CIMHeader::fromJson(const JSONSTR &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _CIMName = json["CIMName"];
    _CIMType = json["CIMType"];
    _CIMDate = json["CIMDate"];
    _CIMDescription = json["CIMDescription"];

    for (auto include: json["includes"]) {
        auto meta = Include{include["type"], include["path"]};
        _includes.emplace_back(meta);
    }
}

[[maybe_unused]] const std::string &NNU::OpenCIM::CIMHeader::getCIMName() const {
    return _CIMName;
}

[[maybe_unused]] void NNU::OpenCIM::CIMHeader::setCIMName(const std::string &CIMName) {
    _CIMName = CIMName;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::CIMHeader::getCIMDate() const {
    return _CIMDate;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::CIMHeader::getCIMDescription() const {
    return _CIMDescription;
}

[[maybe_unused]] void NNU::OpenCIM::CIMHeader::setCIMDescription(const std::string &CIMDescription) {
    _CIMDescription = CIMDescription;
}

[[maybe_unused]] int NNU::OpenCIM::CIMHeader::getIncludeCount() const {
    return static_cast<int>(_includes.size());
}

[[maybe_unused]] const NNU::OpenCIM::Include &NNU::OpenCIM::CIMHeader::getInclude(int index) const {
    return _includes[index];
}

[[maybe_unused]] void NNU::OpenCIM::CIMHeader::addInclude(const Include &include) {
    _includes.emplace_back(include);
}

[[maybe_unused]] void NNU::OpenCIM::CIMHeader::removeInclude(const Include &include) {
    auto it = std::find(_includes.begin(), _includes.end(), include);
    _includes.erase(it);
}

[[maybe_unused]] NNU::OpenCIM::CIMType NNU::OpenCIM::CIMHeader::getCIMType() const {
    return _CIMType;
}

