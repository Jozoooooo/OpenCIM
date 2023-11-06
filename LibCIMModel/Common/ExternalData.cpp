#include <nlohmann/json.hpp>

#include "ExternalData.hpp"

NNU::OpenCIM::Common::ExternalData::ExternalData() : _id(new UniqueID()),
                                                       _dataFormat(UNKNOWNDAT) {
}

JSONSTR NNU::OpenCIM::Common::ExternalData::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["DataFormat"] = _dataFormat;
    json["OuterUrl"] = _outerUrl;
    json["InnerUrl"] = _innerUrl;

    return json.dump();
}

void NNU::OpenCIM::Common::ExternalData::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _dataFormat = json["DataFormat"];
    _outerUrl = json["OuterUrl"];
    _innerUrl = json["InnerUrl"];
}

[[maybe_unused]] UniqueID *NNU::OpenCIM::Common::ExternalData::getId() const {
    return _id;
}

[[maybe_unused]] NNU::OpenCIM::Common::DataFormat NNU::OpenCIM::Common::ExternalData::getDataFormat() const {
    return _dataFormat;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Common::ExternalData::getOuterUrl() const {
    return _outerUrl;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::Common::ExternalData::getInnerUrl() const {
    return _innerUrl;
}

[[maybe_unused]] void
NNU::OpenCIM::Common::ExternalData::setDataFormat(NNU::OpenCIM::Common::DataFormat dataFormat) {
    ExternalData::_dataFormat = dataFormat;
}

[[maybe_unused]] void NNU::OpenCIM::Common::ExternalData::setOuterUrl(const std::string &outerUrl) {
    ExternalData::_outerUrl = outerUrl;
}

[[maybe_unused]] void NNU::OpenCIM::Common::ExternalData::setInnerUrl(const std::string &innerUrl) {
    ExternalData::_innerUrl = innerUrl;
}

bool NNU::OpenCIM::Common::ExternalData::operator==(const NNU::OpenCIM::Common::ExternalData &rhs) const {
    return _id == rhs._id;
}

bool NNU::OpenCIM::Common::ExternalData::operator!=(const NNU::OpenCIM::Common::ExternalData &rhs) const {
    return !(rhs == *this);
}
