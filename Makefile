## Manual Parameters
CC := arm-linux-gnueabi-gcc

## Automatic Parameters (DO NOT TOUCH)
CROSS_COMPILE := $(shell uname -n)

ifneq ($(CROSS_COMPILE), ev3dev)
CC := docker exec compiler $(CC)
EXEC := docker exec compiler qemu-arm-static
endif

## Rules

ifeq ($(CROSS_COMPILE), ev3dev)
default: all
else
default: run_docker all
endif

all: hello.o

hello.o: hello.c
	$(CC) -I/usr/local/include hello.c -o hello.o /usr/local/lib/libev3dev-c.a

.PONEY: clean run_docker stop_docker

run_docker: 
	./setup_docker.sh

stop_docker:
	docker stop compiler

clean:
	-rm -f *.o

