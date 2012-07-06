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
 * DS1307 - Circuitry (no battery back-up yet)
 *
 *     .--|[]|--.                      ^ 3V3
 *     |  32k7  |                      |
 *     | .------'                      |
 *     | |    ,____  ____.             |
 *     | '-1--|X1  `' VCC|--8----------'
 *     '---2--|X2     SQW|--7--------------,---=220=--> 3V3
 *      ,--3--|Vbat   SCL|--6---=4k7=--,   |
 *      |  4.-|GND    SDA|--5---=4k7=--|   |
 *      |   | `----------'             |   '----------| GND
 *      .___.                          |
 *          |                          v 3V3
 *          '---| GND
 */

#define DS1307_SEC_ADDR		0x00
#define DS1307_MIN_ADDR		0x01
#define DS1307_HOUR_ADDR	0x02
#define DS1307_DOW_ADDR		0x03
#define DS1307_DAY_ADDR		0x04
#define DS1307_MONTH_ADDR	0x05
#define DS1307_YEAR_ADDR	0x06

#define DS1307_CTL_ADDR		0x07
#define DS1307_SRAM_ADDR	0x08

#define DS1307_SRAM_SIZE	0x38

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

/* Retrieve Hour, Minute and Seconds from System Time */
#define SYS_HOUR (((__TIME__[0]-'0')*10) + (__TIME__[1]-'0'))
#define SYS_MINS (((__TIME__[3]-'0')*10) + (__TIME__[4]-'0'))
#define SYS_SECS (((__TIME__[6]-'0')*10) + (__TIME__[7]-'0'))

/* Retrieve current Day from System. Value Range is 01-31 */
#define SYS_DAY ((					\
	(__DATE__[4]==' ' ? 0 : __DATE__[4]-'0')*10) +	\
	(__DATE__[5]-'0'))

/*
 * Map the current Month as retrieved from System to
 * its nummeric value as expected by DS1307.
 * Value Range is 01-12
 */
#define SYS_MONTH (						\
	  __DATE__[2] == 'n' ? (__DATE__[1] == 'a' ? 1 : 6)	\
	: __DATE__[2] == 'b' ? 2				\
	: __DATE__[2] == 'r' ? (__DATE__[1] == 'p' ? 4 : 3)	\
	: __DATE__[2] == 'y' ? 5				\
	: __DATE__[2] == 'l' ? 7				\
	: __DATE__[2] == 'g' ? 8				\
	: __DATE__[2] == 'p' ? 9				\
	: __DATE__[2] == 't' ? 10				\
	: __DATE__[2] == 'v' ? 11 : 12)

/*
 * Retrieve current Year from System.
 * Only consider last two digits of year due to the
 * fact that the value range of DS1307 is 00-99
 * for Year 2000 until 2099
 */
#define SYS_YEAR (((__DATE__[9]-'0')* 10) + (__DATE__[10]-'0'))

/*
 * DS1307 - Register Map
 *
 *      ,----,--------------,-------------------.
 * 0x00 | CH | 10 SECONDS   |       SECONDS     | 00-59
 *      |----+--------------+-------------------|
 * 0x01 | X  | 10 MINUTES   |       MINUTES     | 00-59
 *      |----+----,----,----+-------------------|
 *      |    | 12 |A/P | 10 |                   |
 * 0x02 | X  |----+----+----|       HOURS       | 00-23
 *      |    | 24 |10HR| HR |                   |
 *      |----+----+----+----+----,--------------|
 * 0x03 | X  | X  | X  | X  | X  |  DAY OF WEEK | 1-7
 *      |----+----+---------+----'--------------|
 * 0x04 | X  | X  | 10 DATE |       DAY (DATE)  | 01-31
 *      |----+----+---------+-------------------|
 * 0x05 | X  | X  | 10 MONTH|       MONTH       | 01-12
 *      |----'----'---------+-------------------|
 * 0x06 |      10 YEAR      |       YEAR        | 00-99
 *      |----,----,----,----+----,----,----,----|
 * 0x07 | OUT|  X | X  |SQWE| X  | X  | X  | X  |
 *      `----'----'----'----'----'----'----'----'
 *      7                                       0
 */
struct rtc_tm {
	/* 0x00 */
	int sec : 7;
	int ch : 1;
	/* 0x01 */
	int min : 7;
	int minpad : 1;
	/* 0x02 */
	int hour : 6;
	int ampm : 1;
	int hourpad : 1;
	/* 0x03 */
	int dow : 3;
	int dowpad : 5;
	/* 0x04 */
	int day : 6;
	int daypad : 2;
	/* 0x05 */
	int month : 5;
	int monthpad : 3;
	/* 0x06 */
	int year;
	/* 0x07 */
	char ctl;
	/* 0x08 - 0x3F */
	char sram[56];
};

extern struct rtc_tm ds1307_tm;

struct rtc_tm* ds1307GetTime(void);
void ds1307Init(void);
void ds1307SetDate(uint8_t, uint8_t, uint8_t);
void ds1307SetTime(uint8_t, uint8_t, uint8_t);

#endif /* _DS1307_H_ */
