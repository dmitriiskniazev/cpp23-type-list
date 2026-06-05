# type-list

[![CI](https://github.com/dmitriiskniazev/type-list/actions/workflows/ci.yml/badge.svg)](https://github.com/dmitriiskniazev/type-list/actions/workflows/ci.yml)

Compile-time type lists for C++23 modules: a `nil` / `cons` spine, one module partition per operation, and a single umbrella import.

## Features

- **C++23 modules** — `export module type_list:<partition>` with `import type_list` for the full API
- **Minimal core** — `nil`, `cons`, and the `type_list` concept
- **Algorithms** — access, construction, map / filter / fold, zip / unzip, reverse, flatten
- **Template-template metafunctions** — pass unary or binary class templates to map, filter, fold, and zip_with

## Requirements

- **Compiler:** Clang 19+ with `-std=c++23` and experimental modules (`import std`)
- **Build:** CMake 3.28+ and Ninja (recommended)
- **macOS:** [Homebrew LLVM](https://formulae.brew.sh/formula/llvm) — the project expects `/opt/homebrew/opt/llvm/bin/clang++`

## Quick start

```bash
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
```

Generate `compile_commands.json` for clangd:

```bash
./scripts/gen_compile_commands.sh
```

## Usage

```cpp
import std;
import type_list;

struct A;
struct B;
struct C;

using List = type_list::from_pack_t<A, B, C>;
using Reversed = type_list::reverse_t<List>;
static_assert(type_list::size_v<Reversed> == 3);
static_assert(std::same_as<type_list::front_t<Reversed>, C>);
```

Run the matching example:

```bash
./build/type_list_front_example
./build/type_list_map_example
```

## Imports

| Style | Example | When to use |
|-------|---------|-------------|
| Umbrella | `import type_list;` | Default — full public API |
| Partition | `import type_list:map;` | Minimal dependency surface |

Partition names match the stem of the module file under `modules/type_list/` (e.g. `map.cppm` → `import type_list:map`).

## Naming conventions

### Library API (`namespace type_list`)

| Kind | Pattern | Examples |
|------|---------|----------|
| Type alias | `<op>_t<...>` | `front_t`, `push_back_t`, `map_t` |
| Value alias | `<op>_v<...>` | `size_v` |
| Concept | lowercase noun / adjective | `type_list`, `empty`, `non_empty` |
| Map / zip functor | class template | `template <typename T> struct Boxed;` then `map_t<Boxed, List>` |
| Filter predicate | `::value` | `struct Keep : std::bool_constant<...> {};` then `filter_t<Keep, List>` |
| Fold / zip_with functor | nested `type` | `struct Op : std::type_identity<...> {};` |

**Parameter order:** `push_front_t<Type, List>` · `push_back_t<List, Type>` · `map_t<Unary, List>` · `filter_t<Predicate, List>` · `fold_left_t<State, Binary, List>` · `zip_with_t<Binary, Left, Right>`.

### Tests and examples

Marker types and functors use **PascalCase** (`Fst`, `List`, `Boxed`, `MakePair`) so they read clearly next to lowercase library names.

### Files and build targets

| Artifact | Pattern | Example |
|----------|---------|---------|
| Module partition | `modules/type_list/<op>.cppm` | `map.cppm` |
| Test | `tests/<op>_test.cpp` | `map_test.cpp` |
| Example | `examples/<op>_example.cpp` | `map_example.cpp` |
| Test binary | `type_list_<op>_test` | `type_list_map_test` |
| Example binary | `type_list_<op>_example` | `type_list_map_example` |

Full symbol and partition reference: [docs/API.md](docs/API.md).

## Project layout

```
modules/
  type_list.cppm              # re-exports all partitions
  type_list/
    types.cppm                # nil, cons, type_list
    type_list.cppm            # type_list concept export
    empty.cppm, non_empty.cppm, size.cppm
    front.cppm, back.cppm, pop_front.cppm, pop_back.cppm
    push_front.cppm, push_back.cppm, insert.cppm
    concat.cppm, from_pack.cppm
    map.cppm, filter.cppm, fold_left.cppm, fold_right.cppm
    zip.cppm, zip_with.cppm, unzip.cppm
    reverse.cppm, flatten.cppm
tests/                        # one *_test.cpp per operation
examples/                     # one *_example.cpp per operation
scripts/                      # format, ci, compile_commands helpers
.github/                      # Actions, issue/PR templates, labeler
docs/API.md                   # detailed API reference
CONTRIBUTING.md               # contributor workflow
AGENTS.md                     # guide for AI coding agents
```

## API overview

| Category | Symbols |
|----------|---------|
| Core | `nil`, `cons`, `type_list`, `empty`, `non_empty`, `size`, `size_v` |
| Access | `front`, `front_t`, `back`, `back_t`, `pop_front`, `pop_front_t`, `pop_back`, `pop_back_t` |
| Build | `push_front_t`, `push_back_t`, `insert_t`, `concat_t`, `from_pack`, `from_pack_t` |
| Transform | `map_t`, `filter_t`, `fold_left_t`, `fold_right_t` |
| Combine | `zip_t`, `zip_with_t`, `unzip_t`, `reverse_t`, `flatten_t` |
| Functor params | template-template parameters on `map_t`, `filter_t`, `fold_*_t`, `zip_with_t` |

See [docs/API.md](docs/API.md) for signatures, partition map, and examples.

## Formatting

Requires [clang-format](https://clang.llvm.org/docs/ClangFormat.html) 18+:

```bash
./scripts/format.sh
./scripts/format-check.sh   # CI-style dry run
```

Optional [pre-commit](https://pre-commit.com/) hooks: `pre-commit install` (see [CONTRIBUTING.md](CONTRIBUTING.md)).

## IDE support

After `./scripts/gen_compile_commands.sh`, point clangd at the `build/` compilation database. On macOS, `.clangd` selects Homebrew LLVM as the compiler driver for `import std`.

## For AI agents

See [AGENTS.md](AGENTS.md) for build commands, layout conventions, how to add a partition, and common pitfalls.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Full local verification:

```bash
./scripts/ci.sh
```

## License

See [LICENSE](LICENSE).
