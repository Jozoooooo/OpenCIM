# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.25)

project (OpenCIM)

# 场景数据模型核心类库
add_subdirectory (LibCIMModel)
# 场景数据模型验证案例
add_subdirectory (ACIMCreator)
# 场景可视化工具
add_subdirectory (ACIMViewer)