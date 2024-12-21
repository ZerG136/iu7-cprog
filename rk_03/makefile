SHELL := /bin/bash

CC := gcc
CFLAGS := -c -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -O2 -g0
LDFLAGS := -lm
DEPFLAGS := -MMD -MF

SRCS := $(wildcard ./*.c)
OBJS := $(patsubst ./%.c, ./%.o, $(SRCS))

app.exe: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

./%.o : ./%.c
	$(CC) $(CFLAGS) $(DEPFLAGS) $(@:.0=.d) -c $< -o $@

.PHONY: build run clean

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

build : app.exe

run : build
	./app.exe

clean:
	@rm -f ./*.o ./*.exe
