LLVM_CONFIG=/Volumes/SSD/data/clang+llvm-3.3-x86_64-apple-darwin12/bin/llvm-config
CXXFLAGS=$(shell $(LLVM_CONFIG) --cxxflags)
LLVM_LIBS=$(shell $(LLVM_CONFIG) --ldflags --libs irreader jit interpreter nativecodegen)

all:
	ispc --emit-llvm shader.ispc -h shader_ispc.h -o shader.bc
	g++-4.8 $(CXXFLAGS) main.cc $(LLVM_LIBS)
