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
  tests/combine/zip_with_test.cpp
  tests/combine/unzip_test.cpp
  tests/combine/reverse_test.cpp
  tests/combine/flatten_test.cpp
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
  examples/combine/zip_with_example.cpp
  examples/combine/unzip_example.cpp
  examples/combine/reverse_example.cpp
  examples/combine/flatten_example.cpp
)

mkdir -p build
for src in "${source_files[@]}"; do
  stem="${src#*/}"
  stem="${stem%.cpp}"
  stem="${stem//\//_}"
  "$cxx" -std=c++23 -fmodules-ts "$src" "${obj_dir}"/*.o -o "build/type_list_${stem}"
done

echo "built build/type_list_*"
