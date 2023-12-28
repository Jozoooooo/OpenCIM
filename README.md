# OpenCIM

<img src="https://pic.imgdb.cn/item/64c325591ddac507cc9a5a6e.jpg" style="zoom:50%;"  alt=""/>

[![Static Badge](https://img.shields.io/badge/南师大-地科院-orange)](http://dky.njnu.edu.cn/)
![Static Badge](https://img.shields.io/badge/OpenCIM-LibCIMModel-blue)![Static Badge](https://img.shields.io/badge/OpenCIM-CIMCreator-blue)![Static Badge](https://img.shields.io/badge/OpenCIM-CIMViewer-blue)
![Static Badge](https://img.shields.io/badge/C%2B%2B-v17-green)![Static Badge](https://img.shields.io/badge/CMake-v3.25-green)

OpenCIM是基于闾国年教授场景学思想的场景数据模型实现。

本仓库包含以下内容：

- LibCIMModel —— OpenCIM核心库，提供场景学数据模型操作SDK。
- CIMCreator —— OpenCIM创建的简单示例，调用LibCIMModel实现简单场景用例。
- CIMViewer —— OpenCIM简单可视化，调用LIbCIMModel读取CIMCreator生成的示例数据并可视化。

    - CPSViewer ——对CIMModel中分类、颗粒体系进行可视化。
    - 3DViewer —— 对CIMModel进行三维可视化。
- Data —— CIMCreator 中所生成的ACIM示例数据。
- Paper —— 场景学主要著作

## 文件结构

- 3rdlibs 外部库文件
- Data 示例数据
- LibCIMModel、CIMCreator、CIMViewer 仓库核心文件
- out 编译输出文件

## 安装

无需安装，采用CMake编译运行

## LibCIMModel

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

因此我们将【概念】、【公理】作为一类，称为场景标准——【CIMStandard】；将【组件】、【实体】【系统】作为一类称为场景内容——【CIMContent】。

上述六类对象在场景中都具有【UniqueID】字段作为唯一标识，【UniqueID】采用【Code】和【Comments】进行描述。【Code】为对象编码，全局唯一；【Comments】为对象描述，由用户输入，仅便于场景文件的阅读和理解。

对象间调用采用【UniqueID】形式进行调用，并不之间传输对象。

所有对象储存在场景中，可以根据【UniqueID】中的【Code】查询任意对象。

### 库依赖

LibCIMModel对JSON文件的读写依赖于nlohmann库。

### 模型简述

#### CIMStandard

场景标准由四部分组成：

- 引用的外部场景标准（零至多个）—— includeStandard
- 场景头（有且只有一个） —— CIMHeader
- 公理集合 （零至多个）—— axioms
- 概念集合（零至多个）—— concepts

##### includeStandard

在构建场景标准时，如果有部分标准在另一场景标准文件中已经构建，或本场景标准希望基于某一标准进行扩充描述等，可以引用外部场景标准文件。

##### CIMHeader

用于描述场景信息，主要包含：

- 场景名 —— CIMName
- 场景类型（场景标准、场景内容） —— CIMType
- 场景创建日期 —— CIMDate
- 场景描述信息 —— CIMDescription
- 场景引用的外部场景路径（场景标准或场景内容） —— includes

##### axioms

对场景中【概念】的逻辑约束，主要包含：

- 公理标识 —— id
- 公理类型（空 编号0、作用 编号1、推导 编号2、子类 编号3、父类 编号4、父颗粒 编号5、子颗粒 编号6、附属 编号7） —— axiomType
- 公理依据 —— basis
- 公理对应概念集合 —— correspondingConcepts

##### concepts

对世界万物的抽象，主要包含：

- 概念标识 —— id
- 概念名 —— name
- 公理集合 —— axioms

#### CIMContent

场景内容主要由七部分组成：

- 引用的外部场景标准（零至一个）—— includeStandard
- 引用的外部场景内容（零至多个）—— includeCIMContent
- 场景头（有且只有一个） —— CIMHeader
- 外联数据集合（零至多个）—— externalDatas
- 组件集合（零至多个）—— components
- 实体集合（零至多个）—— entities
- 系统集合（零至多个）—— systems

##### includeStandard/includeCIMContent

在构建场景内容时，可以引用外部场景标准对场景内容进行约束。

在构建场景内容时，如果有部分内容在另一场景内容文件中已经构建，可以引用外部场景内容文件。

##### CIMHeader

与CIMStandard场景头一致。

##### externalDatas

场景中外联的公共已知格式文件，如.obj、.ifc、.png等，主要包含：

- 外联数据标识 —— id

- 数据格式 —— dataFormat

- 数据外部储存地址 —— outerUrl

  [^数据在硬盘中或网络上的储存位置]:

- 数据内部储存地址 —— innerUrl

  [^如IFC文件内部具有复杂的文件结构，可以只引用某一IFC文件内部某一构件。]:

##### components

用于对场景【实体】内部进行描述，属于无状态、无根要素。

component为基类，仅具有组件类型（componentType）字段。

共有八类组件继承自component类，分别为语义（Semantics）、空间几何（SpatialGeometry）、空间位置（SpatialLocation）、空间系统（SpatialSystem）、时间点（TemporalPoint）、时间范围（TemporalRange）、时间系统（TemporalSystem）、属性（Property）。

- 语义：定义（definition）、描述（description） 编号0

- 空间几何：空间几何类型（spatialGeometryType）、geometry（空间几何描述）、uv（几何材质）编号3

- 空间位置：x平移距离（panX）、y平移距离（panY）、z平移距离（panZ）、rotateX（x旋转角度）、rotateY（y旋转角度）、z旋转角度（rotateZ）、模型缩放（scale）
  编号1

- 空间系统：空间坐标系标准EPSG（coordinateSystem）、中央经线（centralMeridian） 编号2

- 时间点：时间戳（timeStamp） 编号4

- 时间范围：开始时间时间戳（startTime）、结束时间时间戳（endTime） 编号6

- 时间系统：时间系统名（temporalSystemName）、时间系统类型（temporalSystemType）、相对时间系统（relativeTemporalSystem）、与相对时间系统的转换（trans）
  编号5

- 属性：字段名（fieldName）、字段来源（source）、字段类型（fieldType）、字段值（fieldType） 编号7

  [^表达材质属性，需要特定的字段名和字段类型]:

##### entities

场景中的活动对象，主要包含：

- 构成组件集合 —— components

##### system

用于对场景【实体】间进行描述。

system为基类，仅具有系统类型（systemType）字段。

共有三类系统继承自system类，分别为关系（Relation）、演化（Evolution）、机制（Mechanism）。

- 关系：描述（description）、出发实体集合（fromEntities）、指向实体集合（toEntities） 编号0
- 演化：出发实体（fromEntity）、指向实体（toEntity） 编号1
- 机制：机制名（mechanismName）、机制描述（mechanismComments）、机制版本（mechanismVersion）、机制路径（mechanismPath） 编号2

### 库功能

- 创建、读取、查询、修改、保存CIMStandard
- 创建、读取、查询、修改、保存CIMContent

### 使用说明

1. 编译LibCIMModel
2. 引入LibCIMModel头文件、静态链接库
3. 通过CreateCIMStandard、CreateCIMContent创建场景操作接口
4. 通过场景接口实现场景功能

### 保存格式

采用JSON格式进行保存，JSON中为场景中各类型对象的列表，每一列表中储存着该类型下的所有对象，每一对象的JSON结构与逻辑结构一致。

![](https://pic.imgdb.cn/item/64c23f591ddac507cc386dea.jpg)

公理JSON结构示例

![](https://pic.imgdb.cn/item/64c2450f1ddac507cc44e24e.jpg)

概念JSON结构示例

### 快速开始

下面示例如何使用LibCIMModel创建并保存场景，更详细的场景构建示例，请查看CIMCreator。

```c++
#include <ICIMStandard.hpp>
#include <ICIMContent.hpp>

using namespace NNU::OpenCIM;

int main()
{
    // 打开场景标准
    auto CIMStandard = CreateCIMStandard();
    CIMStandard->fromJson("./Example/CIMStandard.json");
    
     // 创建场景
    auto CIMContent = CreateCIMContent();
    
    // 创建场景头
    auto header = CIMContent->getHeader();
    header->setCIMName("NNU-CIM3");
    header->setCIMDescription("南师大老北区CIM3层级ACIM示例");
    header->addInclude(Include{STANDARD, "./CIMStandard.json"});
    
    // 保存场景
    CIMContent->toJson("Example/NNU-ACIM/NNU-ACIM.json");
}
```

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

## CIMCreator

### 背景

CIMCreator 是基于LibCIMModel的基础上，构建场景模型数据集的示例可执行程序。

### 库依赖

CIMCreator 依赖于LibCIMModel库。

### 程序功能

程序中共有三个示例函数：CIMStandard、NNU-ACIM、TestPlugin，分别用于构建CIM场景基础标准示例、CIM3层级以南师大北区数据为例的ACIM数据格式示例、场景机制使用示例。

### 快速开始

#### 编译插件

将CMakeList对应位置修改为如下形式，编译程序即可。

```cmake
#add_executable(CIMCreator CIMStandard.cpp Mechanism/TestPlugin.cpp main.cpp NNU-ACIM.cpp)
add_library(CIMCreator SHARED Mechanism/Plugin/HelloMechanism.cpp)
```

#### 运行示例

将CMakeList对应位置修改为如下形式。

```cmake
add_executable(CIMCreator CIMStandard.cpp Mechanism/TestPlugin.cpp main.cpp NNU-ACIM.cpp)
# add_library(CIMCreator SHARED Mechanism/Plugin/HelloMechanism.cpp)
```

在main.cpp文件中选择想要运行的函数，并取消注释。

```c++
int main() {
//    CIMStandard();
//    NNUACIM();
    TestPlugin();
}
```

### 更新记录

|   更新时间    | 更新类型 |        更新内容         |
|:---------:|:----:|:-------------------:|
| 2023.7.17 |  修改  |       调整文件结构        |
| 2023.7.17 |  新增  | CIM1层级【公理】-【概念】标准示例 |
| 2023.7.17 |  新增  |     【材质】【纹理】示例      |
| 2023.7.18 |  新增  |       【机制】示例        |

## CIMViewer

### 背景

CIMViewer是基于LibCIMModel的基础上，对场景JSON文件进行可视化的程序。

### 库依赖

CIMViewer中，3DViewer依赖于LibCIMModel和VTK库；CPSViewer依赖于LibCIMModel和glfw库。

### 程序功能

程序分为两个模块：

- 3DViewer（3 Dimension Viewer）—— 场景JSON中所有具有几何的实体三维静态可视化。
- CPSViewer（Classification Particle System Viewer） —— 场景JSON中所有概念和公理所构成的分类颗粒体系可视化。

### 快速开始

#### 3DViewer

3DViewer采用命令行程序形式，从命令行读取程序参数。

3DViewer程序参数有且只有一个，参数要求如下：

| 参数类型   | 参数含义     | 示例                                         |
|--------|----------|--------------------------------------------|
| string | 场景json路径 | ../../../../../Data/NNU-ACIM/NNU-ACIM.json |

在编译运行时，可以设置程序参数，例：`../../../../../Data/NNU-ACIM/NNU-ACIM.json`。

或在控制台打开程序所在目录，并输入`3DViewer.exe ../../../../../Data/NNU-ACIM/NNU-ACIM.json `。

![](https://pic.imgdb.cn/item/64c324601ddac507cc98f2ea.jpg)

3DViewer程序示例

#### CPSViewer

CPSViewer采用命令行形式，从命令行读取程序参数。

3DViewer程序参数有两个，参数要求如下：

| 参数类型   | 参数含义                   | 示例                                         |
|--------|------------------------|--------------------------------------------|
| int    | 1：场景标准文件<br />2：场景内容文件 | 2                                          |
| string | 场景json路径               | ../../../../../Data/NNU-ACIM/NNU-ACIM.json |

在编译运行时，可以设置程序参数，例：`2 ../../../../../Data/NNU-ACIM/NNU-ACIM.json`。

或在控制台打开程序所在目录，并输入`CPSViewer.exe 2 ../../../../../Data/NNU-ACIM/NNU-ACIM.json `。

![](https://pic.imgdb.cn/item/64c3243e1ddac507cc989e65.jpg)

CPSViewer分类体系示例

![](https://pic.imgdb.cn/item/64c3242b1ddac507cc987ea1.jpg)

CPSViewer颗粒体系示例

### 更新记录

|   更新时间    | 更新类型 |     更新内容     |
|:---------:|:----:|:------------:|
| 2023.7.26 |  新增  | 创建CIMViewer  |
| 2023.7.30 |  修改  | 修改了部分描述与说明文字 |

