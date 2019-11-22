include ../../variables.mk

CXX := $(LLVM_INSTALL_PREFIX)/bin/clang++
CC := $(LLVM_INSTALL_PREFIX)/bin/clang

TEST_SRCS := $(wildcard *.c)
TEST_OBJS := $(patsubst %.c,%.o,$(TEST_SRCS))
TEST_LLS := $(patsubst %.c,%.ll,$(TEST_SRCS))
INCLUDES := $(wildcard *.h)

INCLUDE_DIRS := -I$(GLIB_INCLUDE_PATH) -I$(GLIB_CONFIG_INCLUDE_PATH)
LIB_DIRS := -L$(GLIB_LIB_PATH)

CFLAGS := -Wall -lglib-2.0 -lgobject-2.0 $(INCLUDE_DIRS) $(LIB_DIRS)

all: run

run : fakesrc-minimal.linked.config fakesrc-minimal.linked.ll
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(PHASAR_BINARY_PATH)/phasar --config=$<
