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

all: test test.ll

%.o : %.c $(INCLUDES)
	LD_LIBRARY_PATH=$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(CC) $(CFLAGS) -c -o $@ $<

%.ll : %.c $(INCLUDES)
	LD_LIBRARY_PATH=$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(CC) $(CFLAGS) -g -S -emit-llvm -o $@ $<

test : $(TEST_OBJS)
	LD_LIBRARY_PATH=$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(CC) $(CFLAGS) -o $@ $^

test.bc : $(TEST_LLS)
	LD_LIBRARY_PATH=$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(LLVM_INSTALL_PREFIX)/bin/llvm-link $^ -o $@

test.ll : test.bc
	LD_LIBRARY_PATH=$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(LLVM_INSTALL_PREFIX)/bin/llvm-dis test.bc

clean :
	rm $(TEST_OBJS)
	rm $(TEST_LLS)
	rm test
	rm test.ll
	rm test.bc

run : test.c.ll.conf test.ll
	LD_LIBRARY_PATH=$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(PHASAR_BINARY_PATH)/phasar --config=$<
