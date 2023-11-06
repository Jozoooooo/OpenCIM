# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.25)

project (CIMViewer)

# 场景分类颗粒树可视化
add_subdirectory ("CPSViewer")
# 场景三维可视化
add_subdirectory ("3DViewer")