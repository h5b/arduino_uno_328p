/*
 * Copyright (c) 2011 Sebastian Trahm
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
#include <avr/interrupt.h>

#include "board.h"
#include "ds1631.h"
#include "i2c.h"
#include "uart.h"
#include "util.h"

int
main(void)
{
	static const char infostring[] = "SW-I2C Demo - DS1631\r\n";

	/* set User LED on Port B as output */
	DDRB = LED_BIT;
	/* initialize UART */
	uartInit();
	/* initialize I2C */
	i2cInit();
	/* global interrupt enable */
	sei();

	/* DS1631 - Set Continuous Temperature Conversion */
	ds1631WriteConfig(DS1631_WR_ADDR, DS1631_CONT_CONV);
	/* DS1631 - Request Temperature Reading */
	ds1631WriteConfig(DS1631_WR_ADDR, DS1631_READ_TEMP);

	uartPutString(infostring);

	while (1) {
		/* Temperature Reading */
	}

	/* never reached */
	return (0);
}
