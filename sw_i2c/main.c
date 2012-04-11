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
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "board.h"
#include "ds1631.h"
#include "i2c.h"
#include "uart.h"
#include "util.h"

#if 0
/* output binary representation of integer to UART */
void
binrep(unsigned char val)
{
	int i = 0 ;

	for (i = (sizeof(val)*8)-1; i >= 0; i--)
		uartTransmitByte('0' + ((val >> i) & 1));
	uartPutString(": ");
}
#endif

int
main(void)
{
	static const char infostring[] PROGMEM = "SW-I2C Demo - DS1631\r\n";
	char result[CHAR_BUFFER_SIZE];

	/* set User LED on Port B as output */
	DDRB = LED_BIT;
	/* initialize UART */
	uartInit();
	/* initialize I2C */
	i2cInit();
	/* global interrupt enable */
	sei();
	/* initialize ds1631 */
	ds1631Init();

	uartPutString_P(infostring);

	while (1) {

#if 0
		/* output binary representation */
		binrep(temperatureTH);
#endif

		/* Get Temperature Reading */
		uartPutString("Temperature TH (MSB): ");
		ds1631GetTemperature(DS1631_RD_ADDR, result);
		uartPutString(result);
		uartPutString(" °C\r\n");
		_delay_ms(SECOND);
	}

	/* never reached */
	return (0);
}
