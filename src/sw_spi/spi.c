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

#include "spi.h"

void
spiSendByte(unsigned char data)
{
	SPI_PORT &= ~(1 << SPI_SS);
	SPDR = data;
	/* Wait until Transmission complete */
	while (!(SPSR & (1<<SPIF)));
	SPI_PORT |= (1 << SPI_SS);
}

void
spiInit(void)
{
	/* Set MOSI, SCK and SS as outputs */
	SPI_DDR |= (1 << SPI_MOSI);
	SPI_DDR |= (1 << SPI_SCK);
	SPI_DDR |= (1 << SPI_SS);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = ((1<<SPE)|(1<<MSTR)|(1<<SPR0));
}
