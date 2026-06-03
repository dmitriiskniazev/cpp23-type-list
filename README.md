# cpp23-type-list

Compile-time type lists in **C++23 modules**: a Lisp-style `Nil` / `Cons` spine with metafunctions for map, filter, fold, zip, and more. Educational code — no runtime list API, only `static_assert` and type aliases.

## Requirements

- CMake **3.28+**
- **Ninja** (or Visual Studio generator)
- Compiler with C++23 modules (e.g. **Clang 18+** from LLVM/Homebrew, or **GCC 14+** / `g++-15`)

On macOS with AppleClang only, point CMake at LLVM:

```bash
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++
```

## Quick start

```bash
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
```

Optional example binary:

```bash
./build/type_list_usage
```

## Usage

Import the umbrella module and work entirely at compile time:

```cpp
import type_list;

using Numbers = from_pack_t<int, double, char>;
static_assert(length_v<Numbers> == 3);
static_assert(same_as<head_t<Numbers>, int>);

template <typename T>
using add_pointer = T*;

using Pointers = map_t<add_pointer, Numbers>;
// from_pack_t<int*, double*, char*>
```

See [examples/type_list_usage.cpp](examples/type_list_usage.cpp) for a longer walkthrough and [docs/API.md](docs/API.md) for the full metafunction reference.

## Project layout

```
modules/
  type_list.cppm          # export import of all partitions
  type_list/
    std.cppm              # std re-exports (only partition with #include)
    core.cppm             # Nil, Cons, concepts
    …                     # one partition per algorithm
tests/                    # one executable per metafunction
examples/type_list_usage.cpp
```

## Algorithms

| Name | Alias | Notes |
|------|--------|--------|
| Empty list | `Nil` | |
| Build from pack | `from_pack_t<Ts...>` | |
| Predicate | `is_nil_v<List>` | |
| Size | `length_v<List>` | `integral_constant`-style |
| First / rest | `head_t`, `tail_t` | `non_empty_type_list` |
| Insert | `prepend_t<Elem, List>`, `append_t<List, Elem>` | |
| Combine | `concat_t<Lhs, Rhs>`, `flatten_t<List>` | `flatten` for list-of-lists |
| Transform | `map_t<Op, List>`, `filter_t<Pred, List>` | `Pred` has `::value` |
| Reduce | `fold_left_t`, `fold_right_t` | `F` exposes `typename F<...>::type` |
| Zip | `zip_t<Lhs, Rhs>` | `std::pair`, min length |
| Reverse | `reverse_t<List>` | |

Concepts: `type_list<T>`, `non_empty_type_list<T>`.

## License

MIT — see [LICENSE](LICENSE).
