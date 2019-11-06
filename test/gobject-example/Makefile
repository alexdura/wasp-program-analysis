# set this variable to the location where YOUR glib headers are installed
# GLIB_INSTALL_PREFIX ?= /work/courses/project_course/glib/install/usr/local
GLIB_INSTALL_PREFIX ?= /usr/

CXX := clang++
CC := clang

TEST_SRCS := $(wildcard *.c)
TEST_PROGRAMS := $(patsubst %.c,%,$(TEST_SRCS))

INCLUDE_DIRS := -I$(GLIB_INSTALL_PREFIX)/include/glib-2.0/ -I$(GLIB_INSTALL_PREFIX)/lib/x86_64-linux-gnu/glib-2.0/include/
LIB_DIRS := -L$(GLIB_INSTALL_PREFIX)/usr/local/lib/x86_64-linux-gnu/


CFLAGS := -Wall -lglib-2.0 -lgobject-2.0 $(INCLUDE_DIRS) $(LIB_DIRS)

all : $(TEST_PROGRAMS)

% : %.c
	$(CC) $(CFLAGS) -o $@ $^

%.ll : %.c
	$(CC) $(CFLAGS) -S -emit-llvm -o $@ $^

clean:
	rm gobject-example
