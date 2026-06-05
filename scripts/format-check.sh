#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format not found" >&2
    exit 1
fi

check_dir() {
    local dir="$1"
    local failed=0
    while IFS= read -r -d '' file; do
        if ! clang-format --dry-run --Werror "$file" >/dev/null 2>&1; then
            echo "format check failed: $file" >&2
            failed=1
        fi
    done < <(find "$dir" \( -name '*.cpp' -o -name '*.cppm' \) -print0)
    return "$failed"
}

failed=0
check_dir modules || failed=1
check_dir tests || failed=1
check_dir examples || failed=1

if [[ "$failed" -ne 0 ]]; then
    echo "Run ./scripts/format.sh to fix formatting." >&2
    exit 1
fi

echo "format check passed"
