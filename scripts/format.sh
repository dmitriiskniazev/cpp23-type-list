#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format not found" >&2
    exit 1
fi

find libs -type f \( -name '*.cpp' -o -name '*.cppm' \) -print0 | xargs -0 clang-format -i

echo "formatted C++ sources under libs/"
