/*
 * bootheader.h
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

#include <stdint.h>

#ifndef __MBRHEADER__
#define __MBRHEADER__

#define MBR_HDR_LEN						(224)
#define ID2M_SIZE						(4*7) 
#define MAGIC1							(0x01100000)
#define MAGIC2							(0x01101000)
#define SEPARATOR						(0x0)

typedef struct {
	uint8_t hdr[7];	    //Header: $OS$\0\0\1
	uint8_t xor56;     //XOR of first 56 bytes without this one
	char id2[ID2M_SIZE]; //28 bytes: 03 01 68 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
} mainheader ;

typedef struct {
	uint32_t start_s; //First sector of boot image
	uint32_t magic1;  //Magic number 1
	uint32_t magic2;  //Magic number 2
	uint32_t sectors_t; //Total image length in 512 sectors - 1
	uint32_t image_type;//Image type 0xd - recovery, 0x1 - boot, 0xf - fastboot
	uint32_t separator; //0x0
} hdr_ent;

/* Sanity check for struct size */
typedef char zz[(sizeof(mainheader) == 9*4) ? 1 : -1];
typedef char zzz[(sizeof(hdr_ent) == 6*4) ? 1 : -1];

#endif
