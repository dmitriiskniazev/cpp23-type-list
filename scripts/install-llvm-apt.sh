#!/usr/bin/env bash
# Install LLVM ${LLVM_VERSION:-22} from apt.llvm.org on Debian/Ubuntu.
set -euo pipefail

llvm_version="${LLVM_VERSION:-22}"
codename="$(. /etc/os-release && echo "${VERSION_CODENAME}")"

wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | sudo tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
echo "deb http://apt.llvm.org/${codename}/ llvm-toolchain-${codename}-${llvm_version} main" | sudo tee "/etc/apt/sources.list.d/llvm-${llvm_version}.list"
sudo apt-get update
sudo apt-get install -y \
    "clang-${llvm_version}" \
    "clang-format-${llvm_version}" \
    "libc++-${llvm_version}-dev" \
    "libc++abi-${llvm_version}-dev" \
    ninja-build \
    cmake

sudo ln -sf "/usr/bin/clang++-${llvm_version}" /usr/bin/clang++
sudo ln -sf "/usr/bin/clang-format-${llvm_version}" /usr/bin/clang-format

echo "LLVM ${llvm_version} installed (clang++, clang-format)"
