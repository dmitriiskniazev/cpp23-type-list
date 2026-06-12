cmake_minimum_required(VERSION 3.28)

include(cmake/CppModules.cmake)
cpp_detect_toolchain()

project(cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cpp_apply_linux_rpath()
cpp_require_ninja_or_vs()

include(CTest)
enable_testing()

add_subdirectory(libs/type-list)
