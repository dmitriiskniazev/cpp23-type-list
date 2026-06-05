# cpp23-type-list

Compile-time type lists in **C++23 modules**: a Lisp-style `nil` / `cons` spine with metafunctions for map, filter, fold, zip, and more. Educational code — no runtime list API, only `static_assert` and type aliases.

## Requirements

- CMake **3.28+** (CMake **4.x** recommended for experimental `import std` support)
- **Ninja** (or Visual Studio generator)
- **LLVM Clang 18+** with libc++ standard library modules (`import std`). On macOS, use Homebrew LLVM — Apple Clang does not provide `libc++.modules.json`.

On macOS, point CMake at LLVM (also auto-detected when installed via Homebrew):

```bash
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++
```

## Quick start

```bash
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
```

Optional example binaries (one per partition):

```bash
./build/type_list_construct_push_front_example
./build/type_list_transform_map_example
```

## Usage

Import the umbrella module. All symbols live in namespace `type_list`. Use `import std` for standard types (`std::same_as`, `std::type_identity`, …) — no `#include` needed:

```cpp
import std;
import type_list;

struct Fst;
struct Snd;
struct Trd;

using List = type_list::from_pack_t<Fst, Snd>;
using ExtendedList = type_list::push_back_t<List, Trd>;
using ExpectedList = type_list::from_pack_t<Fst, Snd, Trd>;
static_assert(std::same_as<ExtendedList, ExpectedList>);
```

See `examples/` for per-partition walkthroughs (mirrors `modules/` and `tests/`) and [docs/API.md](docs/API.md) for the full metafunction reference.

## Project layout

```
modules/
  type_list.cppm              # umbrella: export import of submodules
  type_list/
    core/
      core.cppm               # submodule :core
      types.cppm              #   :core.types — nil, cons
      type_list.cppm          #   :core.type_list — type_list concept
    traits/
      traits.cppm             # submodule :traits
      empty.cppm              #   :traits.empty
      non_empty.cppm          #   :traits.non_empty
      size.cppm               #   :traits.size
    access/                   # :access.front, back, pop_front, pop_back
    construct/                # :construct.push_front, push_back, insert, concat, from_pack
    transform/                # :transform.map, filter, fold_left, fold_right
    combine/                  # :combine.zip, reverse, flatten
tests/
  core/                     # mirrors core/
  traits/
  access/
  construct/
  transform/
  combine/
examples/
  core/                     # mirrors modules/ and tests/
  traits/
  access/
  construct/
  transform/
  combine/
```

Import the full library with `import type_list`, a submodule, or a leaf partition:

```cpp
import type_list;                    // everything
import type_list:traits;            // empty, non_empty, size_v
import type_list:construct.push_back;   // push_back_t only
```

Library and consumer code use **`import std`** (CMake builds libc++'s `std` module automatically). Standard names stay **`std::`-qualified** — e.g. `std::type_identity`, `std::same_as`.

## Algorithms

| Name | Alias | Notes |
|------|--------|--------|
| `nil` | `nil` | empty list |
| `from_pack_t` | `from_pack_t<Ts...>` | build from a type pack |
| `empty` | `empty<list>` | predicate |
| `size_v` | `size_v<list>` | element count |
| `front_t` / `back_t` | `front_t<list>`, `back_t<list>` | first / last type (`non_empty`) |
| `pop_front_t` / `pop_back_t` | `pop_front_t<list>`, `pop_back_t<list>` | drop first / last (`non_empty`) |
| `push_front_t` / `push_back_t` / `insert_t` | `push_front_t<type, list>`, … | insert one type |
| `concat_t` / `flatten_t` | `concat_t<left, right>`, `flatten_t<list>` | list algebra |
| `map_t` / `filter_t` | `map_t<unary_op, list>`, … | transform (`filter` `unary_op` has `::value`) |
| `fold_left_t` / `fold_right_t` | `fold_left_t<init, binary_op, list>`, … | `binary_op` inherits `std::type_identity` |
| `zip_t` | `zip_t<left, right>` | `std::pair`; stops at shorter list |
| `zip_with_t` | `zip_with_t<binary_op, left, right>` | custom element type; stops at shorter list |
| `unzip_t` | `unzip_t<list>` | `std::pair` of two type lists |
| `reverse_t` | `reverse_t<list>` | reverse element order |

Concepts: `type_list::type_list<type>`, `type_list::non_empty<type>`, `type_list::empty<type>`.

## Formatting

`clang-format` uses **three configs**:

| Path | Style |
|------|--------|
| `modules/` | root `.clang-format` — tight wraps for template metaprogramming |
| `tests/`, `examples/` | local `.clang-format` — 100 columns, attached braces, single-line asserts |

Run `./scripts/format.sh` to format all three trees. Format-on-save in the IDE picks up the nearest `.clang-format` (walks up from the file path).

In `examples/` and `tests/`, use **PascalCase** for marker types, type aliases, metafunction structs, and template type parameters (`Fst`, `List`, `Boxed`, `Type`, …). Library API identifiers stay lowercase (`from_pack_t`, `map_t`, `unary_op`, …).

## License

MIT — see [LICENSE](LICENSE).
