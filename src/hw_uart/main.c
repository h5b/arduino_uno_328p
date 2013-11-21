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

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "board.h"
#include "uart.h"

#define BAUDRATE	38400
#define HALF_SECOND	500

int
main(void)
{
	static const char infostring[] = "HW-UART Demo\r\n";

	/* set User LED on Port B as output */
	DDRB = USER_LED;
	uartInit(BAUDRATE);
	sei();

	uartPutString(infostring);

	while (1) {
		/* output a heartbeat */
		uartPutString(".. ");
		_delay_ms(HALF_SECOND);
	}

	/* never reached */
	return (0);
}
