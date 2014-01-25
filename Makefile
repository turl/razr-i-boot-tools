CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -D_BSD_SOURCE -march=i586 -m32 -ffunction-sections -fdata-sections 
LDFLAGS=$(CFLAGS) -march=i586 -m32 -ffunction-sections -fdata-sections 
DUMPFLAGS=-dead-strip -dead_strip_dylibs -static 

.PHONY: clean

all: gxi_pack gxi_unpack gxi_dump_images gxi_dump_images_s

clean:
	rm -f *.o gxi_pack gxi_unpack gxi_dump_images gxi_dump_images_s

gxi_pack: gxi_pack.o
	$(CC) -o $@ $< $(CFLAGS)

gxi_unpack: gxi_unpack.o
	$(CC) -o $@ $< $(CFLAGS) 

gxi_dump_images_pc.o: gxi_dump_images.c
	$(CC) -c -o $@ $< $(CFLAGS) -DPC

gxi_dump_images_s: gxi_dump_images.o
	$(CC) -o $@ $< $(CFLAGS)

gxi_dump_images: gxi_dump_images_pc.o
	$(CC) -o $@ $< $(CFLAGS) $(DUMPFLAGS)
	strip $@
