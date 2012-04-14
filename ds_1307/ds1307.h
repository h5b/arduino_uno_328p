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

#ifndef _DS1307_H_
#define _DS1307_H_

/*
 * DS1307 - Circuitry
 *
 *     .--|[]|--.                      ^ 3V3
 *     |  32K7  |                      |
 *     | .------'                      |
 *     | |    ,____  ____.             |
 *     | '-1--|X1  `' VCC|--8----------'
 *     '---2--|X2     SQW|--7--------------,---=220=--> 3V3
 *      ,--3--|Vbat   SCL|--6---=4k7=--,   |
 *      |  4.-|GND    SDA|--5---=4k7=--|   |
 *      |   | `----------'             |   '----->|---| GND
 *      .___.                          |
 *          |                          v 3V3
 *          '---| GND
 */


#define DS1307_SEC		0x00
#define DS1307_MIN		0x01
#define DS1307_HOUR		0x02
#define DS1307_DOW		0x03
#define DS1307_DATE		0x04
#define DS1307_MONTH		0x05
#define DS1307_YEAR		0x06

#define DS1307_CTL_ADDR		0x07
#define DS1307_SRAM_ADDR	0x08
#define DS1307_SRAM_SIZE	0x38	/* 56 bytes of NV SRAM */

#define DS1307_RD_ADDR		0xD1
#define DS1307_WR_ADDR		0xD0

/*
 * DS1307 - Control Register
 * ,----------------------------------------.
 * | OUT | 0 | 0 | SQWE | 0 | 0 | RS1 | RS0 |
 * `----------------------------------------'
 * 7                                        0
 *
 *
 * SQW Output Rate in relation to Square-Wave Enable (SQWE)
 * and Rate Select (RS0/RS1) settings
 *
 * RS0 | RS1 | SQWE | SQW Output
 * ----+-----+ -----+-----------
 *  0  |  0  |  1   |      1Hz
 *  0  |  1  |  1   |  4k096Hz
 *  1  |  0  |  1   |  8k192Hz
 *  1  |  1  |  1   | 32k768Hz
 */
#define DS1307_SQWE		0x10

/*
 * DS1307 - Register Map Struct
 */
struct rtc_tm {
	/* 0x00 */
	int sec;
	int min;
	int hour;
	int mday;
	int mon;
	int year;
	int wday;
	/* XXX Add complete Register Map and Padding */
	/* 0x07 */
	char ctl;
	/* 0x08 - 0x3F */
	char sram[56];
};

extern struct rtc_tm ds1307_tm;

struct rtc_tm* ds1307GetTime(void);
void ds1307Init(void);
void ds1307SetTime(uint8_t, uint8_t, uint8_t);

#endif /* _DS1307_H_ */
