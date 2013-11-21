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

#include "board.h"

int
main(void)
{
	/*
	 * Initialize TIMER1 to generate compare match event once
	 * per second.
	 *
	 * CTC MODE Enable:			(1 << WGM12)
	 * PRESCALER:				((1 << CS12) | (1 << CS10))
	 * Compare Match Interrupt Enable:	(1 << OCIE1A)
	 * Timer Compare Value:			((F_CPU/PRESCALER) - 1)
	 */
	TCCR1B |= (1 << WGM12);
	TCCR1B |= ((1 << CS12) | (1 << CS10));
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = ((F_CPU / 1024) - 1);

	/* set Port of User LED as output */
	DDRB = USER_LED;
	sei();

	while(1)
	{
		/* everything is done in the ISR */
	}

	/* never reached */
	return (0);
}

/* TIMER1 compare match event ISR */
ISR
(TIMER1_COMPA_vect)
{
	PORTB ^= (USER_LED);
}
