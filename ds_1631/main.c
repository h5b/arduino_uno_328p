/*
 * Copyright (c) 2011-2012 Sebastian Trahm
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

#include "ds1631.h"
#include "../board.h"
#include "../hw_uart/uart.h"
#include "../sw_i2c/i2c.h"

#define CHAR_BUFFER_SIZE	32
#define SECOND			1000

int
main(void)
{
	static const char infostring[] PROGMEM = "SW-I2C Demo - DS1631\r\n";
	char temperature[CHAR_BUFFER_SIZE];
	char buffer[CHAR_BUFFER_SIZE];
	unsigned char readCount;

	DDRB = LED;
	uartInit();
	i2cInit(I2C_FAST_MODE);
	sei();
	ds1631Init();
	uartPutString_P(infostring);

	while (1) {
		readCount = ds1631GetRegister(DS1631_READ_COUNT);
		ds1631GetTemperature(DS1631_RD_ADDR, temperature);
		sprintf(buffer, "TEMP: [COUNT REG: %02d] [TH: %s °C]\r\n",
		    readCount, temperature);
		uartPutString(buffer);
		_delay_ms(SECOND);
	}

	/* never reached */
	return (0);
}
