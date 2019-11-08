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

# Explaining once again to your compiler where everything is...
INCLUDE_DIRS ?= -I$(PHASAR_INCLUDE_PATH)
INCLUDE_DIRS += -I$(LLVM_INCLUDE_PATH)
INCLUDE_DIRS += -I$(WISE_ENUM_INCLUDE_PATH)

LLVM_FLAGS := `$(LLVM_INSTALL_PREFIX)/bin/llvm-config --cppflags`

IFDSPluginSrc := CastCheck.cxx
IFDSPlugin := $(patsubst %.cxx,%.so,$(IFDSPluginSrc))

all: run
castcheck: CastCheck.cxx CastCheck.h
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) $(LLVM_FLAGS) $(IFDSPluginSrc) -o $(IFDSPlugin)

clean:
	rm -f $(IFDSPlugin)
	rm -f *.dot
	rm -f *.json

run: gobject-example.c.ll.conf castcheck
	$(PHASAR_INSTALL_PREFIX)/build/phasar --config gobject-example.c.ll.conf
