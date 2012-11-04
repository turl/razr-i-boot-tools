CC=gcc

.PHONY: clean

all: pack

clean:
	rm *.o pack

pack: pack.o
	$(CC) -o $@ $<
