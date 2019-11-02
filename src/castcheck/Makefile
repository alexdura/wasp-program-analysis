GLIB_INSTALL_PREFIX ?= /usr/
LLVM_INSTALL_PREFIX ?= /home/noric/Dev/wasp-project-course/wasp-program-analysis/llvm/llvm_install/bin
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
LLVM_FLAGS := `$(LLVM_INSTALL_PREFIX)/llvm-config --cppflags`

IFDSPluginSrc := CastCheck.cxx
IFDSPlugin := $(patsubst %.cxx,%.so,$(IFDSPluginSrc))

all: run
castcheck: CastCheck.cxx CastCheck.h
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) $(LLVM_FLAGS) $(IFDSPluginSrc) -o $(IFDSPlugin)

clean:
	rm -f $(IFDSPlugin)
	rm -f *.dot
	rm -f *.json

run: gobject-example.ll.conf castcheck
	phasar --config gobject-example.c.ll.conf
