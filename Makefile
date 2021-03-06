SHELL = /bin/sh

CC=gcc
CFLAGS = -Wall
LIBS = -lXtst -lX11 -lresolv
ALL_CFLAGS = $(CFLAGS)

HEADERS = $(shell find src/ -name '*.h')
SRCS = $(shell find src/ -name '*.c')
OBJS = $(SRCS:.c=.o)

MAIN = keylogger

.PHONY: debug depend clean

all: $(MAIN)
	@echo Done.

$(MAIN): $(OBJS)
	$(CC) $(ALL_CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS) $(MAIN)

depend: $(SRCS)
	makedepend -w70 -Y $^

debug: CFLAGS += -DDEBUG -g
debug: all
