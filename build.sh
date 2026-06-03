#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "$0")" && pwd)"
cd "$root"

cxx="${CXX:-g++-15}"
if ! command -v "$cxx" >/dev/null 2>&1; then
  cxx="${CXX:-g++}"
fi

obj_dir=build/obj
mkdir -p "$obj_dir"
rm -rf gcm.cache

flags=(-std=c++23 -fmodules-ts -x c++)

for part in core is_nil length head tail prepend append concat from_pack map filter fold_left fold_right zip reverse flatten; do
  "$cxx" "${flags[@]}" "modules/type_list/${part}.cppm" -c -o "${obj_dir}/${part}.o"
done

"$cxx" "${flags[@]}" modules/type_list.cppm -c -o "${obj_dir}/type_list.o"

for module in core is_nil length head tail prepend append concat from_pack map filter fold_left fold_right zip reverse flatten; do
  "$cxx" -std=c++23 -fmodules-ts "tests/${module}_test.cpp" "${obj_dir}"/*.o -o "build/type_list_${module}_test"
done

echo "built build/type_list_*_test"
