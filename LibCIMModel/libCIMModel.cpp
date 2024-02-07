/**
@版权 (c) 2023, NanJin Normal University
@文件名 libCIMModel.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 场景数据模型核心库入口
@修订历史 2023.7.28 创建
 2024.2.6 修改名称
**/
#include "CIMSchemaImpl.hpp"
#include "CIMSyntheticImpl.hpp"
#include "CIMDatasetImpl.hpp"

[[maybe_unused]] NNU::OpenCIM::ICIMSchema *NNU::OpenCIM::CreateCIMSchema() {
    return new CIMSchemaImpl();
}

[[maybe_unused]]  void NNU::OpenCIM::DestroyCIMSchema(ICIMSchema *iCIMSchema) {
    iCIMSchema->release();
}

[[maybe_unused]] NNU::OpenCIM::ICIMSynthetic *NNU::OpenCIM::CreateCIMSynthetic() {
    return new CIMSyntheticImpl();
}

[[maybe_unused]]  void NNU::OpenCIM::DestroyCIMSynthetic(ICIMSynthetic *iCIMSynthetic) {
    iCIMSynthetic->release();
}

[[maybe_unused]] NNU::OpenCIM::ICIMDataSet *NNU::OpenCIM::CreateCIMDataSet() {
    return new CIMDataSetImpl();
}

[[maybe_unused]]  void NNU::OpenCIM::DestroyCIMDataSet(NNU::OpenCIM::ICIMDataSet *iCIMDateSet) {
    iCIMDateSet->release();
}
