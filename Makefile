CFLAGS := -Wall -Werror
ifeq ($(DEBUG),1)
	CFLAGS := $(CFLAGS) -g -Og
else
	CFLAGS := $(CFLAGS) -O3
endif

TEST_ARRAY_SIZE := 100

all: build

build:
	gcc -o push_swap $(CFLAGS) push_swap.c stack.c

test: build
	./test.sh $(TEST_ARRAY_SIZE)

clean:
	rm push_swap

.PHONY: all build test clean
