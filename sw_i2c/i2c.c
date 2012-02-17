/*
 * Copyright (c) 2011, 2012 Sebastian Trahm
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
#include <compat/twi.h>

#include "i2c.h"

void
i2cInit(void)
{
	/* set prescaler to 0 */
	TWSR = 0;
	/* initialize I2C bus clock to 400kHz (fast mode) */
	TWBR = ((F_CPU / I2C_CLOCK) - 16) / 2;
}

void
i2cStop(void)
{
	/* send STOP condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	/* wait until bus is released */
	while (TWCR & (1<<TWSTO));
}

unsigned char
i2cReadACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	/* wait until completed */
	while (!(TWCR & (1<<TWINT)));

	return TWDR;
}

unsigned char
i2cReadNAK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* wait until completed */
	while (!(TWCR & (1<<TWINT)));

	return TWDR;
}

unsigned char
i2cStart(unsigned char addr)
{
	/* send START condition */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	/* wait until completed */
	while (!(TWCR & (1<<TWINT)));

	if ((TW_STATUS != TW_START) && (TW_STATUS != TW_REP_START))
		return 1;

	/* send device address */
	TWDR = addr;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while (!(TWCR & (1<<TWINT)));

	if ((TW_STATUS != TW_MT_SLA_ACK) && (TW_STATUS != TW_MR_SLA_ACK))
		return 1;

	return 0;
}

unsigned char
i2cWrite(unsigned char data)
{
	/* load and transmit data */
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	/* wait until completed */
	while (!(TWCR & (1<<TWINT)));

	if (TW_STATUS != TW_MT_DATA_ACK)
		return 1;

	return 0;
}
