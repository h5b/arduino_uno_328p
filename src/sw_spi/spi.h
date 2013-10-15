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

#ifndef _SPI_H_
#define _SPI_H_

/*
 * SPI Port Mapping of ATmega328
 * see Section 14.3.1 "Alternate Functions of Port B"
 * of the ATmega 328 Reference Manual
 */
#define SPI_SS		PB2
#define SPI_MOSI	PB3
#define SPI_MISO	PB4
#define SPI_SCK		PB5

#define SPI_PORT	PORTB
#define SPI_DDR		DDRB

void spiInit(void);
void spiSendByte(unsigned char);

#endif /* _SPI_H_ */
