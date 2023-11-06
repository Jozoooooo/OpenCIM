#ifdef _WIN32

#include <windows.h> // Windows特定头文件

#else
#include <dlfcn.h>   // Linux和macOS特定头文件
#endif

#include <iostream>

#include <nlohmann/json.hpp>

#include "Mechanism.hpp"

NNU::OpenCIM::System::Mechanism::Mechanism() : _mechanismVersion(0), plugin(nullptr) {
    _systemType = SystemType::MECHANISM;
}

JSONSTR NNU::OpenCIM::System::Mechanism::toJson() const {
    nlohmann::json json;

    json["Id"] = nlohmann::json::parse(_id->toJson());
    json["SystemType"] = _systemType;
    json["MechanismName"] = _mechanismName;
    json["MechanismPath"] = _mechanismPath;
    json["MechanismVersion"] = _mechanismVersion;

    return json.dump();
}


void NNU::OpenCIM::System::Mechanism::fromJson(const std::string &jsonStr) {
    nlohmann::json json = nlohmann::json::parse(jsonStr);

    _id = new UniqueID(json["Id"].dump());
    _systemType = json["SystemType"];
    _mechanismName = json["MechanismName"];
    _mechanismPath = json["MechanismPath"];
    _mechanismVersion = json["MechanismVersion"];

    for (const auto &belongConcept: json["BelongConcepts"]) {
        auto uid = new UniqueID(belongConcept.dump());
        _belongConcepts.emplace_back(uid);
    }
}

[[maybe_unused]] const std::string &NNU::OpenCIM::System::Mechanism::getMechanismPath() const {
    return _mechanismPath;
}

[[maybe_unused]] void NNU::OpenCIM::System::Mechanism::setMechanismPath(const std::string &mechanismPath) {
    _mechanismPath = mechanismPath;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::System::Mechanism::getMechanismName() const {
    return _mechanismName;
}

[[maybe_unused]] void NNU::OpenCIM::System::Mechanism::setMechanismName(const std::string &mechanismName) {
    _mechanismName = mechanismName;
}

[[maybe_unused]] const std::string &NNU::OpenCIM::System::Mechanism::getMechanismComments() const {
    return _mechanismComments;
}

[[maybe_unused]] void NNU::OpenCIM::System::Mechanism::setMechanismComments(const std::string &mechanismComments) {
    _mechanismComments = mechanismComments;
}

[[maybe_unused]] int NNU::OpenCIM::System::Mechanism::getMechanismVersion() const {
    return _mechanismVersion;
}

[[maybe_unused]] void NNU::OpenCIM::System::Mechanism::setMechanismVersion(int mechanismVersion) {
    _mechanismVersion = mechanismVersion;
}

[[maybe_unused]] IPlugin *NNU::OpenCIM::System::Mechanism::getMechanismPlugin() const {
    return plugin;
}

[[maybe_unused]] void NNU::OpenCIM::System::Mechanism::load() {
    if (_mechanismPath.empty()) {
        std::cerr << "Failed to find mechanism." << std::endl;
        return;
    }

#ifdef _WIN32
    HINSTANCE MechanismHandle = LoadLibrary(_mechanismPath.c_str());
#else
    void* MechanismHandle = dlopen("_mechanismPath.c_str()", RTLD_LAZY);
#endif

    if (!MechanismHandle) {
        std::cerr << "Failed to load mechanism." << std::endl;
        return;
    }

    typedef IPlugin *(*CreateMechanismFunc)();

#ifdef _WIN32
    auto createMechanism = reinterpret_cast<CreateMechanismFunc>(GetProcAddress(MechanismHandle, "CreateMechanism"));
#else
    auto createMechanism = reinterpret_cast<CreateMechanismFunc>(dlsym(MechanismHandle, "CreateMechanism"));
#endif

    if (!createMechanism) {
        std::cerr << "Failed to get \"CreateMechanism\" pointers from the mechanism." << std::endl;

#ifdef _WIN32
        FreeLibrary(MechanismHandle);
#else
        dlclose(MechanismHandle);
#endif

        return;
    }

    // 创建插件对象并运行
    plugin = createMechanism();
}

[[maybe_unused]] void NNU::OpenCIM::System::Mechanism::getMechanismMeta() {
    if (plugin == nullptr) {
        std::cerr << "mechanism is null." << std::endl;
        return;
    }

    _mechanismName = plugin->getName();
    _mechanismComments = plugin->getComments();
    _mechanismVersion = plugin->getVersion();
}
