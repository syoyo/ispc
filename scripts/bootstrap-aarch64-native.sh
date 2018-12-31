#!/bin/bash

rm -rf build-aarch64

# set path to llvm-4.0.1 in CMAKE_MODULE_PATH
# cxxflags : for sys/cdefs.h

cmake -Bbuild-aarch64 -H. -DAARCH64_ENABLED=On \
  -DCMAKE_C_FLAGS="-I/usr/include/aarch64-linux-gnu" \
  -DCMAKE_CXX_FLAGS="-I/usr/include/aarch64-linux-gnu" \
  -DCMAKE_MDULE_PATH=$HOME/local/aarch64/clang+llvm-4.0.1-aarch64-linux-gnu/lib/cmake/llvm \
  -DCMAKE_INSTALL_PREFIX=$HOME/local/aarch64/ispc 
