
Assume Ubuntu 16.04 aarch64

```
$ sudo apt install flex bison autoconf automake libtool
```

Install armhf(arm 32bit) include files(required to compile 32bit builtin library)

```
$ sudo apt install libc6-dev-armhf-cross
```

Install LLVM 4.0.1
(Compiling with LLVM 5.0 > fails due to `dump` API change)


http://releases.llvm.org/download.html

Add path to prebuilt LLVM 4.0.1


Pass `AARCH64_ENABLED=On` to cmake

```
$ ./scripts/bootstrap-aarch64-native.sh
$ cd build-aarch64
$ make
```

