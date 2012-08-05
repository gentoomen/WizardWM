CFLAGS+=-std=c99 -Wall -pedantic -O2 -ggdb -D_GNU_SOURCE
LIBS=-lxcb
CC?=gcc
BINNAME=wizwm

${BINNAME}: ${BINNAME}.c
	${CC} $< ${CFLAGS} -o $@ ${LIBS}

clean:
	-rm -f $(OBJECTS) ${BINNAME}

install: trog
	cp -v ${BINNAME} /usr/bin/

.PHONY: clean
