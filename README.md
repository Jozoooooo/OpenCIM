# OpenCIM

<img src="https://pic.imgdb.cn/item/64c325591ddac507cc9a5a6e.jpg" style="zoom:50%;"  alt=""/>

[![Static Badge](https://img.shields.io/badge/南师大-地科院-orange)](http://dky.njnu.edu.cn/)
![Static Badge](https://img.shields.io/badge/OpenCIM-LibCIMModel-blue)![Static Badge](https://img.shields.io/badge/OpenCIM-CIMCreator-blue)![Static Badge](https://img.shields.io/badge/OpenCIM-CIMViewer-blue)
![Static Badge](https://img.shields.io/badge/C%2B%2B-v17-green)![Static Badge](https://img.shields.io/badge/CMake-v3.25-green)

本仓库包含以下内容：

- LibCIMModel —— OpenCIM核心库，提供CIM交换格式操作SDK。
- ACIMTest —— OpenCIM创建的简单示例，调用LibCIMModel实现简单场景用例。
- ACIMViewer —— OpenCIM数据集的可视化。

- ACIMCreator —— ACIMCreator 是基于LibCIMModel的基础上，构建CIM数据集的可执行程序。
- SchemaConvert —— 读取指定格式xlsx文件自动生成CIM模式信息的可执行控制台程序。
- Paper —— 场景学主要著作。

## 文件结构

- 3rdlibs 外部库文件
- LibCIMModel、ACIMCreator、ACIMViewer、ACIMTest、SchemaConvert
- out 编译输出文件

## 安装

无需安装，采用CMake编译运行

## LibCIMModel

！！LibCIMModel进行了多次更新，最新接口请看源码，接口标准请查阅《城市信息模型数据交换格式标准》。

### 背景

LibCIMModel用于构建场景数据模型。

场景数据模型由以下组成部分：

- 公理
- 概念
- 外联数据
- 组件
- 实体
- 系统

场景数据模型的设计思想如下：

世界可以认为是一个个【场景】构成，场景可以互相嵌套。

场景是由一系列的【实体】所组成。实体是有明确内涵与外延的概念。实体包括了时间、地点、人物、事物、时间、现象。

实体由可以复用的组件所描述，这些组件包含了语义、位置、几何、时间、属性。比较简单的组件直接在场景文件中描述，比较复杂的可以通过外联数据的方式描述。

实体间由系统描述，这些系统包括关系、演化与作用机制。

其中【组件】、【实体】、【系统】为场景模型的主要构成要素，统一继承自【要素】。

每一【要素】会归属于零至多个【概念】，【概念】间采用【公理】进行逻辑约束。

### 库依赖

LibCIMModel对JSON文件的读写依赖于nlohmann库。

### 库功能

- 创建、读取、查询、修改、保存CIMSchema
- 创建、读取、查询、修改、保存CIMSynthetic

### 使用说明

1. 编译LibCIMModel
2. 引入LibCIMModel头文件、静态链接库
3. 通过CreateCIMSchema、CreateCIMSynthetic创建场景操作接口
4. 通过场景接口实现场景功能

### 保存格式

采用JSON格式进行保存，JSON中为场景中各类型对象的列表，每一列表中储存着该类型下的所有对象，每一对象的JSON结构与逻辑结构一致。

![](https://pic.imgdb.cn/item/64c23f591ddac507cc386dea.jpg)

公理JSON结构示例

![](https://pic.imgdb.cn/item/64c2450f1ddac507cc44e24e.jpg)

概念JSON结构示例

### 更新记录

|    更新时间    | 更新类型 |                 更新内容                 |
|:----------:|:----:|:------------------------------------:|
| 2023.7.17  |  修改  |       场景头字段<br />场景头字段创建、查询接口        |
| 2023.7.17  |  新增  |            用于描述场景信息的场景头类             |
| 2023.7.17  |  修改  |          在【属性】中增加对“材质”描述的能力          |
| 2023.7.17  |  修改  | 将【时间位置】更名为【时间点】<br />将【时间几何】更名为【时间段】 |
| 2023.7.18  |  修改  |    “fromJson”函数实现代码<br />要素删除实现代码    |
| 2023.7.18  |  修改  |      外部场景模型字段<br />外部场景模型字段查询接口      |
| 2023.7.18  |  修改  |             【机制】热拔插实现代码              |
| 2023.7.21  |  修改  |            将SetUv更名为SetUV            |
| 2023.7.21  |  修改  |     将IMechanismPlugin更名为IPlugin      |
| 2023.7.21  |  修改  |       将CIMHeader.hpp/cpp移动至根目录       |
| 2023.7.21  |  新增  |                用于描述材质                |
| 2023.7.21  |  修改  |        材质字段<br />材质字段创建、查询接口         |
| 2023.7.21  |  修改  |            删除【属性】中的“材质”描述            |
| 2023.7.22  |  修改  | 将Property作为基类，派生出内部属性类和外部数据线类（纹理材质）  |
| 2023.7.22  |  修改  |           在Element添加“注解”字段           |
| 2023.7.22  |  修改  |    添加“Meta”类型，场景间相互调用采用Meta类型进行调用    |
| 2023.7.22  |  新增  |           getMeta函数实现获取元数据           |
| 2023.7.22  |  修改  |              将场景和场景标准拆分              |
| 2023.7.24  |  修改  |               整体结构进行微调               |
|  2023.8.1  |  新增  |           新增根据注释查询场景要素的接口            |
| 2023.12.15 |  新增  |               新增编码修改接口               |
| 2023.12.15 |  新增  |              概念新增概念类型字段              |
| 2023.12.15 |  修改  |           实体、组件、系统概念映射接口调整           |
|  2024.2.6  |  修改  |            接口名称与现有标准保持一致             |
|  2024.2.6  |  新增  |         CIM数据集接口，用于读写.CIM文件          |
|  2024.2.6  |  修复  |    LibCIMModel setAreaNumber导致的错误    |
| 2024.2.27  |  修改  |             空间系统改为EPSG描述             |

## ACIMCreator

* ACIMCreator 是基于LibCIMModel的基础上，采用GUI构建CIM数据集的可执行程序。
* 将会在后续上线。

## ACIMTest

### 背景

### 库依赖

* ACIMTest 依赖于LibCIMModel库。

### 程序功能

程序中共有四个个示例函数：CIMSchema、CIMSynthetic、CIMDataSet、TestPlugin，分别用于测试模式层、ACIM综合模型、CIM数据集、ACIM插件接口。

### 快速开始

将CMakeList对应位置修改为如下形式，编译程序即可。

```cmake
#add_executable(ACIMCreator CIMSchema.cpp Mechanism/TestPlugin.cpp main.cpp NNU-ACIM.cpp)
add_library(ACIMCreator SHARED Mechanism/Plugin/HelloMechanism.cpp)
```

将CMakeList对应位置修改为如下形式。

```cmake
add_executable(ACIMCreator CIMSchema.cpp Mechanism/TestPlugin.cpp main.cpp NNU-ACIM.cpp)
# add_library(ACIMCreator SHARED Mechanism/Plugin/HelloMechanism.cpp)
```

在main.cpp文件中选择想要运行的函数。

```c++
int main() {
    CIMSchema();
    CIMSynthetic();
    CIMDataSet();
}
```

### 更新记录

|   更新时间    | 更新类型 |        更新内容         |
|:---------:|:----:|:-------------------:|
| 2023.7.17 |  修改  |       调整文件结构        |
| 2023.7.17 |  新增  | CIM1层级【公理】-【概念】标准示例 |
| 2023.7.17 |  新增  |     【材质】【纹理】示例      |
| 2023.7.18 |  新增  |       【机制】示例        |
| 2024.2.6  |  新增  |     CIM数据集构建示例      |

## ACIMViewer

* #### 注：2024年1月5日版本后的数据集无法查看，最新ACIM Viewer正在开发中，会在近期上线。

## SchemaConvert

### 功能

本程序为读取指定格式xlsx文件自动生成CIM模式信息的可执行控制台程序。

### 依赖库

- LibCIMModel
- xlnt

### 快速上手

1. 打开控制台。
2. 定位至程序路径。
3. 参数：程序名 xlsx路径 输出模式信息json路径【缺省】。

### xlsx格式

- 必须包含名为“分类表”和“颗粒表”的sheet。

- 可以包含名为“属性表”和“关系表”的sheet。

- 表单第一列为父概念名。

- 表单第二列为分类/颗粒依据。

- 表单第三列为子概念名。

- 表单第四列为叶子概念CIM编码。

- 示例：

  | FJGN       | GLYJ             | ZJGN           | BM     |
  | ---------- | ---------------- | -------------- | ------ |
  | 行政区     | 行政区的分类     | CIM1行政区     |        |
  | CIM1行政区 | CIM1行政区的分类 | CIM1国家       | 601000 |
  | CIM1行政区 | CIM1行政区的分类 | CIM1省级行政区 |        |

### 注

- 输出模式信息json路径可以缺省，缺省值为当前程序路径，自动生成result.json。
- 可以直接将xlsx文件拖拽至可执行程序上，便捷运行。
