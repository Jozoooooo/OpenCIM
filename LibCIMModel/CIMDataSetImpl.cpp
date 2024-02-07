#include <fstream>

#include "CIMDatasetImpl.hpp"
#include "Common/Date.hpp"

#include <nlohmann/json.hpp>

NNU::OpenCIM::CIMDataSetImpl::CIMDataSetImpl() : _date(Common::Date::currentDate()) {

}

void NNU::OpenCIM::CIMDataSetImpl::toJson(const char *jsonPath) {
    nlohmann::json json;

    json["名称"] = _name;
    json["创建人"] = _author;
    json["创建单位"] = _institution;
    json["创建时间"] = _date;
    json["版本"] = _version;
    json["模式信息路径"] = _schemaPath;

    for (int i = 0; i < _syntheticName.size(); i++) {
        nlohmann::json synthetic;
        synthetic["名称"] = _syntheticName[i];
        synthetic["路径"] = _syntheticPath[i];

        json["综合模型路径"].emplace_back(synthetic);
    }

    json["表达模型路径"] = _expressionPath;
    json["MD5"] = _md5;

    std::ofstream file(jsonPath);
    file << json.dump(JSONINDENT);
}

void NNU::OpenCIM::CIMDataSetImpl::fromJson(const char *jsonPath) {
    FILE *fp;
    auto error = fopen_s(&fp, jsonPath, "r");
    if (error) {
        return;
    }
    char buffer[1024 * 8];
    std::string result;
    while (fgets(buffer, 1024 * 8, fp) != nullptr) {
        result.append(buffer);
    }
    fclose(fp);

    nlohmann::json json = nlohmann::json::parse(result);

    _name = json["名称"];
    _author = json["创建人"];
    _institution = json["创建单位"];
    _date = json["创建时间"];
    _version = json["版本"];
    _schemaPath = json["模式信息路径"];
    for (auto synthetic: json["综合模型路径"]) {
        _syntheticName.emplace_back(synthetic["名称"]);
        _syntheticPath.emplace_back(synthetic["路径"]);
    }
    _expressionPath = json["表达模型路径"];
    _md5 = json["MD5"];

    _iCIMSchema = CreateCIMSchema();
    _iCIMSchema->fromJson(_schemaPath.c_str());

    for(const auto & i : _syntheticPath)
    {
        auto temp = CreateCIMSynthetic();
        temp->fromJson(i.c_str());
        _iCIMSynthetic.emplace_back(temp);
    }
}

void NNU::OpenCIM::CIMDataSetImpl::release() {
    delete this;
}

const char *NNU::OpenCIM::CIMDataSetImpl::getName() {
    return _name.c_str();
}

void NNU::OpenCIM::CIMDataSetImpl::setName(const char *name) {
    _name = name;
}

const char *NNU::OpenCIM::CIMDataSetImpl::getAuthor() {
    return _author.c_str();
}

void NNU::OpenCIM::CIMDataSetImpl::setAuthor(const char *author) {
    _author = author;
}

const char *NNU::OpenCIM::CIMDataSetImpl::getInstitution() {
    return _institution.c_str();
}

void NNU::OpenCIM::CIMDataSetImpl::setInstitution(const char *institution) {
    _institution = institution;
}

const char *NNU::OpenCIM::CIMDataSetImpl::getDate() {
    return _date.c_str();
}

const char *NNU::OpenCIM::CIMDataSetImpl::getVersion() {
    return _version.c_str();
}

void NNU::OpenCIM::CIMDataSetImpl::setVersion(const char *version) {
    _version = version;
}

const char *NNU::OpenCIM::CIMDataSetImpl::getSchemaPath() {
    return _schemaPath.c_str();
}

void NNU::OpenCIM::CIMDataSetImpl::setSchemaPath(const char *path) {
    _schemaPath = path;
}

const char *NNU::OpenCIM::CIMDataSetImpl::getSyntheticPath(int i) {
    if (_syntheticPath.size() <= i) {
        return nullptr;
    } else {
        return _syntheticPath[i].c_str();
    }
}

const char *NNU::OpenCIM::CIMDataSetImpl::getSyntheticName(int i) {
    if (_syntheticName.size() <= i) {
        return nullptr;
    } else {
        return _syntheticName[i].c_str();
    }
}

void NNU::OpenCIM::CIMDataSetImpl::addSyntheticPath(const char *name, const char *path) {
    _syntheticPath.emplace_back(path);
    _syntheticName.emplace_back(name);
}

void NNU::OpenCIM::CIMDataSetImpl::removeSyntheticPath(const char *name, const char *path) {
    auto it = std::find(_syntheticName.begin(), _syntheticName.end(), name);
    _syntheticName.erase(it);

    it = std::find(_syntheticPath.begin(), _syntheticPath.end(), path);
    _syntheticPath.erase(it);
}

NNU::OpenCIM::ICIMSchema *NNU::OpenCIM::CIMDataSetImpl::getSchema() {
    return _iCIMSchema;
}

NNU::OpenCIM::ICIMSynthetic *NNU::OpenCIM::CIMDataSetImpl::getSynthetic(int i) {
    if (_iCIMSynthetic.size() <= i) {
        return nullptr;
    } else {
        return _iCIMSynthetic[i];
    }
}

const char *NNU::OpenCIM::CIMDataSetImpl::getMD5() {
    return _md5.c_str();
}

void NNU::OpenCIM::CIMDataSetImpl::setMD5(const char *md5) {
    _md5 = md5;
}

const char *NNU::OpenCIM::CIMDataSetImpl::getExpressionPath() {
    return _expressionPath.c_str();
}

void NNU::OpenCIM::CIMDataSetImpl::setExpressionPath(const char *path) {
    _expressionPath = path;
}
