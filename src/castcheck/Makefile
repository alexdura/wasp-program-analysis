GLIB_INSTALL_PREFIX ?= /usr/
CXX := clang++
CC := clang
CXX_FLAGS := -std=c++14
CXX_FLAGS += -Wall
CXX_FLAGS += -Wno-return-type-c-linkage
CXX_FLAGS += -O0
CXX_FLAGS += -fPIC
CXX_FLAGS += -shared
CXX_FLAGS += -g
INCLUDE_DIRS ?= -I/include/wise_enum/
LLVM_FLAGS := `llvm-config --cppflags`

IFDSPluginSrc := CastCheck.cxx
IFDSPlugin := $(patsubst %.cxx,%.so,$(IFDSPluginSrc))

all: run
castcheck: Castcheck.cxx Castcheck.h
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) $(LLVM_FLAGS) $(IFDSPluginSrc) -o $(IFDSPlugin)

Test.ll: Test.c
	$(CC) -S -g -emit-llvm Test.c

clean:
	rm -f $(IFDSPlugin)
	rm -f *.dot
	rm -f *.json

run: Test.ll castcheck
	phasar --config Test.c.ll.conf
