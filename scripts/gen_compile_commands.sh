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
  modules/type_list.cppm
)

{
  echo '['
  for i in "${!modules[@]}"; do
    write_module_entry "${modules[$i]}"
    [[ $i -lt $((${#modules[@]} - 1)) ]] && echo ','
  done
  echo ','
  write_cpp_entry tests/type_list_test.cpp
  echo ']'
} > compile_commands.json

echo "wrote compile_commands.json"
