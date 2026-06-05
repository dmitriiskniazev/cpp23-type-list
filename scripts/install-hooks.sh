#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

if ! command -v pre-commit >/dev/null 2>&1; then
    echo "pre-commit not found. Install with: pip install pre-commit  (or brew install pre-commit)" >&2
    exit 1
fi

pre-commit install
echo "pre-commit hooks installed"
