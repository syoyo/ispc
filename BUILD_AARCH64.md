
Assume Ubuntu 16.04 aarch64

```
$ sudo apt install flex bison autoconf automake libtool
$ sudo apt install libtinfo-dev libncurses5-dev
$ sudo apt install zlib1g-dev
```

Install LLVM 4.0.1
(Compiling with LLVM 5.0 > fails due to `dump` API change)


http://releases.llvm.org/download.html

Add path to prebuilt LLVM 4.0.1


Pass `AARCH64_ENABLED=On` to cmake
Set `-DLLVM_DIR` to installed LLVM 4.0.1's cmake dir.

```
$ ./scripts/bootstrap-aarch64-native.sh
$ cd build-aarch64
$ make
```

