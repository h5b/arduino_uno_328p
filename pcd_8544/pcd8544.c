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

#include <avr/pgmspace.h>

#include "pcd8544.h"
#include "sw_spi/spi.h"

#define SFONT_MAX_X	5

const unsigned char
PROGMEM SmallFont[][5] =
{
	{0x00, 0x00, 0x00, 0x00, 0x00}, /*   */
	{0x00, 0x00, 0x5f, 0x00, 0x00}, /* ! */
	{0x00, 0x07, 0x00, 0x07, 0x00}, /* " */
	{0x14, 0x7f, 0x14, 0x7f, 0x14}, /* # */
	{0x24, 0x2a, 0x7f, 0x2a, 0x12}, /* $ */
	{0x23, 0x13, 0x08, 0x64, 0x62}, /* % */
	{0x36, 0x49, 0x55, 0x22, 0x50}, /* & */
	{0x00, 0x05, 0x03, 0x00, 0x00}, /* ' */
	{0x00, 0x1c, 0x22, 0x41, 0x00}, /* ( */
	{0x00, 0x41, 0x22, 0x1c, 0x00}, /* ) */
	{0x14, 0x08, 0x3e, 0x08, 0x14}, /* * */
	{0x08, 0x08, 0x3e, 0x08, 0x08}, /* + */
	{0x00, 0x50, 0x30, 0x00, 0x00}, /* , */
	{0x08, 0x08, 0x08, 0x08, 0x08}, /* - */
	{0x00, 0x60, 0x60, 0x00, 0x00}, /* . */
	{0x20, 0x10, 0x08, 0x04, 0x02}, /* / */
	{0x3e, 0x51, 0x49, 0x45, 0x3e}, /* 0 */
	{0x00, 0x42, 0x7f, 0x40, 0x00}, /* 1 */
	{0x42, 0x61, 0x51, 0x49, 0x46}, /* 2 */
	{0x21, 0x41, 0x45, 0x4b, 0x31}, /* 3 */
	{0x18, 0x14, 0x12, 0x7f, 0x10}, /* 4 */
	{0x27, 0x45, 0x45, 0x45, 0x39}, /* 5 */
	{0x3c, 0x4a, 0x49, 0x49, 0x30}, /* 6 */
	{0x01, 0x71, 0x09, 0x05, 0x03}, /* 7 */
	{0x36, 0x49, 0x49, 0x49, 0x36}, /* 8 */
	{0x06, 0x49, 0x49, 0x29, 0x1e}, /* 9 */
	{0x00, 0x36, 0x36, 0x00, 0x00}, /* : */
	{0x00, 0x56, 0x36, 0x00, 0x00}, /* ; */
	{0x08, 0x14, 0x22, 0x41, 0x00}, /* < */
	{0x14, 0x14, 0x14, 0x14, 0x14}, /* = */
	{0x00, 0x41, 0x22, 0x14, 0x08}, /* > */
	{0x02, 0x01, 0x51, 0x09, 0x06}, /* ? */
	{0x32, 0x49, 0x79, 0x41, 0x3e}, /* @ */
	{0x7e, 0x11, 0x11, 0x11, 0x7e}, /* A */
	{0x7f, 0x49, 0x49, 0x49, 0x36}, /* B */
	{0x3e, 0x41, 0x41, 0x41, 0x22}, /* C */
	{0x7f, 0x41, 0x41, 0x22, 0x1c}, /* D */
	{0x7f, 0x49, 0x49, 0x49, 0x41}, /* E */
	{0x7f, 0x09, 0x09, 0x09, 0x01}, /* F */
	{0x3e, 0x41, 0x49, 0x49, 0x7a}, /* G */
	{0x7f, 0x08, 0x08, 0x08, 0x7f}, /* H */
	{0x00, 0x41, 0x7f, 0x41, 0x00}, /* I */
	{0x20, 0x40, 0x41, 0x3f, 0x01}, /* J */
	{0x7f, 0x08, 0x14, 0x22, 0x41}, /* K */
	{0x7f, 0x40, 0x40, 0x40, 0x40}, /* L */
	{0x7f, 0x02, 0x0c, 0x02, 0x7f}, /* M */
	{0x7f, 0x04, 0x08, 0x10, 0x7f}, /* N */
	{0x3e, 0x41, 0x41, 0x41, 0x3e}, /* O */
	{0x7f, 0x09, 0x09, 0x09, 0x06}, /* P */
	{0x3e, 0x41, 0x51, 0x21, 0x5e}, /* Q */
	{0x7f, 0x09, 0x19, 0x29, 0x46}, /* R */
	{0x46, 0x49, 0x49, 0x49, 0x31}, /* S */
	{0x01, 0x01, 0x7f, 0x01, 0x01}, /* T */
	{0x3f, 0x40, 0x40, 0x40, 0x3f}, /* U */
	{0x1f, 0x20, 0x40, 0x20, 0x1f}, /* V */
	{0x3f, 0x40, 0x38, 0x40, 0x3f}, /* W */
	{0x63, 0x14, 0x08, 0x14, 0x63}, /* X */
	{0x07, 0x08, 0x70, 0x08, 0x07}, /* Y */
	{0x61, 0x51, 0x49, 0x45, 0x43}, /* Z */
	{0x00, 0x7f, 0x41, 0x41, 0x00}, /* [ */
	{0x02, 0x04, 0x08, 0x10, 0x20}, /* ¥ */
	{0x00, 0x41, 0x41, 0x7f, 0x00}, /* ] */
	{0x04, 0x02, 0x01, 0x02, 0x04}, /* ^ */
	{0x40, 0x40, 0x40, 0x40, 0x40}, /* _ */
	{0x00, 0x01, 0x02, 0x04, 0x00}, /* ` */
	{0x20, 0x54, 0x54, 0x54, 0x78}, /* a */
	{0x7f, 0x48, 0x44, 0x44, 0x38}, /* b */
	{0x38, 0x44, 0x44, 0x44, 0x20}, /* c */
	{0x38, 0x44, 0x44, 0x48, 0x7f}, /* d */
	{0x38, 0x54, 0x54, 0x54, 0x18}, /* e */
	{0x08, 0x7e, 0x09, 0x01, 0x02}, /* f */
	{0x0c, 0x52, 0x52, 0x52, 0x3e}, /* g */
	{0x7f, 0x08, 0x04, 0x04, 0x78}, /* h */
	{0x00, 0x44, 0x7d, 0x40, 0x00}, /* i */
	{0x20, 0x40, 0x44, 0x3d, 0x00}, /* j */
	{0x7f, 0x10, 0x28, 0x44, 0x00}, /* k */
	{0x00, 0x41, 0x7f, 0x40, 0x00}, /* l */
	{0x7c, 0x04, 0x18, 0x04, 0x78}, /* m */
	{0x7c, 0x08, 0x04, 0x04, 0x78}, /* n */
	{0x38, 0x44, 0x44, 0x44, 0x38}, /* o */
	{0x7c, 0x14, 0x14, 0x14, 0x08}, /* p */
	{0x08, 0x14, 0x14, 0x18, 0x7c}, /* q */
	{0x7c, 0x08, 0x04, 0x04, 0x08}, /* r */
	{0x48, 0x54, 0x54, 0x54, 0x20}, /* s */
	{0x04, 0x3f, 0x44, 0x40, 0x20}, /* t */
	{0x3c, 0x40, 0x40, 0x20, 0x7c}, /* u */
	{0x1c, 0x20, 0x40, 0x20, 0x1c}, /* v */
	{0x3c, 0x40, 0x30, 0x40, 0x3c}, /* w */
	{0x44, 0x28, 0x10, 0x28, 0x44}, /* x */
	{0x0c, 0x50, 0x50, 0x50, 0x3c}, /* y */
	{0x44, 0x64, 0x54, 0x4c, 0x44}, /* z */
	{0x00, 0x08, 0x36, 0x41, 0x00}, /* { */
	{0x00, 0x00, 0x7f, 0x00, 0x00}, /* | */
	{0x00, 0x41, 0x36, 0x08, 0x00}, /* } */
};

