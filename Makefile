CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -D_BSD_SOURCE

ifneq ($(LENOVO_IMAGE),)
	CFLAGS+=-DLENOVO_IMAGE=1
endif

ifneq ($(DELL_IMAGE),)
	CFLAGS+=-DDELL_IMAGE=1
endif

.PHONY: clean

all: pack unpack

clean:
	rm -f *.o pack unpack

pack: pack.o
	$(CC) -o $@ $< $(CFLAGS)

unpack: unpack.o
	$(CC) -o $@ $< $(CFLAGS)
