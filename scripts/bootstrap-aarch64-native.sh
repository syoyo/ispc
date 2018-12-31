#!/bin/bash

rm -rf build-aarch64

# set path to llvm-4.0.1 in CMAKE_MODULE_PATH
# cxxflags : for sys/cdefs.h

CXX=g++ CC=gcc cmake -Bbuild-aarch64 -H. -DAARCH64_ENABLED=On \
  -DCMAKE_C_FLAGS="-I/usr/include/aarch64-linux-gnu" \
  -DCMAKE_CXX_FLAGS="-I/usr/include/aarch64-linux-gnu" \
  -DISPC_INCLUDE_TESTS=OFF \
  -DISPC_INCLUDE_UTILS=OFF \
  -DLLVM_DIR=$HOME/local/clang+llvm-4.0.1-aarch64-linux-gnu/lib/cmake/llvm \
  -DCMAKE_INSTALL_PREFIX=$HOME/local/aarch64/ispc 
