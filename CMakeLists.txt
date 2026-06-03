cmake_minimum_required(VERSION 3.28)

project(cpp23-type-list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
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
            modules/type_list/std.cppm
            modules/type_list/core.cppm
            modules/type_list/is_nil.cppm
            modules/type_list/length.cppm
            modules/type_list/head.cppm
            modules/type_list/tail.cppm
            modules/type_list/prepend.cppm
            modules/type_list/append.cppm
            modules/type_list/concat.cppm
            modules/type_list/from_pack.cppm
            modules/type_list/map.cppm
            modules/type_list/filter.cppm
            modules/type_list/fold_left.cppm
            modules/type_list/fold_right.cppm
            modules/type_list/zip.cppm
            modules/type_list/reverse.cppm
            modules/type_list/flatten.cppm
)
target_include_directories(type_list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(TYPE_LIST_MODULE_TESTS
    core
    is_nil
    length
    head
    tail
    prepend
    append
    concat
    from_pack
    map
    filter
    fold_left
    fold_right
    zip
    reverse
    flatten
)

enable_testing()

foreach(module IN LISTS TYPE_LIST_MODULE_TESTS)
    set(target type_list_${module}_test)
    add_executable(${target} tests/${module}_test.cpp)
    target_link_libraries(${target} PRIVATE type_list)
    add_test(NAME ${target} COMMAND ${target})
endforeach()

add_executable(type_list_usage examples/type_list_usage.cpp)
target_link_libraries(type_list_usage PRIVATE type_list)
