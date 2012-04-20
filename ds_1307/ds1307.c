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

#include <avr/io.h>

#include "ds1307.h"
#include "../sw_i2c/i2c.h"
#include "../util/util.h"

struct rtc_tm ds1307_tm;

struct rtc_tm*
ds1307GetTime(void)
{
	unsigned char rtcInfo[7];
	uint8_t i;

	/* Request Start Address to be 0x00 (SECONDS) */
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_SEC_ADDR);
	i2cStop();

	/* Request Read from DS1307 */
	i2cStart(DS1307_RD_ADDR);
	/*
	 * Consecutive Read Seven Bytes: Seconds, Minutes,
	 * Hours, Workday, Day of Month, Month, Year
	 */
	for (i=0; i < (sizeof(rtcInfo) - 1); i++)
	{
		rtcInfo[i] = bcd2dec(i2cReadACK());
	}
	/* Last Read has to be NAK */
	rtcInfo[sizeof(rtcInfo)] = bcd2dec(i2cReadNAK());
	i2cStop();

	/* 7th Bit is CLOCK HALT: Mask Seconds to ensure it is Disabled */
	rtcInfo[0] &= (0x7F);

	/* Fill time structure of DS1307 with data */
	ds1307_tm.sec = rtcInfo[0];
	ds1307_tm.min = rtcInfo[1];
	ds1307_tm.hour = rtcInfo[2];
	ds1307_tm.dow = rtcInfo[3];
	ds1307_tm.day = rtcInfo[4];
	ds1307_tm.month = rtcInfo[5];
	ds1307_tm.year = rtcInfo[6];

	return &ds1307_tm;
}

void
ds1307Init(void)
{
	/*
	 * Request Start Address to be 0x07 (CONTROL Register)
	 * and Enable SQW Output
	 */
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_CTL_ADDR);
	i2cWrite(DS1307_SQWE);
	i2cStop();
}

void
ds1307SetDate(uint8_t day, uint8_t month, uint8_t year)
{
	/* Request Start Address to be 0x04 (DAY (DATE)) */
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_DAY_ADDR);
	i2cWrite(dec2bcd(day));
	i2cWrite(dec2bcd(month));
	i2cWrite(dec2bcd(year));
	i2cStop();
}

void
ds1307SetTime(uint8_t hours, uint8_t mins, uint8_t secs)
{
	/* Request Start Address to be 0x00 (SECONDS) */
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_SEC_ADDR);
	i2cWrite(dec2bcd(secs));
	i2cWrite(dec2bcd(mins));
	i2cWrite(dec2bcd(hours));
	i2cStop();
}
