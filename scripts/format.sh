#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format not found" >&2
    exit 1
fi

format_dir() {
    local dir="$1"
    find "$dir" \( -name '*.cpp' -o -name '*.cppm' \) -print0 | xargs -0 clang-format -i
}

format_dir modules
format_dir tests
format_dir examples

echo "formatted modules/, tests/, examples/"
