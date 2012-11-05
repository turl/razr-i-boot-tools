CC=gcc

.PHONY: clean

all: pack unpack

clean:
	rm *.o pack unpack

pack: pack.o
	$(CC) -o $@ $<

unpack: unpack.o
	$(CC) -o $@ $<
