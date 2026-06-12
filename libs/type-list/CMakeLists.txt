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
    types_test.cpp
    type_list_test.cpp
    empty_test.cpp
    size_test.cpp
    front_test.cpp
    back_test.cpp
    pop_front_test.cpp
    pop_back_test.cpp
    push_front_test.cpp
    push_back_test.cpp
    insert_test.cpp
    concat_test.cpp
    from_pack_test.cpp
    map_test.cpp
    filter_test.cpp
    fold_left_test.cpp
    fold_right_test.cpp
    zip_test.cpp
    zip_with_test.cpp
    unzip_test.cpp
    reverse_test.cpp
    flatten_test.cpp
)

foreach(rel_path IN LISTS TYPE_LIST_TESTS)
    string(REPLACE ".cpp" "" stem "${rel_path}")
    set(target "type_list_${stem}")
    add_executable(${target} "tests/${rel_path}")
    target_link_libraries(${target} PRIVATE type_list)
    add_test(NAME ${target} COMMAND ${target})
endforeach()

set(TYPE_LIST_EXAMPLES
    types_example.cpp
    type_list_example.cpp
    empty_example.cpp
    size_example.cpp
    front_example.cpp
    back_example.cpp
    pop_front_example.cpp
    pop_back_example.cpp
    push_front_example.cpp
    push_back_example.cpp
    insert_example.cpp
    concat_example.cpp
    from_pack_example.cpp
    map_example.cpp
    filter_example.cpp
    fold_left_example.cpp
    fold_right_example.cpp
    zip_example.cpp
    zip_with_example.cpp
    unzip_example.cpp
    reverse_example.cpp
    flatten_example.cpp
)

foreach(rel_path IN LISTS TYPE_LIST_EXAMPLES)
    string(REPLACE ".cpp" "" stem "${rel_path}")
    set(target "type_list_${stem}")
    add_executable(${target} "examples/${rel_path}")
    target_link_libraries(${target} PRIVATE type_list)
endforeach()
