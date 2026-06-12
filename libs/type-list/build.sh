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

module_files=(
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

for part in "${module_files[@]}"; do
  stem="${part//\//_}"
  stem="${stem%.cppm}"
  "$cxx" "${flags[@]}" "$part" -c -o "${obj_dir}/${stem}.o"
done

"$cxx" "${flags[@]}" modules/type_list.cppm -c -o "${obj_dir}/type_list.o"

source_files=(
  tests/types_test.cpp
  tests/type_list_test.cpp
  tests/empty_test.cpp
  tests/size_test.cpp
  tests/front_test.cpp
  tests/back_test.cpp
  tests/pop_front_test.cpp
  tests/pop_back_test.cpp
  tests/push_front_test.cpp
  tests/push_back_test.cpp
  tests/insert_test.cpp
  tests/concat_test.cpp
  tests/from_pack_test.cpp
  tests/map_test.cpp
  tests/filter_test.cpp
  tests/fold_left_test.cpp
  tests/fold_right_test.cpp
  tests/zip_test.cpp
  tests/zip_with_test.cpp
  tests/unzip_test.cpp
  tests/reverse_test.cpp
  tests/flatten_test.cpp
  examples/types_example.cpp
  examples/type_list_example.cpp
  examples/empty_example.cpp
  examples/size_example.cpp
  examples/front_example.cpp
  examples/back_example.cpp
  examples/pop_front_example.cpp
  examples/pop_back_example.cpp
  examples/push_front_example.cpp
  examples/push_back_example.cpp
  examples/insert_example.cpp
  examples/concat_example.cpp
  examples/from_pack_example.cpp
  examples/map_example.cpp
  examples/filter_example.cpp
  examples/fold_left_example.cpp
  examples/fold_right_example.cpp
  examples/zip_example.cpp
  examples/zip_with_example.cpp
  examples/unzip_example.cpp
  examples/reverse_example.cpp
  examples/flatten_example.cpp
)

mkdir -p build
for src in "${source_files[@]}"; do
  stem="$(basename "${src%.cpp}")"
  "$cxx" -std=c++23 -fmodules-ts "$src" "${obj_dir}"/*.o -o "build/type_list_${stem}"
done

echo "built build/type_list_*"
