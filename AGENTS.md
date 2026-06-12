# Agent guide

Instructions for AI coding agents working in **type-list** — a compile-time C++23 module library for type lists (`nil` / `cons`). There is no runtime list API; behavior is validated with `static_assert` and type aliases.

## Quick reference

| Topic | Location |
|-------|----------|
| User-facing overview | [README.md](README.md) |
| Full API, partitions, examples map | [docs/API.md](docs/API.md) |
| Library modules | `modules/type_list/*.cppm` |
| Umbrella re-exports | `modules/type_list.cppm` |
| Tests | `tests/<op>_test.cpp` |
| Examples | `examples/<op>_example.cpp` |
| CMake registration | `CMakeLists.txt` |

## Verify changes

Prefer the CI entrypoint (format check, no-`#include` guard, CMake + Ninja, ctest):

```bash
./scripts/ci.sh
```

Or run steps manually:

```bash
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
./scripts/format-check.sh
./scripts/check-no-includes.sh
```

After editing modules, regenerate IDE metadata if needed:

```bash
./scripts/gen_compile_commands.sh
```

Format before finishing:

```bash
./scripts/format.sh
```

Optional git hooks: `pre-commit install` (see `.pre-commit-config.yaml`).

**Toolchain:** Homebrew LLVM Clang with `import std` (Apple Clang is not supported). CMake auto-detects `/opt/homebrew/opt/llvm/bin/clang++`.

## Architecture

- **One partition per operation** — `modules/type_list/<op>.cppm` exports `type_list:<op>`.
- **Umbrella module** — `modules/type_list.cppm` `export import`s every partition; consumers use `import type_list;`.
- **Internal imports** — partitions use `import :types`, `import :type_list`, etc. (relative to the primary module interface).
- **Implementation style** — recursive class templates inheriting `std::type_identity<Result>`; public surface exposes `*_t` / `*_v` aliases inside an `export { ... }` block.

## Naming rules

### Library (`namespace type_list`)

- Types / concepts: lowercase (`nil`, `cons`, `empty`, `type_list`).
- Result aliases: `<op>_t`, constants: `<op>_v` (e.g. `front_t`, `size_v`).
- Namespace opening brace on the **same line**: `namespace type_list {`.
- Template parameter names in library code: lowercase (`list`, `type`, `head_type`, `tail`).

### Tests and examples

- Marker types: ordinal **PascalCase** (`Fst`, `Snd`, `Trd`, `Frh`, …); functors: descriptive names (`Boxed`, `MakePair`).
- Files: `tests/<op>_test.cpp`, `examples/<op>_example.cpp`.
- CMake targets: `type_list_<op>_test`, `type_list_<op>_example` (stem includes `_test` / `_example` suffix).

### Parameter order (easy to get wrong)

| API | Order |
|-----|--------|
| `push_front_t` | `<Type, List>` |
| `push_back_t` | `<List, Type>` |
| `map_t` / `filter_t` | `<Functor, List>` |
| `fold_left_t` / `fold_right_t` | `<State, Binary, List>` |
| `zip_with_t` | `<Binary, Left, Right>` |

`unary_op` and `binary_op` in source are **template-template parameter names**, not exported types.

## Adding a new operation

1. Add `modules/type_list/<op>.cppm` following an existing partition (e.g. `reverse.cppm`).
2. Add `export import :<op>;` to `modules/type_list.cppm`.
3. Register the file in `target_sources(type_list ...)` in `CMakeLists.txt`.
4. Add `tests/<op>_test.cpp` and append to `TYPE_LIST_TESTS`.
5. Add `examples/<op>_example.cpp` and append to `TYPE_LIST_EXAMPLES` (optional for pure concepts).
6. Update [docs/API.md](docs/API.md) symbol index and partition table.
7. Run build, tests, and `./scripts/format.sh`.

**Partition skeleton:**

```cpp
export module type_list:<op>;

import std;

import :types;
import :type_list;
// other :partition imports as needed

namespace type_list {

    // struct <op> : std::type_identity<...> specializations

    export {
        template </* ... */>
        using <op>_t = typename <op></* ... */>::type;
    }

}  // namespace type_list
```

## Formatting

| Tree | Config | Notes |
|------|--------|-------|
| `modules/` | root `.clang-format` | Tight wraps, `AfterNamespace: false` |
| `tests/`, `examples/` | local `.clang-format` | 100 columns, attached function braces |

Do not hand-edit formatting contradictions; run `./scripts/format.sh`.

## Common pitfalls

- **Do not use `#include`** in modules/tests/examples — use `import std;` and `import type_list;`.
- **Do not use Apple Clang** — no libc++ module map for `import std`.
- **New partition** — forgetting `CMakeLists.txt` or umbrella `export import` breaks the build.
- **Filter functors** — must provide `.value` (`std::bool_constant` / `std::integral_constant`).
- **Map functors** — invoked as `Unary<T>`; result is the type denoted by that specialization.
- **Fold / zip_with functors** — need nested `type` (typically `std::type_identity<...>`).
- **Access algorithms** — require `non_empty` list; empty list is a compile error.
- **Keep diffs minimal** — one partition per feature; match surrounding style; no drive-by refactors.

## Git

- Do not commit or push unless the user asks.
- Match existing commit style: short imperative subject, optional body explaining why.

## Out of scope

- No runtime containers or reflection.
- No Boost/STL-style type_list replacement at runtime.
- Educational / header-only-style metaprogramming only.
