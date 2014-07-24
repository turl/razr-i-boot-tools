/*
 * bootheader.h
 *
 * Copyright 2012 Emilio López <turl@tuxfamily.org>
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

#ifndef __BOOTHEADER__
#define __BOOTHEADER__

#ifdef LENOVO_IMAGE
#define HEAD_PADDING						(0x3e0) /* Lenovo K900 */
#define BOOTSTUBSTACK_SIZE					(0x1000)
#elif DELL_IMAGE
#define HEAD_PADDING						(0x3e0) /* Dell Venue 8 */
#define BOOTSTUBSTACK_SIZE					(0x2000)
#else
#define HEAD_PADDING						(0) /* Motorola RAZR i */
#define BOOTSTUBSTACK_SIZE					(0x1000)
#endif

#define CMDLINE_SIZE   						(0x400)
#define PADDING1_SIZE						(0x1000-0x410)
#define CMDLINE_END						(HEAD_PADDING+CMDLINE_SIZE)

struct bootheader {
#if HEAD_PADDING > 0
	char padding0[HEAD_PADDING];
#endif
	char cmdline[CMDLINE_SIZE];
	uint32_t bzImageSize;
	uint32_t initrdSize;
	uint32_t SPIUARTSuppression;
	uint32_t SPIType;
	char padding1[PADDING1_SIZE];
	char bootstubStack[BOOTSTUBSTACK_SIZE];
};

/* Sanity check for struct size */
typedef char z[(sizeof(struct bootheader) == 0x1000 + BOOTSTUBSTACK_SIZE + HEAD_PADDING) ? 1 : -1];

#endif
