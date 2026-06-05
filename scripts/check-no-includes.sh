#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

violations=0
for dir in modules tests examples; do
    while IFS= read -r -d '' file; do
        if grep -Eq '^[[:space:]]*#include[[:space:]]' "$file"; then
            echo "disallowed #include in $file (use import std; and import type_list;)" >&2
            violations=1
        fi
    done < <(find "$dir" \( -name '*.cpp' -o -name '*.cppm' \) -print0)
done

if [[ "$violations" -ne 0 ]]; then
    exit 1
fi

echo "no #include violations"
