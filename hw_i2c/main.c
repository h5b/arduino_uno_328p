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
#include <avr/interrupt.h>

#include "i2c.h"
#include "../board.h"
#include "../hw_uart/uart.h"

#define BAUDRATE	38400

int
main(void)
{
	static const char infostring[] = "HW-I2C (TWI) Demo\r\n";

	DDRB = LED;
	uartInit(BAUDRATE);
	sei();

	uartPutString(infostring);

	while (1) {
	}

	/* never reached */
	return (0);
}
