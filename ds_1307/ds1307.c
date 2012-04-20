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
	unsigned char data;

	/* Request Start Address to be 0x00 (SECONDS) */
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_SEC_ADDR);
	i2cStop();

	/* Consecutive Read Seconds, Minutes, Hours,
	 * Day of Month, Month, Year and Workday */
	i2cStart(DS1307_RD_ADDR);
	data = i2cReadACK();
	/* 7th Bit is CLOCK HALT: ensure it is disabled */
	ds1307_tm.sec = bcd2dec(data & 0x7F);
	data = i2cReadACK();
	ds1307_tm.min = bcd2dec(data);
	data = i2cReadACK();
	ds1307_tm.hour = bcd2dec(data);

	/* XXX: Dummy Read of Day of Week */
	data = i2cReadACK();

	data = i2cReadACK();
	ds1307_tm.day = bcd2dec(data);
	data = i2cReadACK();
	ds1307_tm.month = bcd2dec(data);
	data = i2cReadNAK();
	ds1307_tm.year = bcd2dec(data);

	i2cStop();

	 return &ds1307_tm;
}

void ds1307Init(void)
{
	/* Request Start Address to be 0x07 (CONTROL Register)
	 * and Enable SQW Output */
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_CTL_ADDR);
	i2cWrite(DS1307_SQWE);
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
