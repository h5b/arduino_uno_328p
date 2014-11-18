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

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "board.h"
#include "ds1307.h"
#include "i2c.h"
#include "uart.h"

#define BUFFER_SIZE	32

int
main(void)
{
	struct ds1307_t rtc_tm;

	static const char infostring[] PROGMEM = "Demo - DS1307 RTC\r\n";
	char buffer[BUFFER_SIZE];

	uartInit(BAUDRATE);
	i2cInit(I2C_STD_MODE);
	sei();

	ds1307Init();
	ds1307SetTime(SYS_HOUR, SYS_MINS, SYS_SECS);
	ds1307SetDate(SYS_DAY, SYS_MONTH, SYS_YEAR);

	uartPutString_P(infostring);

	while (1) {
		/* Read Current Time from DS1307 and output to UART */
		ds1307GetTime(&rtc_tm);
		sprintf(buffer, "RTC: [%02d:%02d:%02d] - [%02d.%02d.%02d]\r\n",
		    rtc_tm.hours, rtc_tm.minutes, rtc_tm.seconds, rtc_tm.day,
		    rtc_tm.month, rtc_tm.year);
		uartPutString(buffer);
		_delay_ms(1000);
	}

	/* never reached */
	return (0);
}
