/*
 * Copyright (c) 2012-2014 Sebastian Trahm
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
#include "i2c.h"
#include "util.h"

void
ds1307GetTime(struct ds1307_t* rtc)
{
	uint8_t i, rtcInfo[7];

	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_SEC_ADDR);
	i2cStop();

	i2cStart(DS1307_RD_ADDR);
	/*
	 * Consecutive Read the first Six Bytes: Seconds, Minutes,
	 * Hours, Workday, Day of Month, Month
	 */
	for (i = 0; i < (sizeof(rtcInfo)-1); i++)
	{
		rtcInfo[i] = bcd2dec(i2cReadACK());
	}
	/* Last Read is Year (7th Byte) and needs to be NAK */
	rtcInfo[sizeof(rtcInfo)-1] = bcd2dec(i2cReadNAK());
	i2cStop();

	/* Clear 7th Bit of Seconds to ensure CLOCK HALT is disabled */
	rtcInfo[0] &= DS1307_CLOCK_HALT;

	rtc->seconds = rtcInfo[0];
	rtc->minutes = rtcInfo[1];
	rtc->hours = rtcInfo[2];
	rtc->dayOfWeek = rtcInfo[3];
	rtc->day = rtcInfo[4];
	rtc->month = rtcInfo[5];
	rtc->year = rtcInfo[6];
}

void
ds1307Init(void)
{
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_CTL_ADDR);
	i2cWrite(DS1307_SQWE);
	i2cStop();
}

void
ds1307SetDate(uint8_t day, uint8_t month, uint8_t year)
{
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
	i2cStart(DS1307_WR_ADDR);
	i2cWrite(DS1307_SEC_ADDR);
	i2cWrite(dec2bcd(secs));
	i2cWrite(dec2bcd(mins));
	i2cWrite(dec2bcd(hours));
	i2cStop();
}
