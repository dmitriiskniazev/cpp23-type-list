cmake_minimum_required(VERSION 3.28)

# Experimental CMake support for `import std;` (C++23).
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

if(NOT CMAKE_CXX_COMPILER AND EXISTS "/opt/homebrew/opt/llvm/bin/clang++")
    set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
endif()

if(CMAKE_CXX_COMPILER MATCHES "clang")
    get_filename_component(_llvm_bin "${CMAKE_CXX_COMPILER}" REALPATH)
    get_filename_component(_llvm_prefix "${_llvm_bin}" DIRECTORY)
    get_filename_component(_llvm_prefix "${_llvm_prefix}" DIRECTORY)
    set(_stdlib_modules_json "${_llvm_prefix}/lib/c++/libc++.modules.json")
    if(EXISTS "${_stdlib_modules_json}")
        set(CMAKE_CXX_STDLIB_MODULES_JSON "${_stdlib_modules_json}" CACHE FILEPATH "" FORCE)
    endif()
    unset(_llvm_bin)
    unset(_llvm_prefix)
    unset(_stdlib_modules_json)
endif()

project(type-list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_GENERATOR MATCHES "Ninja" AND NOT CMAKE_GENERATOR MATCHES "Visual Studio")
    message(FATAL_ERROR
        "C++ modules require the Ninja or Visual Studio generator. "
        "Example: cmake -B build -G Ninja")
endif()

add_library(type_list)
target_sources(type_list
    PUBLIC
        FILE_SET CXX_MODULES FILES
            modules/type_list.cppm
            modules/type_list/types.cppm
            modules/type_list/type_list.cppm
            modules/type_list/empty.cppm
            modules/type_list/non_empty.cppm
            modules/type_list/size.cppm
            modules/type_list/front.cppm
            modules/type_list/back.cppm
            modules/type_list/pop_front.cppm
            modules/type_list/pop_back.cppm
            modules/type_list/push_front.cppm
            modules/type_list/push_back.cppm
            modules/type_list/insert.cppm
            modules/type_list/concat.cppm
            modules/type_list/from_pack.cppm
            modules/type_list/map.cppm
            modules/type_list/filter.cppm
            modules/type_list/fold_left.cppm
            modules/type_list/fold_right.cppm
            modules/type_list/zip.cppm
            modules/type_list/zip_with.cppm
            modules/type_list/unzip.cppm
            modules/type_list/reverse.cppm
            modules/type_list/flatten.cppm
)
target_include_directories(type_list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(TYPE_LIST_TESTS
    core/types_test.cpp
    core/type_list_test.cpp
    traits/empty_test.cpp
    traits/size_test.cpp
    access/front_test.cpp
    access/back_test.cpp
    access/pop_front_test.cpp
    access/pop_back_test.cpp
    construct/push_front_test.cpp
    construct/push_back_test.cpp
    construct/insert_test.cpp
    construct/concat_test.cpp
    construct/from_pack_test.cpp
    transform/map_test.cpp
    transform/filter_test.cpp
    transform/fold_left_test.cpp
    transform/fold_right_test.cpp
    combine/zip_test.cpp
    combine/zip_with_test.cpp
    combine/unzip_test.cpp
    combine/reverse_test.cpp
    combine/flatten_test.cpp
)

enable_testing()

foreach(rel_path IN LISTS TYPE_LIST_TESTS)
    string(REPLACE ".cpp" "" stem "${rel_path}")
    string(REPLACE "/" "_" target_suffix "${stem}")
    set(target "type_list_${target_suffix}")
    add_executable(${target} "tests/${rel_path}")
    target_link_libraries(${target} PRIVATE type_list)
    add_test(NAME ${target} COMMAND ${target})
endforeach()

set(TYPE_LIST_EXAMPLES
    core/types_example.cpp
    core/type_list_example.cpp
    traits/empty_example.cpp
    traits/size_example.cpp
    access/front_example.cpp
    access/back_example.cpp
    access/pop_front_example.cpp
    access/pop_back_example.cpp
    construct/push_front_example.cpp
    construct/push_back_example.cpp
    construct/insert_example.cpp
    construct/concat_example.cpp
    construct/from_pack_example.cpp
    transform/map_example.cpp
    transform/filter_example.cpp
    transform/fold_left_example.cpp
    transform/fold_right_example.cpp
    combine/zip_example.cpp
    combine/zip_with_example.cpp
    combine/unzip_example.cpp
    combine/reverse_example.cpp
    combine/flatten_example.cpp
)

foreach(rel_path IN LISTS TYPE_LIST_EXAMPLES)
    string(REPLACE ".cpp" "" stem "${rel_path}")
    string(REPLACE "/" "_" target_suffix "${stem}")
    set(target "type_list_${target_suffix}")
    add_executable(${target} "examples/${rel_path}")
    target_link_libraries(${target} PRIVATE type_list)
endforeach()
