# Agent guide

Instructions for AI coding agents working in **cpp** — a C++23 monorepo (libraries, educational code, lectures, std-style implementations).

## Monorepo layout

| Path | Role |
|------|------|
| `cmake/CppModules.cmake` | Shared `import std` / LLVM / Linux libc++ setup |
| `CMakeLists.txt` | Root project; `add_subdirectory(libs/...)` |
| `libs/<name>/` | Libraries (each has own `CMakeLists.txt`, tests, docs) |
| `scripts/` | `./scripts/ci.sh`, format, compile_commands |
| `edu/`, `lectures/`, `std/` | Reserved for future non-lib trees |

## Verify changes

```bash
./scripts/ci.sh
```

Or manually:

```bash
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
./scripts/format-check.sh
./scripts/check-no-includes.sh
```

Format: `./scripts/format.sh` (all `libs/**/*.cpp` / `*.cppm`).

**Toolchain:** Homebrew LLVM Clang with `import std` (Apple Clang is not supported). CMake auto-detects `/opt/homebrew/opt/llvm/bin/clang++`.

## Adding a new library under `libs/`

1. Create `libs/<name>/` with `CMakeLists.txt`, sources, tests.
2. Add `add_subdirectory(libs/<name>)` to root `CMakeLists.txt`.
3. Register tests with `add_test`; CI runs full `ctest`.
4. Run `./scripts/ci.sh`.

Use `cmake/CppModules.cmake` from the root — do not duplicate toolchain logic in child projects.

---

## type-list (`libs/type-list/`)

Compile-time type lists (`nil` / `cons`). No runtime list API; behavior is validated with `static_assert`.

| Topic | Location |
|-------|----------|
| User overview | [libs/type-list/README.md](libs/type-list/README.md) |
| API reference | [libs/type-list/docs/API.md](libs/type-list/docs/API.md) |
| Modules | `libs/type-list/modules/type_list/*.cppm` |
| Umbrella | `libs/type-list/modules/type_list.cppm` |
| Tests / examples | `libs/type-list/tests/`, `libs/type-list/examples/` |
| CMake | [libs/type-list/CMakeLists.txt](libs/type-list/CMakeLists.txt) |

### type-list architecture

- **One partition per operation** — `modules/type_list/<op>.cppm` exports `type_list:<op>`.
- **Umbrella module** — `export import`s every partition; consumers use `import type_list;`.
- **Implementation** — recursive class templates inheriting `std::type_identity<Result>`; public `*_t` / `*_v` in `export { ... }`.

### type-list naming

**Library (`namespace type_list`):** lowercase concepts; `<op>_t` / `<op>_v` aliases.

**Tests / examples:** ordinal markers (`Fst`, `Snd`, `Trd`, …); functors (`Boxed`, `MakePair`).

**Parameter order:** `push_front_t<Type, List>` · `push_back_t<List, Type>` · `map_t<Functor, List>` · `filter_t<Predicate, List>` · `fold_left_t<State, Binary, List>` · `zip_with_t<Binary, Left, Right>`.

### Adding a type-list operation

1. Add `libs/type-list/modules/type_list/<op>.cppm`.
2. `export import :<op>;` in `modules/type_list.cppm`.
3. Register in `libs/type-list/CMakeLists.txt` (`target_sources`, `TYPE_LIST_TESTS`, `TYPE_LIST_EXAMPLES`).
4. Update [libs/type-list/docs/API.md](libs/type-list/docs/API.md).
5. Run `./scripts/ci.sh`.

### Formatting

| Tree | Config |
|------|--------|
| `libs/type-list/modules/` | root `.clang-format` |
| `libs/type-list/tests/`, `examples/` | local `.clang-format` |

### Pitfalls

- No `#include` in modules/tests/examples — use `import std;` and `import type_list;`.
- No Apple Clang.
- Filter functors need `.value`; map uses `Unary<T>`; fold/zip_with need nested `type`.

## Git

- Do not commit or push unless the user asks.

## Out of scope

- Non-C++ projects (Python vaults, etc.) belong in separate repos.
- Runtime containers or reflection in type-list.
