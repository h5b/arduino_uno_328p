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

#include <avr/io.h>

#include "ds1631.h"
#include "i2c.h"
#include "util.h"

void
ds1631Init(struct ds1631_t* ds)
{
	unsigned char config;

	/* Read Config Register and Set 12 Bit Conversion */
	config = ds1631ReadRegister(ds, DS1631_ACCESS_CFG);
	config |= DS1631_RES_12BIT;
	i2cStart((ds->addr & 0xFE));
	i2cWrite(DS1631_ACCESS_CFG);
	i2cWrite(config);
	i2cStop();

	ds1631WriteConfig(ds, DS1631_CONT_CONV);
	ds1631WriteConfig(ds, DS1631_START_CONV);
}

void
ds1631WriteConfig(struct ds1631_t* ds, unsigned char data)
{
	i2cStart((ds->addr & 0xFE));
	i2cWrite(data);
	i2cStop();
}

void
ds1631ReadSensor(struct ds1631_t* ds)
{
	ds1631WriteConfig(ds, DS1631_READ_TEMP);

	i2cStart(ds->addr);
	ds->msb = i2cReadACK();
	ds->lsb = i2cReadNAK();
	i2cStop();

	/*
	 * The temperature reading of less than 0 degree Celsius is
	 * obtained by calculating the two's complement of the data.
	 * We only consider the Most Significant Byte for now.
	 */
	if (ds->msb & 0x80) {
		ds->val = (int16_t)(ds->msb & 0x7F) - ((ds->msb & 0x80) ? 128 : 0);
	} else {
		ds->val = (int16_t)(ds->msb);
	}
}

unsigned char
ds1631ReadRegister(struct ds1631_t* ds, unsigned char cmd)
{
	unsigned char result;

	i2cStart((ds->addr & 0xFE));
	i2cWrite(cmd);
	i2cStop();

	i2cStart(ds->addr);
	result = i2cReadNAK();
	i2cStop();

	return result;
}
