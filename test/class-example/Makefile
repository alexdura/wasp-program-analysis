include ../../variables.mk

CXX := clang++
CC := clang

TEST_SRCS := $(wildcard *.c)
TEST_OBJS := $(patsubst %.c,%.o,$(TEST_SRCS))
INCLUDES := $(wildcard *.h)

INCLUDE_DIRS := -I$(GLIB_INCLUDE_PATH)
INCLUDE_DIRS += -I$(GLIB_CONFIG_INCLUDE_PATH)
LIB_DIRS := -L$(GLIB_LIB_PATH)

CFLAGS := -g -Wall -lglib-2.0 -lgobject-2.0 $(INCLUDE_DIRS) $(LIB_DIRS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

class-example : $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

class-example.ll : $(TEST_SRCS)
	$(CC) -S -emit-llvm $(CFLAGS) $^
	#
# class-example.ll : $(TEST_SRCS)
# 	$(CC) -S --emit-llvm $(CFLAGS) -o $@ $^
#
clean:
	rm *.o
	rm class-example
