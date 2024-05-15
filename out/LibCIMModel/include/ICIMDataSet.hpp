/**
@版权 (c) 2024, NanJin Normal University
@文件名 ICIMDataSet.hpp
@作者 南京师范大学
@版本 1.0
@最新修改日期 2024.2.6
@文件描述 CIM数据集接口文件，提供对CIM数据集的增删改查等原子操作
@修订历史 2024.2.6 创建
**/

#pragma once

#define  CIM_MODEL_EXPORTS

#ifdef CIM_MODEL_EXPORTS
#define CIM_MODEL_API __declspec(dllexport)
#else
#define CIM_MODEL_API __declspec(dllimport)
#endif

#include "ICIMSchema.hpp"
#include "ICIMSynthetic.hpp"

namespace NNU::OpenCIM {
    struct ICIMDataSet {
        [[maybe_unused]]  virtual void toJson(const char *jsonPath) = 0; // 输出为json

        [[maybe_unused]]  virtual void fromJson(const char *jsonPath) = 0; // 读取json

        virtual void release() = 0;

        virtual const char *getName() = 0; // 获取CIM模型名称

        virtual void setName(const char *name) = 0; // 设置CIM模型名称

        virtual const char *getAuthor() = 0; // 获取CIM模型作者

        virtual void setAuthor(const char *author) = 0; // 设置CIM模型作者

        virtual const char *getInstitution() = 0; // 获取CIM模型创建单位

        virtual void setInstitution(const char *institution) = 0; // 设置CIM模型创建单位

        virtual const char *getDate() = 0; // 获取CIM模型创建时间

        virtual const char *getVersion() = 0; // 获取CIM模型版本

        virtual void setVersion(const char *version) = 0; // 设置CIM模型版本

        virtual const char *getSchemaPath() = 0; // 获取CIM模型模式层路径

        virtual void setSchemaPath(const char *path) = 0; // 设置CIM模型模式层路径

        virtual const char *getSyntheticPath(int i) = 0; // 获取CIM模型综合表达模型路径

        virtual const char *getSyntheticName(int i) = 0; // 获取CIM模型综合表达模型名称

        virtual void addSyntheticPath(const char *name, const char *path) = 0; // 添加CIM模型综合表达模型

        virtual void removeSyntheticPath(const char *name, const char *path) = 0; // 删除CIM模型综合表达模型

        virtual const char *getExpressionPath() = 0; // 获取CIM模型表达模型路径

        virtual void setExpressionPath(const char *path) = 0; // 设置CIM模型表达模型路径

        virtual const char *getMD5() = 0; // 获取CIM模型MD5

        virtual void setMD5(const char *md5) = 0; // 设置CIM模型版MD5

        virtual int getSyntheticCount()=0;// 获取CIM模型综合表达模型个数

        virtual ICIMSchema* getSchema() = 0; // 获取CIM模型模式层

        virtual ICIMSynthetic* getSynthetic(int i) = 0; // 获取CIM模型综合表达模型
    };

    extern "C" [[maybe_unused]]  CIM_MODEL_API ICIMDataSet *CreateCIMDataSet(); // 创建CIM数据集接口

    extern "C" [[maybe_unused]]  CIM_MODEL_API void DestroyCIMDataSet(ICIMDataSet *icCIMDataSet); // 销毁CIM数据集接口
}