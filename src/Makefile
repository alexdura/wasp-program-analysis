CXX := clang++
CC := clang
CXX_FLAGS := -std=c++14
CXX_FLAGS += -Wall
CXX_FLAGS += -Wno-return-type-c-linkage
CXX_FLAGS += -O0
CXX_FLAGS += -fPIC
CXX_FLAGS += -shared
CXX_FLAGS += -g
INCLUDE_DIRS ?= -I/usr/local/include/wise_enum/
LLVM_FLAGS := `llvm-config --cppflags`

IFDSPluginSrc := MyIFDSProblem.cxx
IFDSPlugin := $(patsubst %.cxx,%.so,$(IFDSPluginSrc))

all: ifdsproblem
ifdsproblem: MyIFDSProblem.cxx MyIFDSProblem.h
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) $(LLVM_FLAGS) $(IFDSPluginSrc) -o $(IFDSPlugin)

Test.ll: Test.c
	$(CC) -S -g -emit-llvm Test.c

clean:
	rm -f $(IFDSPlugin)
	rm -f *.dot
	rm -f *.json

run: Test.ll ifdsproblem
	phasar --config Test.c.ll.conf
