# set this variable to the location where YOUR glib headers are installed
GLIB_INSTALL_PREFIX ?= /work/courses/project_course/glib/install/usr/local/

CXX := clang++
CC := clang

TEST_SRCS := $(wildcard *.c)
TEST_OBJS := $(patsubst %.c,%.o,$(TEST_SRCS))
INCLUDES := $(wildcard *.h)

INCLUDE_DIRS := -I$(GLIB_INSTALL_PREFIX)/include/glib-2.0/ -I$(GLIB_INSTALL_PREFIX)/lib/x86_64-linux-gnu/glib-2.0/include/
LIB_DIRS := -L$(GLIB_INSTALL_PREFIX)/lib/x86_64-linux-gnu/


CFLAGS := -g -Wall -lglib-2.0 -lgobject-2.0 $(INCLUDE_DIRS) $(LIB_DIRS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

class-example : $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# class-example.ll : $(TEST_SRCS)
# 	$(CC) -S --emit-llvm $(CFLAGS) -o $@ $^
