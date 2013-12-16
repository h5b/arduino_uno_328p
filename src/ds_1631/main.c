/*
 * Copyright (c) 2011-2013 Sebastian Trahm
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
#include "ds1631.h"
#include "i2c.h"
#include "uart.h"

#define BUFFER_SIZE	48
#define SECOND		1000

int
main(void)
{
	static const char infostring[] PROGMEM = "Demo - DS1631 Thermometer\r\n";
	struct ds1631_t* ds1631_sensor = NULL;
	char buffer[BUFFER_SIZE];
	unsigned char readCount;

	uartInit(BAUDRATE);
	i2cInit(I2C_FAST_MODE);
	ds1631Init();
	sei();

	uartPutString_P(infostring);

	while (1) {
		readCount = ds1631GetRegister(DS1631_READ_COUNT);
		ds1631_sensor = ds1631GetTemperature(DS1631_RD_ADDR);

		sprintf(buffer,
		    "[COUNT: %02d] [TH: %03d] [TL: %03d]\r\n",
		    readCount, ds1631_sensor->msb, ds1631_sensor->lsb);

		uartPutString(buffer);
		_delay_ms(SECOND);
	}

	/* never reached */
	return (0);
}
