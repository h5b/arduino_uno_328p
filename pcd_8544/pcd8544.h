/*
 * Copyright (c) 2012 Sebastian Trahm
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _PCD8544_H_
#define _PCD8544_H_

#define PCD8544_WIDTH		84
#define PCD8544_HEIGHT		48

#define PCD8544_RESET		PB0
#define PCD8544_DATA		PB1
#define PCD8544_SCE		PB2
#define PCD8544_DDR		DDRB
#define PCD8544_PORT		PORTB

/* PCD8544 - Commands */
#define PCD8544_EXTENDED_CMD	0x21
#define PCD8544_STANDARD_CMD	0x20
#define PCD8544_NORMAL_MODE	0x0C
#define PCD8544_INVERT_MODE	0x0D

/* PCD8544 - Settings */
#define PCD8544_VOP		0xA8
#define PCD8544_TEMP_COEFF	0x04
#define PCD8544_BIAS_MODE	0x16

void pcd8544BigNumber(uint8_t, uint8_t, char);
void pcd8544Clear(void);
void pcd8544Init(void);
void pcd8544SetContrast(uint8_t);
void pcd8544SetXY(uint8_t, uint8_t);
void pcd8544SmallChar(char);
void pcd8544SmallStr(const char*);

#endif /* _PCD8544_H_ */
