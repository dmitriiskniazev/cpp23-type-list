#!/usr/bin/env bash
# Regenerates compile_commands.json via CMake (preferred for the monorepo).
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

if [[ -z "${CMAKE_CXX_COMPILER:-}" && -x /opt/homebrew/opt/llvm/bin/clang++ ]]; then
    export CMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++
fi

cmake -B build -G Ninja ${CMAKE_CXX_COMPILER:+-DCMAKE_CXX_COMPILER="$CMAKE_CXX_COMPILER"}

if [[ -f build/compile_commands.json ]]; then
    cp build/compile_commands.json compile_commands.json
    echo "wrote compile_commands.json from build/"
else
    echo "build/compile_commands.json not found" >&2
    exit 1
fi
