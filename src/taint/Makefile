include ../../variables.mk
CXX := clang++
CC := clang
CXX_FLAGS := -std=c++14
CXX_FLAGS += -Wall
CXX_FLAGS += -Wno-return-type-c-linkage
CXX_FLAGS += -O0
CXX_FLAGS += -fPIC
CXX_FLAGS += -shared
CXX_FLAGS += -g
INCLUDE_DIRS ?= -I$(WISE_ENUM_INCLUDE_PATH)
INCLUDE_DIRS += -I$(PHASAR_INCLUDE_PATH)
INCLUDE_DIRS += -I$(LLVM_INCLUDE_PATH)

LLVM_FLAGS := $(shell $(LLVM_INSTALL_PREFIX)/bin/llvm-config --cppflags)

IFDSPluginSrc := MyIFDSProblem.cxx
IFDSPlugin := $(patsubst %.cxx,%.so,$(IFDSPluginSrc))

all: run
ifdsproblem: MyIFDSProblem.cxx MyIFDSProblem.h
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) $(LLVM_FLAGS) $(IFDSPluginSrc) -o $(IFDSPlugin)

Test.ll: Test.c
	$(CC) -S -emit-llvm Test.c

clean:
	rm -f $(IFDSPlugin)
	rm -f *.dot
	rm -f *.json

run: Test.ll ifdsproblem
	phasar --config Test.c.ll.conf