const unsigned char
BigNumbers[10][3][16] PROGMEM =
{
	/* 0 */
	{
		{0,128,192,224,224,96,224,224,192,128,0,0,0,0,0,0},
		{112,255,255,1,0,0,0,0,255,255,254,0,0,0,0,0},
		{0,15,31,60,56,48,56,56,31,15,3,0,0,0,0,0}
	},

	/* 1 */
	{
		{0,0,0,0,128,224,224,0,0,0,0,0,0,0,0,0},
		{0,0,3,3,3,255,255,0,0,0,0,0,0,0,0,0},
		{0,0,56,56,56,63,63,56,56,56,0,0,0,0,0,0},
	},

	/* 2 */
	{
		{0,192,192,224,96,96,224,224,192,128,0,0,0,0,0,0},
		{0,1,0,0,128,192,224,249,63,31,0,0,0,0,0,0},
		{0,60,62,63,63,59,57,56,56,56,56,0,0,0,0,0},
	},

	/* 3 */
	{
		{0,192,224,224,96,96,224,224,192,192,0,0,0,0,0,0},
		{0,1,0,0,48,48,56,125,239,207,0,0,0,0,0,0},
		{0,28,56,56,48,48,56,60,31,15,1,0,0,0,0,0},
	},

	/* 4 */
	{
		{0,0,0,0,0,128,192,224,224,0,0,0,0,0,0,0},
		{224,240,248,222,207,199,193,255,255,192,192,0,0,0,0,0},
		{0,0,0,0,0,0,0,63,63,0,0,0,0,0,0,0},
	},

	/* 5 */
	{
		{0,224,224,224,224,224,224,224,224,224,224,0,0,0,0,0},
		{0,63,63,63,56,56,48,112,240,224,0,0,0,0,0,0},
		{0,28,56,56,48,48,56,60,31,15,1,0,0,0,0,0},
	},

	/* 6 */
	{
		{0,0,128,192,192,224,96,96,224,224,0,0,0,0,0,0},
		{224,254,255,55,57,24,24,56,240,240,192,0,0,0,0,0},
		{0,15,31,28,56,48,48,56,31,15,7,0,0,0,0,0},
	},

	/* 7 */
	{
		{0,224,224,224,224,224,224,224,224,224,224,0,0,0,0,0},
		{0,0,0,0,128,224,248,126,31,7,1,0,0,0,0,0},
		{0,0,56,62,31,7,1,0,0,0,0,0,0,0,0,0},
	},

	/* 8 */
	{
		{0,128,192,224,224,96,96,224,192,192,0,0,0,0,0,0},
		{0,207,255,127,56,48,112,112,255,239,199,0,0,0,0,0},
		{3,15,31,60,56,48,48,56,31,31,15,0,0,0,0,0},
	},

	/* 9 */
	{
		{0,128,192,224,224,96,224,224,192,128,0,0,0,0,0,0},
		{12,63,127,241,224,192,192,225,255,255,254,0,0,0,0,0},
		{0,0,56,48,48,56,56,30,15,7,0,0,0,0,0,0},
	},
};

