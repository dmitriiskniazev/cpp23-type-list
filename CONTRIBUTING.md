# Contributing

Thanks for improving **type-list**. This library is compile-time only: correctness is enforced with `static_assert` and type aliases.

## Prerequisites

- **Clang 19+** with libc++ `import std` (Homebrew LLVM on macOS; [apt.llvm.org](https://apt.llvm.org/) on Linux)
- **CMake 3.28+** and **Ninja**
- **clang-format 22+** (match Homebrew LLVM / apt.llvm.org LLVM 22 used in CI)

Apple Clang and GCC are not supported.

## Local workflow

```bash
# One-shot checks (format, no #include, configure, build, test)
./scripts/ci.sh

# Or step by step:
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
./scripts/format.sh          # after editing C++ sources
```

Optional git hooks:

```bash
pip install pre-commit   # or: brew install pre-commit
./scripts/install-hooks.sh
pre-commit run --all-files
```

## Repository automation

After pushing, GitHub Actions run build/test on macOS and Ubuntu, check formatting, and sync labels. See `.github/workflows/`.

Recommended branch protection on `master`:

- Require status checks: **Format**, **Build (macos-latest)**, **Build (ubuntu-latest)**
- Require pull request reviews (optional for solo maintenance)

## Adding an operation

Follow [AGENTS.md](AGENTS.md). In short:

1. Add `modules/type_list/<op>.cppm`
2. `export import :<op>;` in `modules/type_list.cppm`
3. Register in `CMakeLists.txt` (`TYPE_LIST_TESTS`, `TYPE_LIST_EXAMPLES`)
4. Update [docs/API.md](docs/API.md)
5. Run `./scripts/ci.sh`

## Pull requests

- Keep diffs focused; one partition per feature when possible
- Match naming in [README.md](README.md) (`*_t`, lowercase concepts, PascalCase test markers)
- Do not use `#include` in `modules/`, `tests/`, or `examples/`
- CI must pass on macOS and Ubuntu (see [.github/workflows/ci.yml](.github/workflows/ci.yml))

## Questions

Open a [discussion](https://github.com/dmitriiskniazev/type-list/discussions) or an issue using the templates in `.github/ISSUE_TEMPLATE/`.
