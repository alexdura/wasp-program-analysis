GLIB_INSTALL_PREFIX ?= /usr/
LLVM_INSTALL_PREFIX ?= /home/noric/Dev/wasp-project-course/wasp-program-analysis/llvm/llvm_install/bin
PHASAR_INSTALL_PREFIX ?= /home/noric/Dev/wasp-project-course/wasp-program-analysis/phasar

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
INCLUDE_DIRS ?= -I$(PHASAR_INSTALL_PREFIX)/external/
INCLUDE_DIRS += -I$(PHASAR_INSTALL_PREFIX)/external/wise_enum
INCLUDE_DIRS += -I$(PHASAR_INSTALL_PREFIX)/include
# Let's play hide and seek with the files
INCLUDE_DIRS += -I$(PHASAR_INSTALL_PREFIX)/external/json/include/
INCLUDE_DIRS += -I$(PHASAR_INSTALL_PREFIX)/external/json/include/nlohmann

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

run: gobject-example.c.ll.conf castcheck
	phasar --config gobject-example.c.ll.conf
