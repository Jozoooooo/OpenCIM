/**
@版权 (c) 2023, NanJin Normal University
@文件名 libCIMModel.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景数据模型核心库入口
@修订历史 2023.7.28 创建
**/
#include "CIMStandardImpl.hpp"
#include "CIMContentImpl.hpp"

[[maybe_unused]] NNU::OpenCIM::ICIMStandard *NNU::OpenCIM::CreateCIMStandard() {
    return new CIMStandardImpl();
}

[[maybe_unused]]  void NNU::OpenCIM::DestroyCIMStandard(ICIMStandard *iCIMStandard) {
    iCIMStandard->release();
}

[[maybe_unused]] NNU::OpenCIM::ICIMContent *NNU::OpenCIM::CreateCIMContent() {
    return new CIMContentImpl();
}

[[maybe_unused]]  void NNU::OpenCIM::DestroyCIMContent(ICIMContent *iCIMContent) {
    iCIMContent->release();
}
