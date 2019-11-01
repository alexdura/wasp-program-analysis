# set this variable to the location where YOUR glib headers are installed
GLIB_INSTALL_PREFIX ?= /work/courses/project_course/glib/install/usr/local

CXX := clang++
CC := clang

TEST_SRCS := $(wildcard *.c)
TEST_OBJS := $(patsubst %.c,%.o,$(TEST_SRCS))
TEST_LLS := $(patsubst %.c,%.ll,$(TEST_SRCS))
INCLUDES := $(wildcard *.h)

INCLUDE_DIRS := -I$(GLIB_INSTALL_PREFIX)/include/glib-2.0/ -I$(GLIB_INSTALL_PREFIX)/lib/x86_64-linux-gnu/glib-2.0/include/
LIB_DIRS := -L$(GLIB_INSTALL_PREFIX)/lib/x86_64-linux-gnu/


CFLAGS := -g -Wall -lglib-2.0 -lgobject-2.0 $(INCLUDE_DIRS) $(LIB_DIRS)

all: test test.ll

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

%.ll : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -S -emit-llvm -o $@ $<

test : $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test.bc : $(TEST_LLS)
	llvm-link $^ -o $@

test.ll : test.bc
	llvm-dis test.bc

clean :
	rm $(TEST_OBJS)
	rm $(TEST_LLS)
	rm test
	rm test.ll
	rm test.bc
