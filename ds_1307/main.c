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

#include "board.h"
#include "ds1307.h"
#include "i2c.h"
#include "uart.h"

/* Retrieve Hour, Minute and Seconds from System Time */
#define SYS_HOUR (((__TIME__[0]-'0')*10) + (__TIME__[1]-'0'))
#define SYS_MINS (((__TIME__[3]-'0')*10) + (__TIME__[4]-'0'))
#define SYS_SECS (((__TIME__[6]-'0')*10) + (__TIME__[7]-'0')

int
main(void)
{
	static const char infostring[] PROGMEM = "RTC Demo - DS1307\r\n";
	struct rtc_tm* rtc = NULL;
	char buffer[16];

	/* set User LED on Port B as output */
	DDRB = LED_BIT;
	/* initialize UART */
	uartInit();
	/* initialize I2C */
	i2cInit();
	/* global interrupt enable */
	sei();

	uartPutString_P(infostring);

	while (1) {
		/* do nothing */
	}

	/* never reached */
	return (0);
}
