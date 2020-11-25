## Manual Parameters

CC := arm-linux-gnueabi-gcc

## Automatic Parameters (DO NOT TOUCH)

CROSS_COMPILE := $(shell uname -n)

ifneq ($(CROSS_COMPILE), ev3dev)
CC := docker exec compiler $(CC)
EXEC := docker exec compiler qemu-arm-static
endif

## Rules

default: compile

all: hello.o

hello.o: hello.c
	$(CC) -I/usr/local/include hello.c -o hello.o /usr/local/lib/libev3dev-c.a

run: compile
	$(EXEC) ./hello.o

## PONEY rules

.PONEY: clean run_docker stop_docker

run_docker: 
	./setup_docker.sh

stop_docker:
	docker stop compiler

clean:
	-rm -f *.o

## Generated Rules

ifeq ($(CROSS_COMPILE), ev3dev)
compile: all
else
compile: run_docker all
endif

