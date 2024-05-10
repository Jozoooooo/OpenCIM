# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.25)

project (OpenCIM)

# ACIM核心类库
add_subdirectory (LibCIMModel)
# ACIM验证案例
add_subdirectory (ACIMTest)
# Excel批量转换为模式信息
add_subdirectory (SchemaConvert)
# ACIM可视化系统（轻量版本）
add_subdirectory (ACIMViewer-Lite)