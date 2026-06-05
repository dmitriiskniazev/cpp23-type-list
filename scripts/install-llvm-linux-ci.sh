#!/usr/bin/env bash
# Install official LLVM Linux binaries under /opt/llvm (CI-friendly layout).
set -euo pipefail

llvm_version="${LLVM_VERSION:-22.1.7}"
install_dir="${LLVM_INSTALL_DIR:-/opt/llvm}"
archive="LLVM-${llvm_version}-Linux-X64.tar.xz"
url="https://github.com/llvm/llvm-project/releases/download/llvmorg-${llvm_version}/${archive}"

curl -fsSL "$url" -o "/tmp/${archive}"
sudo rm -rf "$install_dir"
sudo tar -xJf "/tmp/${archive}" -C /opt
sudo mv "/opt/LLVM-${llvm_version}-Linux-X64" "$install_dir"

if [[ -n "${GITHUB_PATH:-}" ]]; then
    echo "${install_dir}/bin" >> "$GITHUB_PATH"
fi
export PATH="${install_dir}/bin:${PATH}"

if command -v apt-get >/dev/null 2>&1; then
    sudo apt-get update
    sudo apt-get install -y ninja-build
fi

echo "LLVM ${llvm_version} installed at ${install_dir}"
"${install_dir}/bin/clang++" --version
"${install_dir}/bin/clang-format" --version
