include ../../variables.mk

CXX := clang++
CC := clang

TEST_SRCS := $(wildcard *.c)
TEST_PROGRAMS := $(patsubst %.c,%,$(TEST_SRCS))

INCLUDE_DIRS := -I$(GLIB_INCLUDE_PATH) -I$(GLIB_CONFIG_INCLUDE_PATH)
LIB_DIRS := -L$(GLIB_LIB_PATH)


CFLAGS := -Wall -lglib-2.0 -lgobject-2.0 $(INCLUDE_DIRS) $(LIB_DIRS)

all : $(patsubst %.vala,%.c,$(wildcard *.vala))

%.c: %.vala
	valac --ccode $^ -o $@

%.ll : %.c
	$(CC) $(CFLAGS) -S -emit-llvm -o $@ $^

clean:
	rm *.c
	rm *.ll

run: example.ll
	LD_LIBRARY_PATH=$(PHASAR_LIBRARY_PATH) $(PHASAR_BINARY_PATH)/phasar --config example.c.ll.conf
