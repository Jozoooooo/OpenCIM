/**
@版权 (c) 2024, NanJin Normal University
@文件名 CIMDataset.cpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 20223.7.28
@文件描述 测试LibCIMModel数据集接口。
@修订历史 2023.7.28 创建
**/

#include "ICIMDataSet.hpp"

using namespace NNU::OpenCIM;

void CIMDateSet() {
    auto cimDateSet = CreateCIMDataSet();
    cimDateSet->fromJson("BasicInfo.CIM");
    cimDateSet->setInstitution("NNU");
    cimDateSet->toJson("test.CIM");
}