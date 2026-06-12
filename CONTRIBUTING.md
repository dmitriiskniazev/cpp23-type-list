# Contributing

Thanks for improving **cpp**. This monorepo holds C++23 projects; the first library is **type-list** under `libs/type-list/` (compile-time only: `static_assert` and type aliases).

## Prerequisites

- **Clang 19+** with libc++ `import std` (Homebrew LLVM on macOS; official LLVM tarball on Linux CI)
- **CMake 4.3+** and **Ninja**
- **clang-format 22+** (match CI)

Apple Clang and GCC are not supported.

## Local workflow

```bash
./scripts/ci.sh

# Or step by step:
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
./scripts/format.sh          # after editing libs/**/*.cpp / *.cppm
```

Optional git hooks:

```bash
pip install pre-commit   # or: brew install pre-commit
./scripts/install-hooks.sh
pre-commit run --all-files
```

## Repository automation

GitHub Actions run format check, build/test on macOS and Ubuntu, and label PRs. See `.github/workflows/`.

Recommended branch protection on `master`:

- Require status checks: **Format**, **Build (macos-latest)**, **Build (ubuntu-latest)**

## Adding a type-list operation

Follow [AGENTS.md](AGENTS.md). In short:

1. Add `libs/type-list/modules/type_list/<op>.cppm`
2. `export import :<op>;` in `libs/type-list/modules/type_list.cppm`
3. Register in `libs/type-list/CMakeLists.txt`
4. Update [libs/type-list/docs/API.md](libs/type-list/docs/API.md)
5. Run `./scripts/ci.sh`

## Adding another library

1. Create `libs/<name>/` with its own `CMakeLists.txt`
2. Add `add_subdirectory(libs/<name>)` to root `CMakeLists.txt`
3. Reuse `cmake/CppModules.cmake` — do not duplicate toolchain setup

## Pull requests

- Keep diffs focused
- No `#include` in module trees under `libs/`
- CI must pass on macOS and Ubuntu

## Questions

Open a [discussion](https://github.com/dmitriiskniazev/cpp/discussions) or an issue using `.github/ISSUE_TEMPLATE/`.
