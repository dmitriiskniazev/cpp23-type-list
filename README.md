# cpp

[![CI](https://github.com/dmitriiskniazev/cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/dmitriiskniazev/cpp/actions/workflows/ci.yml)

Monorepo for C++23 projects: libraries, educational exercises, lecture code, and standard-library-style implementations.

## Requirements

- **Compiler:** Clang 19+ with `-std=c++23` and `import std`
- **Build:** CMake 4.3+ and Ninja
- **macOS:** [Homebrew LLVM](https://formulae.brew.sh/formula/llvm)

## Quick start

```bash
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
```

Full local verification:

```bash
./scripts/ci.sh
```

IDE metadata: configure once, then point clangd at `build/` (or run `./scripts/gen_compile_commands.sh`).

## Projects

| Path | Description |
|------|-------------|
| [libs/type-list](libs/type-list/) | Compile-time type lists (`nil` / `cons`, map, filter, fold, zip) |

Planned top-level areas (add as they land):

| Area | Purpose |
|------|---------|
| `libs/` | Reusable module libraries |
| `edu/` | Educational exercises and small demos |
| `lectures/` | Code tied to talks or courses |
| `std/` | Standard-library-style reference implementations |

## Layout

```
cmake/CppModules.cmake    # shared import std / LLVM toolchain
libs/type-list/           # type_list module library
scripts/                  # ci, format, compile_commands
.github/                  # CI and repo automation
AGENTS.md                 # agent guide (monorepo + libraries)
CONTRIBUTING.md
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). For **type-list** API and partitions, see [libs/type-list/README.md](libs/type-list/README.md) and [libs/type-list/docs/API.md](libs/type-list/docs/API.md).

## License

See [LICENSE](LICENSE).