void
pcd8544Init(void)
{
	PCD8544_DDR |= (1 << PCD8544_DATA);
	/* Toggle Reset */
	PCD8544_PORT &= ~(1 << PCD8544_RESET);
	PCD8544_PORT |= (1 << PCD8544_RESET);

	/* Initial Display Configuration */
	PCD8544_PORT &= ~(1 << PCD8544_DATA);
	spiSendByte(PCD8544_EXTENDED_CMD);
	spiSendByte(PCD8544_VOP);
	spiSendByte(PCD8544_TEMP_COEFF);
	spiSendByte(PCD8544_BIAS_MODE);
	spiSendByte(PCD8544_STANDARD_CMD);
	spiSendByte(PCD8544_NORMAL_MODE);
	PCD8544_PORT |= (1 << PCD8544_DATA);

	pcd8544Clear();
}

void
pcd8544SetContrast(uint8_t contrast)
{
	PCD8544_PORT &= ~(1 << PCD8544_DATA);
	spiSendByte(PCD8544_EXTENDED_CMD);
	spiSendByte(0x80|contrast);
	spiSendByte(PCD8544_STANDARD_CMD);
	PCD8544_PORT |= (1 << PCD8544_DATA);
}

void
pcd8544SetXY(uint8_t x, uint8_t y)
{
	PCD8544_PORT &= ~(1 << PCD8544_DATA);
	if (x <= (PCD8544_WIDTH - 1))
		spiSendByte(0x80|x);
	if (y <= SFONT_MAX_X)
		spiSendByte(0x40|y);
	PCD8544_PORT |= (1 << PCD8544_DATA);
}

void
pcd8544Clear(void)
{
	uint16_t i;

	for (i = 0; i < ((PCD8544_WIDTH * PCD8544_HEIGHT) / 8); i++)
		spiSendByte(0x00);
}

void
pcd8544BigNumber(unsigned char x, unsigned char y, char data)
{
	uint8_t i, j;
	unsigned char val;

	unsigned char *pFont = (unsigned char*) BigNumbers;
	data &= 0x0f;

	for(i = 0; i < 3; i++)
	{
		pcd8544SetXY(x, (y + i));
		for (j = 0; j < 10; j++)
		{
			val = pgm_read_byte(pFont + data * 48 + i * 16 + j);
			spiSendByte(val);
		}
		spiSendByte(0x00);
	}
}

void
pcd8544SmallChar(char data)
{
	uint8_t i;
	unsigned char val;
	unsigned char *pFont = (unsigned char*) SmallFont;

	for (i = 0; i < 5; i++)
	{
		val = pgm_read_byte(pFont + (data - 0x20) * 5 + i);
		spiSendByte(val);
	}
	spiSendByte(0x00);
}

void
pcd8544SmallStr(const char *str)
{
	while (*str)
		pcd8544SmallChar(*str++);
}
