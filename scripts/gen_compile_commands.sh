#!/usr/bin/env bash
# Regenerates compile_commands.json for clangd / IDE (.cppm needs -x c++-module).
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

write_module_entry() {
  local file="$1"
  cat <<ENTRY
  {
    "directory": "${root}",
    "file": "${file}",
    "arguments": [
      "clang++",
      "-std=c++23",
      "-x",
      "c++-module",
      "-c",
      "${file}"
    ]
  }
ENTRY
}

write_cpp_entry() {
  local file="$1"
  cat <<ENTRY
  {
    "directory": "${root}",
    "file": "${file}",
    "arguments": [
      "clang++",
      "-std=c++23",
      "-c",
      "${file}"
    ]
  }
ENTRY
}

modules=(
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
  modules/type_list.cppm
)

tests=(
  tests/core/types_test.cpp
  tests/core/type_list_test.cpp
  tests/traits/empty_test.cpp
  tests/traits/size_test.cpp
  tests/access/front_test.cpp
  tests/access/back_test.cpp
  tests/access/pop_front_test.cpp
  tests/access/pop_back_test.cpp
  tests/construct/push_front_test.cpp
  tests/construct/push_back_test.cpp
  tests/construct/insert_test.cpp
  tests/construct/concat_test.cpp
  tests/construct/from_pack_test.cpp
  tests/transform/map_test.cpp
  tests/transform/filter_test.cpp
  tests/transform/fold_left_test.cpp
  tests/transform/fold_right_test.cpp
  tests/combine/zip_test.cpp
  tests/combine/reverse_test.cpp
  tests/combine/flatten_test.cpp
)

examples=(
  examples/core/types_example.cpp
  examples/core/type_list_example.cpp
  examples/traits/empty_example.cpp
  examples/traits/size_example.cpp
  examples/access/front_example.cpp
  examples/access/back_example.cpp
  examples/access/pop_front_example.cpp
  examples/access/pop_back_example.cpp
  examples/construct/push_front_example.cpp
  examples/construct/push_back_example.cpp
  examples/construct/insert_example.cpp
  examples/construct/concat_example.cpp
  examples/construct/from_pack_example.cpp
  examples/transform/map_example.cpp
  examples/transform/filter_example.cpp
  examples/transform/fold_left_example.cpp
  examples/transform/fold_right_example.cpp
  examples/combine/zip_example.cpp
  examples/combine/reverse_example.cpp
  examples/combine/flatten_example.cpp
)

entries=("${modules[@]}" "${tests[@]}" "${examples[@]}")

{
  echo '['
  for i in "${!entries[@]}"; do
    file="${entries[$i]}"
    if [[ "${file}" == *.cppm ]]; then
      write_module_entry "${file}"
    else
      write_cpp_entry "${file}"
    fi
    [[ $i -lt $((${#entries[@]} - 1)) ]] && echo ','
  done
  echo ']'
} > compile_commands.json

echo "wrote compile_commands.json"
