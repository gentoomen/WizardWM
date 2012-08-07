CFLAGS+=-std=c99 -Wall -pedantic -O2 -ggdb -D_GNU_SOURCE $(shell pkg-config --cflags xcb)
LDFLAGS+=$(shell pkg-config --libs xcb)
MAIN=wizwm
SRC=screen.c wizwm.c
OBJ=$(SRC:.c=.o)
CC?=gcc
DESTDIR?=/
PREFIX?=/usr/local

all: $(SRC) $(MAIN)

$(MAIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(MAIN) $(OBJ)

install: $(MAIN)
	mkdir -p $(DESTDIR)/$(PREFIX)/bin
	cp -v $(MAIN) $(DESTDIR)/$(PREFIX)/bin/$(MAIN)

.PHONY: clean install
