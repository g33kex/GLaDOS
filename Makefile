## Manual Parameters

CC := arm-linux-gnueabi-gcc
FLAGS := -Wall

SRCDIR := src
TRGDIR := bin
INCDIR := include

INSTDIR := /home/robot/bin

TARGET := GLaDOS

LIBS += /usr/local/lib/libev3dev-c.a

## Automatic Parameters (DO NOT TOUCH)

OBJECTS := $(patsubst $(SRCDIR)/%.c,$(TRGDIR)/%.o,$(wildcard $(SRCDIR)/*.c))
TARGET := $(TRGDIR)/$(TARGET)

UNAME := $(shell uname -n)

ifneq ($(UNAME), ev3dev)
CC := docker exec compiler $(CC)
EXEC := docker exec compiler qemu-arm-static
INSTALL := scp $(TARGET) robot:$(INSTDIR) 
else
INSTALL := cp $(TARGET) $(INSTDIR)
endif

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

## Rules

default: compile

$(TARGET): $(OBJECTS)
	$(CC) -lm -o $@ $^ $(LIBS)

mkdir: 
	@mkdir -p $(TRGDIR)

run: compile
	@-$(EXEC) $(TARGET) $(RUN_ARGS) || true

install: compile
	$(INSTALL) 

## Automatic rules

$(TRGDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	$(CC) $(FLAGS) -I/usr/local/include -c $< -o $@ -I$(INCDIR) 

$(TRGDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(FLAGS) -I/usr/local/include -c $< -o $@ -I$(INCDIR) 

## PONEY rules

.PONEY: clean run_docker stop_docker

run_docker: 
	@-./setup_docker.sh

stop_docker:
	@-docker stop compiler

clean:
	-rm -rf $(TRGDIR)

## Generated Rules

ifeq ($(UNAME), ev3dev)
compile: mkdir $(TARGET)
else
compile: mkdir run_docker $(TARGET)
endif
