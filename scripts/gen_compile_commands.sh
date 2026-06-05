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
  modules/type_list/core/types.cppm
  modules/type_list/core/type_list.cppm
  modules/type_list/core/core.cppm
  modules/type_list/traits/empty.cppm
  modules/type_list/traits/non_empty.cppm
  modules/type_list/traits/size.cppm
  modules/type_list/traits/traits.cppm
  modules/type_list/access/front.cppm
  modules/type_list/access/back.cppm
  modules/type_list/access/pop_front.cppm
  modules/type_list/access/pop_back.cppm
  modules/type_list/access/access.cppm
  modules/type_list/construct/push_front.cppm
  modules/type_list/construct/push_back.cppm
  modules/type_list/construct/insert.cppm
  modules/type_list/construct/concat.cppm
  modules/type_list/construct/from_pack.cppm
  modules/type_list/construct/construct.cppm
  modules/type_list/transform/map.cppm
  modules/type_list/transform/filter.cppm
  modules/type_list/transform/fold_left.cppm
  modules/type_list/transform/fold_right.cppm
  modules/type_list/transform/transform.cppm
  modules/type_list/combine/zip.cppm
  modules/type_list/combine/reverse.cppm
  modules/type_list/combine/flatten.cppm
  modules/type_list/combine/combine.cppm
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
