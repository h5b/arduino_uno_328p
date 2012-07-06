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

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "ds1307.h"
#include "../board.h"
#include "../hw_uart/uart.h"
#include "../sw_i2c/i2c.h"

#define SECOND	1000

int
main(void)
{
	static const char infostring[] PROGMEM = "RTC Demo - DS1307\r\n";
	struct rtc_tm* rtc = NULL;
	char buffer[32];

	/* set User LED on Port B as output */
	DDRB = LED;
	/* initialize UART */
	uartInit();
	/*
	 * Initialize I2C Bus to Standard Mode.
	 * According to the datasheet the DS1307 operates in
	 * the standard mode (100kHz) only.
	 * See section "I2C DATA BUS" on page 10 
	 */
	i2cInit(I2C_STD_MODE);
	sei();

	/* Enable DS1307 and SQW Output */
	ds1307Init();
	/* Initialize DS1307 with System Time */
	ds1307SetTime(SYS_HOUR, SYS_MINS, SYS_SECS);
	/* Initialize DS1307 with System Date */
	ds1307SetDate(SYS_DAY, SYS_MONTH, SYS_YEAR);

	/* output Startup Message on UART */
	uartPutString_P(infostring);

	while (1) {
		/* Read Current Time from DS1307 and output to UART */
		rtc = ds1307GetTime();
		sprintf(buffer, "RTC: [%02d:%02d:%02d] - [%02d.%02d.%02d]\r\n",
		    rtc->hour, rtc->min, rtc->sec, rtc->day, rtc->month,
		    rtc->year);
		uartPutString(buffer);
		_delay_ms(SECOND);
	}

	/* never reached */
	return (0);
}
