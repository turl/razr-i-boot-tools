/*
 * pack.c
 *
 * Copyright 2012 Emilio López <turl@tuxfamily.org>
 * Modified for ZTE GXI by Pavel Moravec, 2014 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <endian.h>
#include <string.h>

#include "bootheader.h"

char get_image_code(char image_t) {
  switch(image_t) {
    case 'r':
    case 'R':
		return T_RECOVERY;
    case 'b':
    case 'B':
		return T_BOOT;
    case 'f':
    case 'F':
	return T_FASTBOOT;
    default:
        return 0;
  }
}

int main(int argc, char *argv[])
{
	int img_type=0;
	char *origin;
	char *bzImage;
	char *ramdisk;
	char *output;
	FILE *forigin;
	FILE *foutput;
	FILE *fbzImage;
	FILE *framdisk;
	struct stat st;
	uint32_t tmp, tmp2, pad;
	char buf[BUFSIZ];
	size_t size;
	struct bootheader *file;

	if (argc != 5 && argc != 6)
		ERROR("Usage: %s <valid image> <bzImage> <ramdisk> <output> [type]\nwhere type: is r - recovery, b - boot, f - fastboot\n", argv[0]);

	origin = argv[1];
	bzImage = argv[2];
	ramdisk = argv[3];
	output = argv[4];
	if (argc == 6) { img_type = get_image_code(argv[5][0]); }

	forigin = fopen(origin, "r");
	fbzImage = fopen(bzImage, "r");
	framdisk = fopen(ramdisk, "r");
	foutput = fopen(output, "w");
	if (!forigin || !foutput)
		ERROR("ERROR: failed to open origin or output image\n");

	/* Allocate memory and copy bootstub to it */
	file = calloc(sizeof(struct bootheader), sizeof(char));
	if (file == NULL)
		ERROR("ERROR allocating memory\n");

	if (fread(file, sizeof(struct bootheader), 1, forigin) != 1)
		ERROR("ERROR reading bootstub\n");
		
	checkBootHeader(file);

	/* Figure out the bzImage size and set it */
	if (stat(bzImage, &st) == 0) {
		tmp2 = tmp = st.st_size;
		file->bzImageSize = htole32(tmp);
	} else
		ERROR("ERROR reading bzImage size\n");

	/* Figure out the ramdisk size and set it */
	if (stat(ramdisk, &st) == 0) {
		tmp = st.st_size;
		tmp2 += tmp;
		file->initrdSize = htole32(tmp);
	} else
		ERROR("ERROR reading ramdisk\n");

	/* Calculate padding */
	tmp2+= sizeof(struct bootheader);
	if (tmp2 % SECTOR) { 
		pad = SECTOR - (tmp2 % SECTOR);
		tmp2 += pad;
	}
	
	/* Update OS header */
	file->sectors_t = htole32(tmp2 / 512 - 1);
	if (img_type != 0) { file->image_type = img_type; }
    file->xor56 = calc_sum(file);

	/* Write the patched bootstub to the new image */
	if (fwrite(file, sizeof(struct bootheader), 1, foutput) != 1)
		ERROR("ERROR writing image\n");

	/* Then copy the new bzImage */
	while ((size = fread(buf, 1, BUFSIZ, fbzImage))) {
		if (fwrite(buf, 1, size, foutput) != size) ERROR("ERROR writing output image\n");			
	}

	/* Then copy the ramdisk */
	while ((size = fread(buf, 1, BUFSIZ, framdisk))) {
		if (fwrite(buf, 1, size, foutput) != size) ERROR("ERROR writing output image\n");			
	}
	
	if (pad != 0) {
		memset(buf, 0xff, pad);
		if (fwrite(buf, pad, 1, foutput) != 1) ERROR("ERROR writing output image\n");			
	}

	return 0;
}
